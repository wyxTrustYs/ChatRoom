#pragma once

// CMysocket ����Ŀ��

class CMysocket : public CSocket
{
public:
	CMysocket();
	virtual ~CMysocket();
	virtual void OnReceive(int nErrorCode);

};


