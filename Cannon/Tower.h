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
	void Show(CDC* pDC);//������ʾ���ǲ�ͬ��
	bool SetArea(CRect rctBk);//������ս����
	void AddDir(double dDirAdd) { m_dDir += dDirAdd; }
	void GetPos(int& x, int& y) { x = m_x, y = m_y; };//��ȡ���� �븸�ຯ����һ��
	Shell Fire();//���beep(Ƶ�ʣ�ʱ����//����һ���ڵ�

	CString strImgPathName = GetExePath() + L"sourse\\tower.png";
	CImage m_img;
	CRect m_rctBk;//area

protected:


	
	
private:

};

