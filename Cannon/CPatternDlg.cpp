// CPatternDlg.cpp: 实现文件
//

#include "pch.h"
#include "Cannon.h"
#include "afxdialogex.h"
#include "CPatternDlg.h"
#include "Enemy.h"


// CPatternDlg 对话框

IMPLEMENT_DYNAMIC(CPatternDlg, CDialogEx)

CPatternDlg::CPatternDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PATTERN, pParent)
{

}

CPatternDlg::~CPatternDlg()
{
}

void CPatternDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatternDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DIFF, &CPatternDlg::OnBnClickedButtonDiff)
	ON_BN_CLICKED(IDC_BUTTON_MIDDLE, &CPatternDlg::OnBnClickedButtonMiddle)
	ON_BN_CLICKED(IDC_BUTTON_EASY, &CPatternDlg::OnBnClickedButtonEasy)
END_MESSAGE_MAP()


// CPatternDlg 消息处理程序


void CPatternDlg::OnBnClickedButtonDiff()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pat = 70;
}


void CPatternDlg::OnBnClickedButtonMiddle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pat = 50;
}


void CPatternDlg::OnBnClickedButtonEasy()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pat = 30;
}
