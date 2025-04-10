#include "pch.h"
#include "Obj.h"

#include<MMSystem.h>
#pragma comment(lib,"winmm.lib")

bool Obj::IsOverlap(Obj* pObjA, Obj* pObjB)
{
	double dDis = 0;
	double dx, dy;
	dx = pObjA->m_x - pObjB->m_x;
	dy = pObjA->m_y - pObjB->m_y;
	dDis = sqrt(dx * dx + dy * dy);
	double dThread = 0.0;
	dThread = pObjA->m_nSize/2.0 + pObjB->m_nSize/2.0;// /2.0 半径相加
	if (dThread > dDis)//距离小于阈值
		return true;
	else
		return false;
}//判断碰撞测试
//重载函数名相同，参数不同;运算符重载函数名改了，参数相同//重载程序更漂亮
bool Obj::operator &&(Obj& obj)
{
	return IsOverlap(this, &obj);
}
bool Obj::IsOverlap(Obj& obj)
{
	return IsOverlap(this, &obj);
}

void Obj::Attack(Obj& obj)
{
	int nArm = m_nArm;
	m_nArm -= obj.m_nArm;
	obj.m_nArm -= nArm;
	if (m_nArm < 0)
		m_nArm = 0;
	if (obj.m_nArm < 0)
		obj.m_nArm = 0;
}
void Obj::Add(Obj& obj)
{
	int nArm = m_nArm;
	m_nArm += obj.m_nArm;
	obj.m_nArm -= nArm;
	if (m_nArm < 0)
		m_nArm = 0;
	if (obj.m_nArm < 0)
		obj.m_nArm = 0;
}


bool Obj::PtInRect(RECT rct)
{
	if (m_x<rct.left || m_x>rct.right || m_y<rct.top || m_y>rct.bottom)
		return false;
	else
		return true;
}

void Obj::Sound(CString strFileName)
{
	//如何获得exe所在目录
	CString strPath = GetExePath();

	CString strFilePathName = strPath + L"sourse\\" + strFileName;
	PlaySound(strFilePathName, 0, SND_FILENAME | SND_ASYNC);
}

CString Obj::GetExePath()
{
	CString strPath;
	TCHAR cPath[1024];
	GetModuleFileName(NULL, cPath, 1024);
	strPath = cPath;
	strPath = strPath.Left(strPath.ReverseFind('\\') + 1);
	return strPath;
}