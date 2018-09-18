#pragma once

// CMysocket ÃüÁîÄ¿±ê

class CMysocket : public CSocket
{
public:
	CMysocket();
	virtual ~CMysocket();
	virtual void OnReceive(int nErrorCode);

};


