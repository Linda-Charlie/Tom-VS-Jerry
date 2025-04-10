#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
{
	/*CString pattern[3] = { L"difficult",L"middle",L"easy" };
	int i;
	switch (i)
	{
	case 0:
		m_dSpeed = 100;
	case 1:
		m_dSpeed = 70;
	case 2:
		m_dSpeed = 50;
	}*/
	
	m_nArm = 2;

	m_imgenemy.Load(strImgPathName);
}
Enemy::~Enemy() 
{

}

void Enemy::Show(CDC* pDC) {

	if (m_nArm > 0) {
		if (m_imgenemy.IsNull())
	    {
			Obj::Show(pDC);
	    }
	    else
	    {
			m_imgenemy.Destroy();
			m_imgenemy.Load(strImgPathName);
			pDC->SetStretchBltMode(HALFTONE);//ͼ������ʱ���Ա�֤��ʾЧ������
			CRect rctSrc(0, 0, m_imgenemy.GetWidth(), m_imgenemy.GetHeight());//ͼ�����ʾ������������ʾȫ��
			CRect rectDest(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);//
			m_imgenemy.SetTransparentColor(RGB(253,197,36));//
			//m_imgenemy.SetTransparentColor(RGB(255, 218, 210));
			m_imgenemy.Draw(pDC->GetSafeHdc(), rectDest, rctSrc);
	    }
	}
}