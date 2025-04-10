#pragma once
#include"Obj.h"
class Shell :public Obj
{
public:
	Shell();
	~Shell();
	void Show(CDC* pDC);
	//void SetDir(double dDir) { m_dDir = dDir; }//设置炮弹方向，弧度
	//void GetPos(int& x, int& y);//获取坐标
	void UpdatePos();

public:
	void SetInitialPos(int x, int y) { m_x = m_x0 = x, m_y = m_y0 = y; };
	void SetInitialTime(__int64 nIniTime) { m_nFireTime = nIniTime; };

protected:
	//double m_dDir = 0.0;//direction 0~PI
	//int m_x = 0, m_y = 0;//center position
	//int m_nSize = 10;//尺寸
	//double m_dSpeed = 100;//炮弹速度
	//
	//
	int m_x0, m_y0;//开炮位置
	__int64 m_nFireTime;//开炮初始时刻  GetTickCoumt64()获取当前时间

public:
	//CImage m_imgShell;
	static CImage m_img;
	CString strImgPathName = GetExePath() + L"sourse\\shell.jpg";
};
//继承（提取公因式）
