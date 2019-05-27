#pragma once


#include <vector>

class CarouselPic;

class CMyPainter
{
	CMyPainter();
public:
	static CMyPainter* GetInst();
	~CMyPainter();
	void AddPic(CarouselPic* pPic);
	bool RemovePic(CarouselPic* pPic);
	void Painter(HDC dc);

	void SelectPic(int nPic);
	void FirstAndLastSwap(bool bBeFirst);
	void MoveToRight(int nValue);
	void MoveToLeft(int nValue);

	void SetRightMove();
	void SetLeftMove();
private:
	std::vector<CarouselPic*>   m_vContainPic;
	bool	m_bRightMove;
};

