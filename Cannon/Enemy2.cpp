#include "pch.h"
#include "Enemy2.h"

Enemy2::Enemy2()
{
	m_nArm = 1;

	m_imgenemy2.Load(strImgPathName);
}
Enemy2::~Enemy2() {

}

void Enemy2::Show(CDC* pDC) 
{
	if (m_nArm > 0) {
		if (m_imgenemy2.IsNull())
		{
			Obj::Show(pDC);
		}
		else
		{
			m_imgenemy2.Destroy();
			m_imgenemy2.Load(strImgPathName);
			pDC->SetStretchBltMode(HALFTONE);//ͼ������ʱ���Ա�֤��ʾЧ������
			CRect rctSrc(0, 0, m_imgenemy2.GetWidth(), m_imgenemy2.GetHeight());//ͼ�����ʾ������������ʾȫ��
			CRect rectDest(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);//
			m_imgenemy2.SetTransparentColor(RGB(90, 121, 188));//
			m_imgenemy2.Draw(pDC->GetSafeHdc(), rectDest, rctSrc);
		}
	}

}
