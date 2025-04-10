#include "pch.h"
#include "Tower.h"

Tower::Tower() {
	m_dDir = 3.14159 / 2.0;//炮管初始化方向
	m_rctBk = CRect(0, 0, 800, 600);//背景区域
	m_nSize = 100;
	m_nArm = 20;

	m_img.Load(strImgPathName);
}

Tower::~Tower() {

}

bool Tower::SetArea(CRect rctBk) {
	m_rctBk = rctBk;
	m_x = (m_rctBk.left + m_rctBk.right) / 2;
	m_y = m_rctBk.bottom;
	return true;
}

void Tower::Show(CDC* pDC) {

	
	if (m_img.IsNull())
	{
		Obj::Show(pDC);
		//m_img.Destroy();
	}
	else
	{
		pDC->SetStretchBltMode(HALFTONE);//图像缩放时可以保证显示效果良好
		CRect rctSrc(0, 0, m_img.GetWidth(), m_img.GetHeight());//图像的显示区域，这里是显示全部
		CRect rectDest(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);//
		m_img.SetTransparentColor(RGB(255, 255, 255));//
		m_img.Draw(pDC->GetSafeHdc(), rectDest, rctSrc);
	}
	CPen Pen2(PS_SOLID, 5, RGB(255, 255, 255));
	CPen* Pen02 = pDC->SelectObject(&Pen2);
	pDC->MoveTo(m_x, m_y);
	int nSize = 40;
	pDC->LineTo(m_x + nSize * cos(m_dDir), m_y - nSize * sin(m_dDir));
	
	

	//CPen Pen1(PS_SOLID, 30, RGB(176, 196, 222));
	//CPen* Pen01 = pDC->SelectObject(&Pen1);
	//pDC->Rectangle(m_x - 30, m_y - 30, m_x + 30, m_y + 30);
	//CPen Pen3(PS_SOLID, 30, RGB(119, 136, 153));
	//CPen* Pen03 = pDC->SelectObject(&Pen3);
	//pDC->Ellipse(m_x - 25, m_y - 25, m_x + 25, m_y + 25);//显示炮塔
	
	//pDC->MoveTo(m_x, m_y);
	//int nSize = 70;
	//pDC->LineTo(m_x + nSize * cos(m_dDir), m_y - nSize * sin(m_dDir));//显示炮筒

	/*pDC->Ellipse(m_x - 30, m_y - 30, m_x + 30, m_y + 30);*/
	


}

Shell Tower::Fire()
{
	Shell sh;
	//Beep(1000, 100);
	sh.SetInitialTime(GetTickCount64());
	sh.SetDir(m_dDir);
	sh.SetInitialPos(m_x, m_y);
	sh.SetSpeed(300);
	//播放声音
	//Sound(L"blast.wav");
	
	return sh;
}