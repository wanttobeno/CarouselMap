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

void MyDragImage(Gdiplus::Graphics &graphics, Gdiplus::Image* pImage,Gdiplus::Rect& rect)
{
	graphics.DrawImage(pImage, rect);
}

#define  PIC_MID_WIDTH  302
#define  PIC_MID_HEIGHT 144

#define  PIC_BIG_WIDTH  385
#define  PIC_BIG_HEIGHT 183

#define  PIC_WIDTH 288


// 1秒24帧,修改这段数据达到阻尼动画效果
int g_Pic0_2_Left[] = { 00, 06, 12, 18, 24, 30, 35, 40, 45, 49, /**/53, 57, 61, 65, 68, 71, 74, 77, 80, 83, 86,
89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 98, 98, 98 };

// 前10个2梯度
int g_Pic0_2_Top[] = { 50, 48, 46, 44, 42, 40, 38, 36, 34, 32,/**/31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 11, 11, 11 };

int g_Pic1_Width[] = { 302, 306, 310, 314, 318, 322, 326, 330, 334, 338,/**/ 340, 342, 346, 348, 350, 352, 354, 356, 358, 360, 362,
364, 366, 368, 370, 372, 374, 376, 378, 380, 382, 384, 384, 385 };

// 前10个2梯度
int g_Pic1_Hight[] = { 144, 146, 148, 150, 152, 154, 156, 158, 160, 162,/**/ 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 
174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 183, 183, 183 };


///////////////////////////
// 98~288
int g_Pic2_X[] = { 98, 110, 120, 130, 140, 150, 160, 170, 180, 190,/**/195, 200, 205, 210, 215, 220, 225, 230, 235, 240, 250,
255, 260, 265, 270, 274, 278, 282, 284, 286, 288, 288, 288, 288 };

int g_Pic2_2_Buttom[] = { 11, 13, 15, 17, 19, 21, 23, 25, 27, 29,/**/30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50, 50, 50 };

int g_Width2Small[] = { 385, 381, 377, 373, 369, 365, 361, 357, 353, 349,/**/ 347, 345, 343, 341, 339, 337, 335, 333, 331, 329, 327,
325, 323, 320, 318, 316, 314, 312, 310, 308, 306, 304, 304, 302 };


int g_Height2Small[] = { 183, 181, 179, 177, 175, 173, 171, 169, 167, 165,/**/ 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154,
153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 144, 144, 144 };


extern bool g_bAnimat;
extern int g_animatCount;

void CMyPainter::Painter(HDC dc)
{
	if (m_vContainPic.empty())
		return;
	Gdiplus::Graphics graphics(dc);

	if (g_bAnimat)
	{
		// 动画分左右模式
		int nArrSize1 = sizeof(g_Pic0_2_Left) / sizeof(int);
		int nArrSize2 = sizeof(g_Pic0_2_Top) / sizeof(int);
		int nArrSize3 = sizeof(g_Pic1_Hight) / sizeof(int);
		int nArrSize4 = sizeof(g_Pic1_Width) / sizeof(int);
		if (m_bRightMove)
		{
			if (g_animatCount > nArrSize1 - 1)
			{
				// 动画结束
				Gdiplus::Rect rect3(0, g_Pic0_2_Top[0], PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[0])->GetImage(), rect3);

				// 右图
				Gdiplus::Rect rect2(g_Pic2_X[nArrSize1 - 1], g_Pic2_2_Buttom[nArrSize1 - 1], g_Width2Small[nArrSize1 - 1], g_Height2Small[nArrSize1 - 1]);
				MyDragImage(graphics, (m_vContainPic[2])->GetImage(), rect2);

				// 中间图
				Gdiplus::Rect rect1(g_Pic0_2_Left[nArrSize1 - 1], g_Pic0_2_Top[nArrSize1 - 1], g_Pic1_Width[nArrSize1 - 1], g_Pic1_Hight[nArrSize1 - 1]);
				MyDragImage(graphics, (m_vContainPic[1])->GetImage(), rect1);
			}
			else
			{
				// 第三张右移
				Gdiplus::Rect rect2(g_Pic2_X[g_animatCount] + 288, 50, PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[2])->GetImage(), rect2);

				// 最后一张图，开始出现
				Gdiplus::Rect rectLast(g_Pic2_X[g_animatCount] - 288, 50, PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[m_vContainPic.size() - 1])->GetImage(), rectLast);


				// 中间图移动到右边
				Gdiplus::Rect rect1(g_Pic2_X[g_animatCount], g_Pic2_2_Buttom[g_animatCount], g_Width2Small[g_animatCount], g_Height2Small[g_animatCount]);
				MyDragImage(graphics, (m_vContainPic[1])->GetImage(), rect1);


				// 第一张图右移
				Gdiplus::Rect rect0(g_Pic0_2_Left[g_animatCount], g_Pic0_2_Top[g_animatCount], g_Pic1_Width[g_animatCount], g_Pic1_Hight[g_animatCount]);
				MyDragImage(graphics, (m_vContainPic[0])->GetImage(), rect0);

				//wchar_t buf[128] = { 0 };
				//swprintf(buf, L"绘制动画%2d  X:%d  Y:%d  R:%d  B: %d || W:%d H:%d \n", g_animatCount, rect1.GetLeft(), rect1.GetTop(), rect1.GetRight(), rect1.GetBottom(), rect1.Width, rect1.Height);
				//::OutputDebugString(buf);

				g_animatCount++;
				if (g_animatCount >= nArrSize1)
				{
					this->MoveToRight(288);
				}
			}
		}
		else
		{
			int nIndex = nArrSize1 - g_animatCount -1;
			if (g_animatCount > nArrSize1 - 1)
			{
				// 动画结束
				Gdiplus::Rect rect3(0, g_Pic0_2_Top[0], PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[0])->GetImage(), rect3);

				// 右图
				Gdiplus::Rect rect2(g_Pic2_X[nArrSize1 - 1], g_Pic2_2_Buttom[nArrSize1 - 1], g_Width2Small[nArrSize1 - 1], g_Height2Small[nArrSize1 - 1]);
				MyDragImage(graphics, (m_vContainPic[2])->GetImage(), rect2);

				// 中间图
				Gdiplus::Rect rect1(g_Pic0_2_Left[nArrSize1 - 1], g_Pic0_2_Top[nArrSize1 - 1], g_Pic1_Width[nArrSize1 - 1], g_Pic1_Hight[nArrSize1 - 1]);
				MyDragImage(graphics, (m_vContainPic[1])->GetImage(), rect1);
			}
			else
			{
				// 第1张左移
				Gdiplus::Rect rectLast(g_Pic2_X[nIndex] - 288, 50, PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[0])->GetImage(), rectLast);

				// 中间图左移
				Gdiplus::Rect rect0(g_Pic0_2_Left[nIndex], g_Pic0_2_Top[nIndex], g_Pic1_Width[nIndex], g_Pic1_Hight[nIndex]);
				MyDragImage(graphics, (m_vContainPic[1])->GetImage(), rect0);

				// 第4张左移, 最后几帧移动过快
				Gdiplus::Rect rect2(g_Pic2_X[nIndex] + 288, 50, PIC_MID_WIDTH, PIC_MID_HEIGHT);
				MyDragImage(graphics, (m_vContainPic[3])->GetImage(), rect2);

				// 右边移动到中间
				Gdiplus::Rect rect1(g_Pic2_X[nIndex], g_Pic2_2_Buttom[nIndex], g_Width2Small[nIndex], g_Height2Small[nIndex]);
				MyDragImage(graphics, (m_vContainPic[2])->GetImage(), rect1);

				//wchar_t buf[128] = { 0 };
				//swprintf(buf, L"绘制动画%2d  X:%d  Y:%d  R:%d  B: %d || W:%d H:%d \n", nIndex, rect1.GetLeft(), rect1.GetTop(), rect1.GetRight(), rect1.GetBottom(), rect1.Width, rect1.Height);
				//::OutputDebugString(buf);
				g_animatCount++;
				if (g_animatCount >= nArrSize1)
				{
					this->MoveToLeft(288);
				}
			}
		}
		return;
	}
	else
	{
		// 动画结束，固定绘图
		int nArrSize1 = sizeof(g_Pic0_2_Left) / sizeof(int);
		Gdiplus::Rect rect3(0, g_Pic0_2_Top[0], PIC_MID_WIDTH, PIC_MID_HEIGHT);
		MyDragImage(graphics, (m_vContainPic[0])->GetImage(), rect3);
		// 右图
		Gdiplus::Rect rect2(g_Pic2_X[nArrSize1 - 1], g_Pic2_2_Buttom[nArrSize1 - 1], g_Width2Small[nArrSize1 - 1], g_Height2Small[nArrSize1 - 1]);
		MyDragImage(graphics, (m_vContainPic[2])->GetImage(), rect2);
		// 中间图
		Gdiplus::Rect rect1(g_Pic0_2_Left[nArrSize1 - 1], g_Pic0_2_Top[nArrSize1 - 1], g_Pic1_Width[nArrSize1 - 1], g_Pic1_Hight[nArrSize1 - 1]);
		MyDragImage(graphics, (m_vContainPic[1])->GetImage(), rect1);
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
		if ((m_vContainPic[0])->GetLeft() <= PIC_WIDTH)
		{
			this->FirstAndLastSwap(false);
			(m_vContainPic[nSize-1])->SetLeft(2*PIC_WIDTH);
		}
	}
}

void CMyPainter::SetLeftMove()
{
	m_bRightMove = false;
}

void CMyPainter::SetRightMove()
{
	m_bRightMove = true;
}