#pragma once
#include"Obj.h"
class Shell :public Obj
{
public:
	Shell();
	~Shell();
	void Show(CDC* pDC);
	//void SetDir(double dDir) { m_dDir = dDir; }//�����ڵ����򣬻���
	//void GetPos(int& x, int& y);//��ȡ����
	void UpdatePos();

public:
	void SetInitialPos(int x, int y) { m_x = m_x0 = x, m_y = m_y0 = y; };
	void SetInitialTime(__int64 nIniTime) { m_nFireTime = nIniTime; };

protected:
	//double m_dDir = 0.0;//direction 0~PI
	//int m_x = 0, m_y = 0;//center position
	//int m_nSize = 10;//�ߴ�
	//double m_dSpeed = 100;//�ڵ��ٶ�
	//
	//
	int m_x0, m_y0;//����λ��
	__int64 m_nFireTime;//���ڳ�ʼʱ��  GetTickCoumt64()��ȡ��ǰʱ��

public:
	//CImage m_imgShell;
	static CImage m_img;
	CString strImgPathName = GetExePath() + L"sourse\\shell.jpg";
};
//�̳У���ȡ����ʽ��
