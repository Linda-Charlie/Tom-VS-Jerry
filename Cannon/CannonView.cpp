
// CannonView.cpp: CCannonView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Cannon.h"
#endif

#include "CannonDoc.h"
#include "CannonView.h"
#include"random"
#include"Thread"//多线程
#include "ConfigDlg.h"
#include "CInfoFoLe.h"
#include "CLoginDlg.h"
#include "CPatternDlg.h"
#include "CWinDlg.h"
#include "CFailDlg.h"

#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib,"Winmm.lib")

CImage Shell::m_img;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCannonView

IMPLEMENT_DYNCREATE(CCannonView, CView)

BEGIN_MESSAGE_MAP(CCannonView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCannonView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_Set_Parameters, &CCannonView::OnSetParameters)
	ON_COMMAND(ID_Set_Colors, &CCannonView::OnSetColors)
	ON_COMMAND(ID_CONFIG, &CCannonView::OnConfig)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CCannonView 构造/析构

CCannonView::CCannonView() noexcept
{
	// TODO: 在此处添加构造代码
	m_rctBackground = CRect(0, 0, 800, 600);
	m_Tower.SetArea(m_rctBackground);

	/*CLoginDlg login;
	login.DoModal();
	CPatternDlg pattern;
	if (pattern.DoModal() == IDOK)
	{
		for (auto& enemy : m_vecEnemy)
		{
			enemy.SetSpeed(pattern.pat);
		}
		for (auto& enemy2 : m_vecEnemy2)
		{
			enemy2.SetSpeed(pattern.pat);
		}
		
	}*/
}

CCannonView::~CCannonView()
{
	m_bRunThread = false;
	Sleep(1000);
}

BOOL CCannonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCannonView 绘图

void CCannonView::OnDraw(CDC* pDC)
{
	CCannonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	CMemDC dc(*pDC, this);
	CDC* pMemDC = &dc.GetDC();
	CRect rct;
	GetClientRect(&rct);
	pMemDC->Rectangle(&rct);


	//绘制作战区域
	pMemDC->Rectangle(&m_rctBackground);
	CImage m_imgBck;
	CString GetBacPath;
	GetBacPath = m_Tower.GetExePath() + L"sourse\\back2.jpg";
	m_imgBck.Load(GetBacPath);
	if (!m_imgBck.IsNull())
	{
		m_imgBck.Destroy();
	    m_imgBck.Load(GetBacPath);
	    m_imgBck.Draw(pMemDC->GetSafeHdc(), m_rctBackground);
	}
	
	
	//显示炮塔//一个无所谓锁定
	m_Tower.Show(pMemDC);
	int grade = 0;
	int emynum = 40;
	int emynum2 = 60;

	m_mtxShow.lock();//锁定
	//显示炮弹
	for (auto sh : m_vecShell)
	{
		sh.Show(pMemDC);
		if (sh.m_nArm == 0)
			//m_Tower.m_grade += 1;
			grade += 1;
	}//炮弹没有产生  ...
	//显示敌人
	for (auto emy : m_vecEnemy)
	{
		emy.Show(pMemDC);
		if (emy.m_nArm == 0)
			emynum -= 1;
	}
	for (auto emy2 : m_vecEnemy2)
	{
		emy2.Show(pMemDC);
		if (emy2.m_nArm == 0)
			emynum2 -= 1;
	}
	//显示奶酪
	for (auto cheese : m_vecCheese)
	{
		cheese.Show(pMemDC);
	}
	m_mtxShow.unlock();

	
	//炮塔敌人碰撞测试
	for (auto& enemy : m_vecEnemy)
	{
		if (m_Tower && enemy)
		{
			m_Tower.Attack(enemy);
		}
	}
	for (auto& enemy2 : m_vecEnemy2)
	{
		if (m_Tower && enemy2)
		{
			m_Tower.Attack(enemy2);
		}
	}
	//炮塔奶酪碰撞测试
	for (auto& cheese : m_vecCheese)
	{
		if (m_Tower && cheese)
		{
			m_Tower.Add(cheese);
		}
	}

	//for (auto& shell : m_vecShell)
	//{
	//	for (auto& enemy : m_vecEnemy)
	//	{
	//		if (shell && enemy)
	//		{
	//			if (shell.m_nArm <= 0)
	//				m_Tower.m_grade += 1;
	//		}
	//	}
	//	for (auto& enemy2 : m_vecEnemy2)
	//	{
	//		if (shell && enemy2)
	//		{
	//			if (shell.m_nArm <= 0)
	//				m_Tower.m_grade += 1;
	//		}
	//	}
	//}
	
	//显示游戏进度
	pMemDC->TextOutW(1, 1, L"汤姆的生命值");
	pMemDC->TextOutW(1, 20, L"打败杰瑞次数");
	pMemDC->TextOutW(1, 40, L"剩余杰瑞个数");
	pMemDC->TextOutW(1, 60, L"剩余泰菲个数");
	CString cur_nArm;
	cur_nArm.Format(L"%d", m_Tower.m_nArm);
	pMemDC->TextOutW(120, 1, cur_nArm);
	CString cur_grade;
	cur_grade.Format(L"%d",grade );
	pMemDC->TextOutW(120, 20, cur_grade);
	CString cur_emy1;
	CString cur_emy2;
	cur_emy1.Format(L"%d", emynum);
	cur_emy2.Format(L"%d", emynum2);
	pMemDC->TextOutW(120, 40, cur_emy1);
	pMemDC->TextOutW(120, 60, cur_emy2);
	
	if (m_Tower.m_nArm <= 0 || emynum == 0 && emynum2 == 0 )
	{
		Shell sh;
		sh.Sound(L"Fail.wav");
		KillTimer(1002);
		KillTimer(1003);
		KillTimer(1004);
		m_bRunThread = false;
		Sleep(1000);
		//AfxMessageBox(L"Tom was defeated！");
		CFailDlg fail;
		fail.DoModal();
		exit(0);
	}
	if (grade == 50)
	{
		Shell sh;
		sh.Sound(L"Win.wav");
		KillTimer(1002);
		KillTimer(1003);
		KillTimer(1004);
		m_bRunThread = false;
		Sleep(1000);
		//AfxMessageBox(L"Tom is winner！");
		CWinDlg win;
		win.DoModal();
		exit(0);
	}
	/*else
	{
		KillTimer(1002);
		KillTimer(1003);
		KillTimer(1004);
		m_bRunThread = false;
		Sleep(1000);
		AfxMessageBox(L"原来猫和老鼠注定和平共处！");
		exit(0);
	}*/
}


// CCannonView 打印


void CCannonView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCannonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCannonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCannonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCannonView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCannonView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCannonView 诊断

#ifdef _DEBUG
void CCannonView::AssertValid() const
{
	CView::AssertValid();
}

void CCannonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCannonDoc* CCannonView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCannonDoc)));
	return (CCannonDoc*)m_pDocument;
}
#endif //_DEBUG


// CCannonView 消息处理程序


BOOL CCannonView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;

	return CView::OnEraseBkgnd(pDC);
}

//炮塔键盘操作
void CCannonView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//ASSERT(FALSE);//当他相应的时候程序就崩了
	int x, y;
	m_Tower.GetPos(x, y);
	switch (nChar)
	{
	case 'a':
	case 'A':
		//m_Tower.AddDir(3.14159 / 10.0);
		if (x - 70 > m_rctBackground.left)
			m_Tower.SetPos(x - 10, y);
		Invalidate(FALSE);
		break;
	case 'd':
	case 'D':
		//m_Tower.AddDir(-3.14159 / 10.0);
		if (x + 70 < m_rctBackground.right)
			m_Tower.SetPos(x + 10, y);
		Invalidate(FALSE);
		break;
	case 'w':
	case 'W':
		if (y -50 > m_rctBackground.top)
			m_Tower.SetPos(x, y - 10);
		Invalidate(FALSE);
		break;
	case 's':
	case 'S':
		if (y + 50 < m_rctBackground.bottom)
			m_Tower.SetPos(x, y + 10);
		Invalidate(FALSE);
		break;
	case 'q':
	case 'Q':
		m_Tower.AddDir(3.14159 / 10.0);
		Invalidate(FALSE);
		break;
	case 'e':
	case 'E':
		m_Tower.AddDir(-3.14159 / 10.0);
		Invalidate(FALSE);
		break;
	default:
		break;
	}


	CView::OnChar(nChar, nRepCnt, nFlags);
}

//炮塔鼠标开炮
void CCannonView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	Shell sh = m_Tower.Fire();
	m_vecShell.push_back(sh);

	//m_Tower.Fire();

	CView::OnLButtonDown(nFlags, point);
}


void CCannonView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Enemy emy;
	Enemy2 emy2;
	cheese cheese;
	CPatternDlg pattern;
	switch (nIDEvent)
	{
	case 1002:
			Invalidate(FALSE);
			break;
	case 1003:
		if (m_vecEmyPos.size() > 0) 
		{
			emy.SetDir(-M_PI_2);
			emy.SetInitialTime(GetTickCount64());
			emy.SetPos(m_vecEmyPos[m_vecEmyPos.size() - 1], 10);//
			emy.SetInitialPos(m_vecEmyPos[m_vecEmyPos.size() - 1], 10);
			emy.SetSize(60);
			emy.SetSpeed(speed);
			m_vecEmyPos.pop_back();

			m_vecEnemy.push_back(emy);
			Invalidate(FALSE);
		}
	case 1004:
		if (m_vecEmyPos2.size() > 0)
		{
			emy2.SetDir(-M_PI_2);
			emy2.SetInitialTime(GetTickCount64());
			emy2.SetPos(m_vecEmyPos2[m_vecEmyPos2.size() - 1], 10);
			emy2.SetInitialPos(m_vecEmyPos2[m_vecEmyPos2.size() - 1], 10);
			emy2.SetSize(40);
			emy2.SetSpeed(speed);
			m_vecEmyPos2.pop_back();

			m_vecEnemy2.push_back(emy2);
			Invalidate(FALSE);
		}
	case 1005:
		if (m_vecCheePosx.size() > 0 && m_vecCheePosy.size()>0 )
		{
			cheese.SetInitialTime(GetTickCount64());
			cheese.SetPos(m_vecCheePosx[m_vecCheePosx.size() - 1], m_vecCheePosy[m_vecCheePosy.size() - 1]);
			cheese.SetSize(50);
			m_vecCheePosx.pop_back();
			m_vecCheePosy.pop_back();

			m_vecCheese.push_back(cheese);
			Invalidate(FALSE);
		}
	/*case 1006:
		if (pattern.pat == difficult)
		{
			emy.SetSpeed(100);
			emy2.SetSpeed(100);
		}
	case 1007:
		if (pattern.pat == middle)
		{
			emy.SetSpeed(75);
			emy2.SetSpeed(75);
		}
	case 1008:
		if (pattern.pat == easy)
		{
			emy.SetSpeed(50);
			emy2.SetSpeed(50);
		}*/
	default:
		break;
	}
	/*if (m_Tower.m_nArm <= 0)
	{
		KillTimer(1002);
		KillTimer(1003);
		KillTimer(1004);
		m_bRunThread = false;
		Sleep(1000);
		AfxMessageBox(L"Tom was defeated！");
		exit(0);
	}*/
	


	CView::OnTimer(nIDEvent);
}


void CCannonView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	// TODO: 在此添加专用代码和/或调用基类

	CLoginDlg login;
	login.DoModal();
	CPatternDlg pattern;
	if (pattern.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		speed = pattern.pat;
	}
	

	/*SetTimer(1006, 30, NULL);
	SetTimer(1007, 30, NULL);
	SetTimer(1008, 30, NULL);*/

	SetTimer(1002, 30, NULL);

	SetTimer(1003, 1000, NULL);//
	SetTimer(1004, 1000, NULL);
	SetTimer(1005, 1000000, NULL);

	//生成随机敌人40个和60个
	int min = m_rctBackground.left + 1, max = m_rctBackground.right - 1;
	std::random_device seed;//硬件生成随机数种子
	std::ranlux48 engine(seed());//
	std::uniform_int_distribution<>distrib(min, max);//
	int xPos; int xPos2; int xPos3;
	for (int i = 0; i < 40; i++) {
		xPos = distrib(engine);//
		m_vecEmyPos.push_back(xPos);
	}
	for (int i = 0; i < 60; i++) {
		xPos2 = distrib(engine);//
		m_vecEmyPos2.push_back(xPos2);
	}
	//生成随机奶酪50个
	for (int i = 0; i < 50; i++)
	{
		xPos3 = distrib(engine);
		m_vecCheePosx.push_back(xPos3);
	}
	int miny = m_rctBackground.top + 300, maxy = m_rctBackground.bottom - 1;
	std::random_device seedy;
	std::ranlux48 enginey(seedy());
	std::uniform_int_distribution<>distriby(miny, maxy);
	int yPos;
	for (int i = 0; i < 50; i++)
	{
		yPos = distriby(enginey);
		m_vecCheePosy.push_back(yPos);
	}

	

	//读取shell enemy的图像
	//Obj obj;
	//Shell::m_img.Load(obj.GetExePath() + L"shell.jpg");
	//m_imgShell.Load(GetShellPath);

	//多线程
	std::thread thRun(ThreadRun, this);
	thRun.detach();

	//游戏背景音乐
	CString strbackmusic;
	strbackmusic = m_Tower.GetExePath() + L"sourse\\Back.wav";
	PlaySound(strbackmusic, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//多线程碰撞测试//资源竞争触发断点
void CCannonView::ThreadRun(CCannonView* pThis)
{
	pThis->m_bRunThread = true;
	for (;;)
	{
		if (pThis->m_bRunThread == false)
			break;
		pThis->m_mtxShow.lock();
		for (auto& shell : pThis->m_vecShell)
		{
			if (shell.m_nArm <= 0)
				continue;
			shell.UpdatePos();//更新位置
			for (auto& enemy : pThis->m_vecEnemy)
			{
				if (enemy.m_nArm <= 0)
					continue;
				enemy.UpdatePos();

				//shell.IsOverlap(enemy);

				if (shell && enemy)
				{
					shell.Attack(enemy);
					//enemy.Sound(L"add.wav");
					
				}
			}
			for (auto& enemy2 : pThis->m_vecEnemy2)
			{
				if (enemy2.m_nArm <= 0)
					continue;
				enemy2.UpdatePos();

				//shell.IsOverlap(enemy);

				if (shell && enemy2)
				{
					shell.Attack(enemy2);
					//enemy2.Sound(L"add.wav");
				}
			}
		}
		//越界
		for (auto& obj : pThis->m_vecShell)
		{
			if (obj.m_nArm <= 0)
				continue;
			if (!obj.PtInRect(pThis->m_rctBackground))
				obj.m_nArm = 0;
		}
		for (auto& obj : pThis->m_vecEnemy)
		{
			if (obj.m_nArm <= 0)
				continue;
			obj.UpdatePos();
			if (!obj.PtInRect(pThis->m_rctBackground))
			{
				obj.m_nArm = 0;
				//obj.Sound(L"hit.wav");
			}
		}
		for (auto& obj : pThis->m_vecEnemy2)
		{
			if (obj.m_nArm <= 0)
				continue;
			obj.UpdatePos();
			if (!obj.PtInRect(pThis->m_rctBackground))
			{
				obj.m_nArm = 0;
				//obj.Sound(L"hit.wav");
			}
		}

		//删除m_nArm<=0
		pThis->m_mtxShow.unlock();

		Sleep(10);
	}
}


//对话框
void CCannonView::OnSetParameters()
{
	// TODO: 在此添加命令处理程序代码
	CString strFilePathName;
	CFileDialog dlg(TRUE);//重点/false是保存
	if (dlg.DoModal()==IDOK)//确定点的是确定ok，否则默认你取消后悔
	{
		strFilePathName = dlg.GetPathName();
		CStdioFile fl;
		if (fl.Open(strFilePathName,CFile::modeRead))
		{
			CString str;
			for (;;)
			{
				fl.ReadString(str);//按行读/writestring
				if (str.IsEmpty())
					break;
				if (str.Find(L"CANNON_SPEED") >= 0)
				{
					TCHAR cKeyWord[64];
					int nSpeed = 0;
					_stscanf_s(str, L"%s %d", cKeyWord, 64, &nSpeed);//scanf,fscanf,sscanf/printf,fprintf,sprintf
					m_Tower.SetSpeed(nSpeed);
				}
				else if (str.Find(L"CANNON_ARM") >= 0)
				{
					TCHAR cKeyWord[64];
					int nArm = 0;
					_stscanf_s(str, L"%s %d", cKeyWord, 64, &nArm);//scanf,fscanf,sscanf/printf,fprintf,sprintf
					//m_Tower.SetSpeed(nArm);
				}
			}
			fl.Close();
		}
		
	}
	CFolderPickerDialog fDlg;//打开一个目录
}


void CCannonView::OnSetColors()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		ASSERT(FALSE);
	}

	CFontDialog fntDlg;
	if (fntDlg.DoModal() == IDOK)
	{
		ASSERT(FALSE);
	}

	//CFileDialog fl();
}


void CCannonView::OnConfig()
{
	// TODO: 在此添加命令处理程序代码
	ConfigDlg dlg;
	if (dlg.DoModal() == IDOK)
	{

	}
}

//炮塔鼠标自由化
void CCannonView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int x, y;
	m_Tower.GetPos(x, y);
	if (point.x >= m_rctBackground.left && point.x <= m_rctBackground.right && point.y <= m_rctBackground.bottom && point.y  >= m_rctBackground.top)
	{
		m_Tower.SetPos(point.x, point.y);
	}
	Invalidate(FALSE);

	
	CView::OnMouseMove(nFlags, point);
}


BOOL CCannonView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (zDelta)
	{
	case 120:
		m_Tower.AddDir(3.14159 / 10.0);
		Invalidate(FALSE);
		break;
	case -120:
		m_Tower.AddDir(-3.14159 / 10.0);
		Invalidate(FALSE);
		break;
	default:
		break;
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


