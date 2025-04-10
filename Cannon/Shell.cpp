#include "pch.h"
#include "Shell.h"

Shell::Shell()
{
	m_nSize = 60, m_dSpeed = 1000;
	m_nArm = 1;

	if (!m_img.IsNull())
	{
		m_img.Destroy();
	}
	m_img.Load(strImgPathName);
}
Shell::~Shell()
{

}

void Shell::Show(CDC* pDC)
{
	/*GetPos(m_x, m_y);

	pDC->Ellipse(m_x - m_nSize / 2, m_y - m_nSize / 2, 
		         m_x + m_nSize / 2, m_y + m_nSize / 2);*/

	UpdatePos();
	
	if (m_nArm > 0) {
		if (m_img.IsNull()) {
			Obj::Show(pDC);
		}
		else {
			pDC->SetStretchBltMode(HALFTONE);
			CRect rctSrc(0, 0, m_img.GetWidth(), m_img.GetHeight());
			CRect rectDest(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);
			m_img.SetTransparentColor(RGB(255, 218, 210));
			m_img.Draw(pDC->GetSafeHdc(), rectDest);
		}
	}
}

/*void Shell::GetPos(int& x, int& y)
{
	__int64 nCurrentTime = GetTickCount64();//获取当前时间
	__int64 nGap = nCurrentTime - m_nFireTime;//时间差，炮弹飞翔时间
	m_x = (nGap / 1000.0) * m_dSpeed * cos(m_dDir) + m_x0;//
	m_y = m_y0 - (nGap / 1000.0) * m_dSpeed * sin(m_dDir);//有问题得改
}*/

void Shell::UpdatePos()
{
	__int64 nCurrentTime = GetTickCount64();//获取当前时间
	__int64 nGap = nCurrentTime - m_nFireTime;//时间差，炮弹飞翔时间
	m_x = (nGap / 1000.0) * m_dSpeed * cos(m_dDir) + m_x0;//
	m_y = m_y0 - (nGap / 1000.0) * m_dSpeed * sin(m_dDir);
}