#include "stdafx.h"
#include "MyPainter.h"
#include <gdiplus.h>
#include "CarouselPic.h"

using namespace Gdiplus;


CMyPainter::CMyPainter()
{
}


CMyPainter::~CMyPainter()
{
}

CMyPainter* CMyPainter::GetInst()
{
	static CMyPainter painter;
	return &painter;
}

void CMyPainter::AddPic(CarouselPic* pPic)
{
	m_vContainPic.push_back(pPic);
}

bool CMyPainter::RemovePic(CarouselPic* pPic)
{
	for (auto it = m_vContainPic.begin(); it != m_vContainPic.end(); it++)
	{
		if (*it = pPic)
		{
			m_vContainPic.erase(it);
			return true;
		}
	}
	return false;
}

void CMyPainter::PaintPic(CarouselPic* pPic)
{

}

extern Gdiplus::Rect gRect[3];
extern int gY;
extern int gX;

void MyDragImage(Gdiplus::Graphics &graphics, Gdiplus::Image* pImage,Gdiplus::Rect& rect)
{
	graphics.DrawImage(pImage, rect);
}

#define  PIC_MID_WIDTH  302
#define  PIC_MID_HEIGHT 144

#define  PIC_BIG_WIDTH  385
#define  PIC_BIG_HEIGHT 183

#define  PIC_WIDTH 288

int gLeft11 = 98;

void CMyPainter::Painter(HDC dc)
{
	if (m_vContainPic.empty())
		return;
	Gdiplus::Graphics graphics(dc);
	int nSize = m_vContainPic.size();
	int nMidPic = -1;
	for (size_t i = 0; i < nSize; i++)
	{
		if ((m_vContainPic[i])->IsSelect() == false)
		{
			//MyDragImage(graphics, (m_vContainPic[i])->GetImage(), gRect[i]);
			int nLeft = (m_vContainPic[i])->GetLeft();
			nLeft = abs(nLeft);
			if (nLeft == 0)
			{
				Gdiplus::Rect rect(nLeft, gY, PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[i])->GetImage(), rect);
			}
			else if (nLeft != PIC_WIDTH)
			{
				if (nLeft >= 0 && nLeft < PIC_WIDTH*3)
				{
					Gdiplus::Rect rect(nLeft - PIC_WIDTH, gY, PIC_MID_WIDTH, PIC_MID_HEIGHT);
					MyDragImage(graphics, (m_vContainPic[i])->GetImage(), rect);
				}
			}
			else if (nLeft == PIC_WIDTH)
			{
				nMidPic = i;
			}
		}
	}

	if (nMidPic!=-1)
	{
		Gdiplus::Rect rect(gX + gLeft11, gY - 39, PIC_BIG_WIDTH, PIC_BIG_HEIGHT);
		MyDragImage(graphics, (m_vContainPic[nMidPic])->GetImage(), rect);
	}
}

void CMyPainter::SelectPic(int nPic)
{
	for (size_t i = 0; i < m_vContainPic.size(); i++)
	{
		if (i == nPic)
		{
			(m_vContainPic[i])->SetSelect();
		}
		else
		{
			(m_vContainPic[i])->SetSelect(false);
		}
	}
}

void CMyPainter::FirstAndLastSwap(bool bBeFirst)
{
	int nSize = m_vContainPic.size();
	if (nSize <= 0)
		return;
	if (bBeFirst)
	{
		auto last = m_vContainPic[nSize - 1];
		m_vContainPic.erase(m_vContainPic.end()-1);
		m_vContainPic.insert(m_vContainPic.begin(), last);
	}
	else
	{
		auto first = m_vContainPic[0];
		m_vContainPic.erase(m_vContainPic.begin());
		m_vContainPic.push_back(first);
	}
}

void CMyPainter::MoveToRight(int nValue)
{
	for (int i = 0; i < m_vContainPic.size(); i++)
	{
		(m_vContainPic[i])->RightMove();
	}


	int nSize = m_vContainPic.size();
	if (nSize)
	{
		int nMaxLeft = 2 * (PIC_WIDTH);
		if ((m_vContainPic[0])->GetLeft() >= PIC_WIDTH)
		{
			this->FirstAndLastSwap(true);
			(m_vContainPic[0])->SetLeft(0);
		}
	}
}

void CMyPainter::MoveToLeft(int nValue)
{
	for (int i = 0; i < m_vContainPic.size(); i++)
	{
		(m_vContainPic[i])->LeftMove();
	}
	int nSize = m_vContainPic.size();
	if (nSize)
	{
		int nMaxLeft = 2 * (-PIC_WIDTH);
		if ((m_vContainPic[0])->GetLeft() < nMaxLeft)
		{
			this->FirstAndLastSwap(false);
			(m_vContainPic[nSize-1])->SetLeft(2*PIC_WIDTH);
		}
	}
}