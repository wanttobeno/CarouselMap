#pragma once

#include <string>

namespace Gdiplus
{
	class Image;
}

class CarouselPic
{
public:
	CarouselPic();
	~CarouselPic();
	bool LoadPic(std::wstring strFile);
	Gdiplus::Image* GetImage();
	unsigned int GetWidth();
	unsigned int GetHeight();

	// 是否被选中
	bool IsSelect();
	void SetSelect(bool bSel = true);

	void SetLeft(int nX);
	int GetLeft();
	void RightMove();
	void LeftMove();
protected:
	void unInit();
private:
	Gdiplus::Image*  m_pImage;
	bool  m_bInit;
	// 是否被选中（比如激活）
	bool  m_bSelect;
	int m_nX;
};

