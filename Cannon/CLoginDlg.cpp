// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Cannon.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "CInfoFoLe.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_START, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_user);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_user = TEXT("汤姆");
	m_pwd = TEXT("31095");

	UpdateData(FALSE);//内容更新到对应控件


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//更新控件数据到数据区
	CInfoFoLe file;
	CString user, pwd;
	user = TEXT("汤姆");
	pwd = TEXT("31095");

	if (m_user == user)
	{
		if (m_pwd != pwd)
		{
			MessageBox(TEXT("密码错误"));
			m_user.Empty();
			m_pwd.Empty();
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
	else
	{
		MessageBox(TEXT("用户不存在"));
		m_user.Empty();
		m_pwd.Empty();
	}
	
}


void CLoginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
