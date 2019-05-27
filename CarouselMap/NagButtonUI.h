#pragma once
#include <gdiplus.h>

enum GDI_BUTON_STATE
{
	G_NORMAL=0,
	G_HOT = 1,
	G_DWON = 2,
};


class CNagButtonUI
{
public:
	CNagButtonUI();
	~CNagButtonUI();
	void UpdateState(GDI_BUTON_STATE state);
	GDI_BUTON_STATE GetState();
	void SetPos(Gdiplus::RectF rect);
	bool ChangeSate(int x, int y);
	void Draw(Gdiplus::Graphics& graphics,bool bLeft);
	void Draw(Gdiplus::Graphics& graphics, int x, int y, int nWidth, int nHeight);
private:
	GDI_BUTON_STATE m_state;
	Gdiplus::RectF  m_Pos;
};

