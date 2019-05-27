#include "stdafx.h"
#include "CarouselPic.h"

#include <gdiplus.h>

CarouselPic::CarouselPic()
{
	m_pImage = NULL;
	m_bInit = false;
	m_bSelect = false;
}

CarouselPic::~CarouselPic()
{
	unInit();
}

void CarouselPic::unInit()
{
	m_bInit = false;
	if (m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

bool CarouselPic::LoadPic(std::wstring strFile)
{
	unInit();
	m_pImage = new Gdiplus::Image(strFile.c_str());
	if (m_pImage->GetLastStatus() == Gdiplus::Status::Ok)
	{
		m_bInit = true;
		return true;
	}
	else
		return false;
}

Gdiplus::Image* CarouselPic::GetImage()
{
	if (m_bInit)
	{
		return m_pImage;
	}
	return NULL;
}

unsigned int CarouselPic::GetWidth()
{
	if (m_bInit)
	{
		return m_pImage->GetWidth();
	}
	return 0;
	
}

unsigned int CarouselPic::GetHeight()
{
	if (m_bInit)
	{
		return m_pImage->GetHeight();
	}
	return 0;
}

bool CarouselPic::IsSelect()
{
	return m_bSelect;
}

void CarouselPic::SetSelect(bool bSel)
{
	m_bSelect = bSel;
}

void CarouselPic::SetLeft(int nX)
{
	m_nX = nX;
}

int CarouselPic::GetLeft()
{
	return m_nX;
}

void CarouselPic::RightMove()
{
	m_nX = m_nX + 288;
}

void CarouselPic::LeftMove()
{
	m_nX = m_nX - 288;
}