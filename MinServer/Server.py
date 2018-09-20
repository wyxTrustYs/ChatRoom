# coding: utf8
import enum
import socket
import struct
import threading
import minsql

Userdict = {}


class MsgType(enum.Enum):
    RegisterMsg = 0
    LoginMsg = 1
    Search = 2
    FriendChat = 3


class SendType(enum.Enum):
    RegisterMsg = 0,
    LoginMsg = 1
    Search = 2
    FriendChat = 3


# 添加服务器类
class Server(object):
    dictlist = {}

    # 构造
    def __init__(self):
        # 初始化套接字
        self.server = socket.socket()
        # 绑定端口，供客户端连接
        self.server.bind(("0.0.0.0", 8000))
        # 监听
        self.server.listen()
        # 初始化的mysql连接
        self.sql = minsql.Mysql()

    # 等待连接
    def accept(self):
        while True:
            # 接收连接， 并输出连接到的主机
            client, addr = self.server.accept()
            print(addr, '连入了服务器')
            # 接收客户端，并为每个客户端开启独立的线程
            t = threading.Thread(target=self.recv, args=(client,))
            t.start()

    # 处理收到的消息
    def recv(self, client):
        while True:
            try:
                # 接收数据
                message = client.recv(2048)
                # 获取发送过来的消息类型
                type, = struct.unpack('i', message[:4])

                # 调用函数的时候，一定self【否则报错，缺少一个参数】
                message = message[4:]
                self.dictfun[type](self, client, message)

                # 如果连接断开则关闭当前socket
            except Exception as msg:
                # 当一个客户端套接字被关闭的时候，会产生一个异常
                print(msg)
                print(client.getsockname(), '退出了服务器')
                self.sql.insert("UPDATE user SET UserStatus=0 "
                                "WHERE UserId=%s " % Userdict[client])
                Userdict.pop(client)
                print(Userdict)
                client.close()
                break

    # 需要用到套接字以及接收到的信息
    def register(self, client, msg):
        # 因为客户端中存储的是wchar_t，所以需要的大小*2
        hwnd, sex, name, pswd, nick = struct.unpack('i8s40s40s40s', msg[0:132])
        # 对解包出的数据进行解码
        sex = sex.decode('utf16').rstrip('\x00')  # rstrip 清楚最右边的指定字符
        name = name.decode('utf16').rstrip('\x00')
        pswd = pswd.decode('utf16').rstrip('\x00')
        nick = nick.decode('utf16').rstrip('\x00')

        print(sex, name, pswd, nick)
        #        birthday = birthday.decode('utf16').rstrip('\x00')
        # 查询数据库中是否存在相同的用户名
        if self.sql.select("SELECT * FROM user WHERE UserName = '%s'" % name) == 0:
            # 如果查询到的条数为0，说明可以进行注册
            if self.sql.insert("INSERT INTO user(UserId, UserName, UserPassword, UserSex,RegDateTime) "
                               "VALUE ('%s', '%s', MD5('%s'), '%s',  now())" % (
                                       name, nick, pswd, sex)):
                client.send(struct.pack('iii20s', SendType.RegisterMsg.value[0], hwnd, 1, '注册成功'.encode('GBK')))
            else:
                client.send(struct.pack('iii20s', SendType.RegisterMsg.value[0], hwnd, 0, '未知错误'.encode('GBK')))
        # 如果已经查询到，就返回信息
        else:
            client.send(struct.pack('iii20s', SendType.RegisterMsg.value[0], hwnd, 0, '已存在的用户名'.encode('GBK')))

    # 返回登录信息
    def login(self, client, msg):
        hwnd, name, pswd = struct.unpack('i40s40s', msg[0:84])
        # 对解包出的数据进行解码
        name = name.decode('utf16').rstrip('\x00')
        pswd = pswd.decode('utf16').rstrip('\x00')
        # 查看用户名是否匹配
        if self.sql.select("SELECT * FROM user WHERE UserId=%s "
                           "AND UserPassword=MD5('%s')" % (name, pswd)) != 0:
            self.sql.insert("UPDATE user SET UserStatus=1 "
                            "WHERE UserId=%s AND UserPassword=MD5('%s')" % (name, pswd))
            nickname = self.sql.QuerySql("SELECT UserName FROM user WHERE UserId=%s " % name)
            nick = nickname[0][0]
            client.send(
                struct.pack('iii20s20s', SendType.LoginMsg.value, hwnd, 1, '登录成功'.encode('GBK'), nick.encode('GBK')))

            Server.dictlist[name] = client
            Userdict[client] = name
        else:
            client.send(struct.pack('iii20s', SendType.LoginMsg.value, hwnd, 0, '用户名或密码错误'.encode('GBK')))

    def search(self, client, msg):
        hwnd, name = struct.unpack('i40s', msg[0:44])
        # 对解包出的数据进行解码
        name = name.decode('utf16').rstrip('\x00')
        Lnum = []
        friend = self.sql.QuerySql("SELECT idb FROM friend WHERE ida=%s " % name)
        for num in friend:
            nickname = self.sql.QuerySql("SELECT UserName FROM user WHERE UserId=%s " % num[0])
            nameid = str(num[0])
            client.send(struct.pack('ii10s10s', SendType.Search.value, hwnd, nameid.encode('gbk'),
                                    nickname[0][0].encode('gbk')))
            Lnum.append(num[0])

    def friendchat(self, client, msg):
        hwnd, user1, user2, message = struct.unpack('i40s40s200s', msg[0:284])
        # 获取需要发送到的用户名
        user1 = user1.decode('utf16').rstrip('\x00')
        user2 = user2.decode('utf16').rstrip('\x00')
        message = message.decode('utf16').rstrip('\x00')

        print(user1)
        print(user2)
        # 将原来的包转发出去
        if user2 in Server.dictlist:
            Server.dictlist[user2].send(b'\x03\x00\x00\x00' + msg)
            # 添加聊天记录到数据库
            # sql = "INSERT INTO msg_log VALUE('%s', '%s', '%s', now())" % (user1, user2, message)
            # self.sql.insert(sql)

    # 一个字典，包含的是对应的消息处理函数
    dictfun = {
        0: register,
        1: login,
        2: search,
        3: friendchat
    }


if __name__ == '__main__':
    server = Server()
    server.accept()
