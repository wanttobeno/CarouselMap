#pragma once

typedef unsigned long ULONG_PTR;

class CAutoGdiPlus
{
public:
	CAutoGdiPlus();
	~CAutoGdiPlus();
private:
	ULONG_PTR m_gdiplusToken;;
};

