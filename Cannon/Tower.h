#pragma once
/************
*2022/03/30   Create...
*2022/
*
* 
* 
***********/
#define _USE_MATH_DEFINES
#include"math.h"
#include"Shell.h"
#include"obj.h"

class Tower :public Obj
{
public:
	Tower() ;
	~Tower() ;
	void Show(CDC* pDC);//子类显示的是不同的
	bool SetArea(CRect rctBk);//设置作战场景
	void AddDir(double dDirAdd) { m_dDir += dDirAdd; }
	void GetPos(int& x, int& y) { x = m_x, y = m_y; };//获取坐标 与父类函数不一样
	Shell Fire();//射击beep(频率，时长）//创建一个炮弹

	CString strImgPathName = GetExePath() + L"sourse\\tower.png";
	CImage m_img;
	CRect m_rctBk;//area

protected:


	
	
private:

};

