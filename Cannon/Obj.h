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
	};//显示
	virtual void SetDir(double dDir) { m_dDir = dDir; };//设置方向，弧度
	virtual void GetPos(int& x, int& y) { x = 0, y = 0; };

	virtual void SetPos(int x, int y) { m_x = x, m_y = y; };
	virtual void SetSize(int nSize) { m_nSize = nSize; };
	virtual void SetSpeed(int dSpeed) { m_dSpeed = dSpeed; };

	static bool IsOverlap(Obj* pObjA, Obj* pObjB);//static该成员变量不与  相关
	virtual bool Obj::IsOverlap(Obj& obj);
	virtual bool Obj::operator &&(Obj& obj);//作为成员变量，只需要一个参数，类自己作为一个参数

	void Attack(Obj& obj);
	void Add(Obj& obj);
	void SetSpeed(double dSpeed) { m_dSpeed = dSpeed; };
	bool PtInRect(RECT rct);//判断一个点是否离开方框 离开 消失
	void Sound(CString strFileName);//play sound
	CString GetExePath();
protected:
	double m_dDir = 0.0;//direction 0~PI
	int m_nSize = 10;
	int m_x = 0, m_y = 0;//center position
	double m_dSpeed = 0.0;//速度

public:
	int m_nArm = 1;//生命力/攻击力

	//CImage* m_pImg = nullptr;
};

//bool operator &&(Obj& a, Obj& b);//
