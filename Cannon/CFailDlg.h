#pragma once
#include "afxdialogex.h"


// CFailDlg 对话框

class CFailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFailDlg)

public:
	CFailDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFailDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Fail };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	afx_msg void OnPaint();
};
