/*********************
*2022-4-6 Create class Obj,Yao Lianle
* 2022-4-7 Add funcation...
*
*
*
***********************/

#pragma once
class Obj
{
public:
	//Obj(CImage* pImg) { m_pImg = pImg; };
	//void SetImg(CImage* pImg) { m_pImg = pImg; };

	virtual void Show(CDC* pDC) { 
		if(m_nArm)
			pDC->Ellipse(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);
	};//��ʾ
	virtual void SetDir(double dDir) { m_dDir = dDir; };//���÷��򣬻���
	virtual void GetPos(int& x, int& y) { x = 0, y = 0; };

	virtual void SetPos(int x, int y) { m_x = x, m_y = y; };
	virtual void SetSize(int nSize) { m_nSize = nSize; };
	virtual void SetSpeed(int dSpeed) { m_dSpeed = dSpeed; };

	static bool IsOverlap(Obj* pObjA, Obj* pObjB);//static�ó�Ա��������  ���
	virtual bool Obj::IsOverlap(Obj& obj);
	virtual bool Obj::operator &&(Obj& obj);//��Ϊ��Ա������ֻ��Ҫһ�����������Լ���Ϊһ������

	void Attack(Obj& obj);
	void Add(Obj& obj);
	void SetSpeed(double dSpeed) { m_dSpeed = dSpeed; };
	bool PtInRect(RECT rct);//�ж�һ�����Ƿ��뿪���� �뿪 ��ʧ
	void Sound(CString strFileName);//play sound
	CString GetExePath();
protected:
	double m_dDir = 0.0;//direction 0~PI
	int m_nSize = 10;
	int m_x = 0, m_y = 0;//center position
	double m_dSpeed = 0.0;//�ٶ�

public:
	int m_nArm = 1;//������/������

	//CImage* m_pImg = nullptr;
};

//bool operator &&(Obj& a, Obj& b);//
