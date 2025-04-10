#include "pch.h"
#include "cheese.h"

cheese::cheese()
{
	m_nArm = 1;

	m_imgcheese.Load(strImgPathName);
}
cheese::~cheese()
{

}

void cheese::Show(CDC* pDC)
{
	if (m_nArm > 0) {
		if (m_imgcheese.IsNull())
		{
			Obj::Show(pDC);
		}
		else
		{
			m_imgcheese.Destroy();
			m_imgcheese.Load(strImgPathName);
			pDC->SetStretchBltMode(HALFTONE);//图像缩放时可以保证显示效果良好
			CRect rctSrc(0, 0, m_imgcheese.GetWidth(), m_imgcheese.GetHeight());//图像的显示区域，这里是显示全部
			CRect rectDest(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);//
			m_imgcheese.SetTransparentColor(RGB(247, 247, 247));
			m_imgcheese.Draw(pDC->GetSafeHdc(), rectDest, rctSrc);
		}
	}
}