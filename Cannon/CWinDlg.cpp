// CWinDlg.cpp: 实现文件
//

#include "pch.h"
#include "Cannon.h"
#include "afxdialogex.h"
#include "CWinDlg.h"


// CWinDlg 对话框

IMPLEMENT_DYNAMIC(CWinDlg, CDialogEx)

CWinDlg::CWinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Win, pParent)
{

}

CWinDlg::~CWinDlg()
{
}

void CWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_WIN, Win);
}


BEGIN_MESSAGE_MAP(CWinDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWinDlg 消息处理程序


void CWinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y,m_hIcon);
	}
	else
	{
		//加载位图
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1);

		//选入DC
		CClientDC cdc(this);
		CDC comdc;
		comdc.CreateCompatibleDC(&cdc);
		comdc.SelectObject(&bitmap);

		//生成BITMAP
		BITMAP bit;
		bitmap.GetBitmap(&bit);

		//客户区域
		CRect rect;
		GetClientRect(rect);

		//用客户区的DC绘制所生成的BITMAP，并适应为窗口大小
		cdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &comdc, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);
	}

}
