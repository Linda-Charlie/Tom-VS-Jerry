
// CannonView.h: CCannonView 类的接口
//

#pragma once
#include"Tower.h"
#include"Shell.h"
#include"Enemy.h"
#include"Enemy2.h"
#include"cheese.h"
#include"Obj.h"
#include<vector>
#include<mutex>


class CCannonView : public CView
{
protected: // 仅从序列化创建
	CCannonView() noexcept;
	DECLARE_DYNCREATE(CCannonView)

// 特性
public:
	CCannonDoc* GetDocument() const;

// 操作
public:
	Tower m_Tower; 
	CRect m_rctBackground;

	std::vector<Shell>m_vecShell;

	std::vector<Enemy>m_vecEnemy;//敌军1
	std::vector<int>m_vecEmyPos;//敌军1出现位置x的随机数记录
	std::vector<Enemy2>m_vecEnemy2;//敌军2
	std::vector<int>m_vecEmyPos2;//敌军2出现位置x的随机数记录
	std::vector<cheese>m_vecCheese;//奶酪
	std::vector<int>m_vecCheePosx;//奶酪出现位置x的随机数记录
	std::vector<int>m_vecCheePosy;//奶酪出现位置y的随机数记录

	std::mutex m_mtxShow;
	bool m_bRunThread = false;//线程结束

	CString difficult;
	CString middle;
	CString easy;
	int speed;

	//BOOL PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);
	//CImage m_imgTower;
	//CImage m_imgEnemy;
	//CImage m_imgShell;
	//CString GetShellPath = m_Tower.GetExePath() + L"source\\shell.jpg";
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCannonView();

	static void ThreadRun(CCannonView* pThis);//多线程必须静态成员函数


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnSetParameters();
	afx_msg void OnSetColors();
	afx_msg void OnConfig();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // CannonView.cpp 中的调试版本
inline CCannonDoc* CCannonView::GetDocument() const
   { return reinterpret_cast<CCannonDoc*>(m_pDocument); }
#endif

