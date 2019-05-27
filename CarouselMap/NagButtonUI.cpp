#include "stdafx.h"
#include "NagButtonUI.h"


CNagButtonUI::CNagButtonUI()
{
	m_state = GDI_BUTON_STATE::G_NORMAL;
}

CNagButtonUI::~CNagButtonUI()
{

}

void CNagButtonUI::UpdateState(GDI_BUTON_STATE state)
{
	m_state = state;
}

GDI_BUTON_STATE CNagButtonUI::GetState()
{
	return m_state;
}

void CNagButtonUI::SetPos(Gdiplus::RectF rect)
{
	m_Pos = rect;
}

bool CNagButtonUI::ChangeSate(int x, int y)
{
	GDI_BUTON_STATE state = m_state;
	if (x>= m_Pos.X && x <= m_Pos.X + m_Pos.Width)
	{
		if (y >= m_Pos.Y && y <= m_Pos.Y + m_Pos.Height)
		{
			m_state = G_HOT;
		}
		else
		{
			m_state = G_NORMAL;
		}
	}
	else
	{
		m_state = G_NORMAL;
	}
	if (state != m_state)
		return true;
	else
		return false;
}

void CNagButtonUI::Draw(Gdiplus::Graphics& graphics,bool bLeft)
{
	Gdiplus::Color bkColor;
	switch (m_state)
	{
	case G_NORMAL:
		bkColor = Gdiplus::Color(0x60, 0x00, 0x00, 0x00);
		break;
	case G_HOT:
		bkColor = Gdiplus::Color(0x80, 0x00, 0x00, 0x00);
		break;
	case G_DWON:
		bkColor = Gdiplus::Color(0xD0, 0x00, 0x00, 0x00);
		break;
	default:
		break;
	}

	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::SolidBrush  solidBrush(bkColor);
	Gdiplus::RectF bkRect = m_Pos;// (500, 90, 38, 38);
	graphics.FillEllipse(&solidBrush, bkRect);

	if (bLeft)
	{
		Gdiplus::RectF bkRect(20, 90, 38, 38);

#define  ZY_OFF1_X1 21
#define  ZY_OFF1_X2 9

#define  ZY_OFF_Y1 6
#define  ZY_OFF_Y2 19
#define  ZY_OFF_Y3 30
		Gdiplus::Pen pen(Gdiplus::Color(0xFF, 0xff, 0xff, 0xff), 2);
		Gdiplus::Point pt1(m_Pos.GetLeft() + ZY_OFF1_X1, m_Pos.GetTop() + ZY_OFF_Y1);
		Gdiplus::Point pt2(m_Pos.GetLeft() + ZY_OFF1_X2, m_Pos.GetTop() + ZY_OFF_Y2);
		Gdiplus::Point pt3(m_Pos.GetLeft() + ZY_OFF1_X1, m_Pos.GetTop() + ZY_OFF_Y3);
		graphics.DrawLine(&pen, pt1, pt2);
		graphics.DrawLine(&pen, pt2, pt3);
	}
	else
	{

#define  ZY_OFF2_X1 17
#define  ZY_OFF2_X2 28


		Gdiplus::Pen pen(Gdiplus::Color(0xFF, 0xff, 0xff, 0xff), 2);
		Gdiplus::Point pt1(m_Pos.GetLeft() + ZY_OFF2_X1, m_Pos.GetTop() + ZY_OFF_Y1);
		Gdiplus::Point pt2(m_Pos.GetLeft() + ZY_OFF2_X2, m_Pos.GetTop() + ZY_OFF_Y2);
		Gdiplus::Point pt3(m_Pos.GetLeft() + ZY_OFF2_X1, m_Pos.GetTop() + ZY_OFF_Y3);
		graphics.DrawLine(&pen, pt1, pt2);
		graphics.DrawLine(&pen, pt2, pt3);
	}
}

void CNagButtonUI::Draw(Gdiplus::Graphics& graphics, int x, int y, int nWidth, int nHeight)
{
	Gdiplus::Color bkColor;
	switch (m_state)
	{
	case G_NORMAL:
		bkColor = Gdiplus::Color(0xA0, 0x00, 0x00, 0x00);
		break;
	case G_HOT:
		bkColor = Gdiplus::Color(0x80, 0x00, 0x00, 0x00);
		break;
	case G_DWON:
		bkColor = Gdiplus::Color(0x60, 0x00, 0x00, 0x00);
		break;
	default:
		break;
	}

	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::SolidBrush  solidBrush(bkColor);
	Gdiplus::RectF bkRect = m_Pos;
	graphics.FillEllipse(&solidBrush, bkRect);
}