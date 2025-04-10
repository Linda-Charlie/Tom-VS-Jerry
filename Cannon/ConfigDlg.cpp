// ConfigDlg.cpp: 实现文件
//

#include "pch.h"
#include "Cannon.h"
#include "afxdialogex.h"
#include "ConfigDlg.h"


// ConfigDlg 对话框

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG, pParent)
{

}

ConfigDlg::~ConfigDlg()
{
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
END_MESSAGE_MAP()


// ConfigDlg 消息处理程序
