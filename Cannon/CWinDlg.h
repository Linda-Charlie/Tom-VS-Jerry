#pragma once
#include "afxdialogex.h"
#include "Obj.h"

// CWinDlg 对话框

class CWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWinDlg)

public:
	CWinDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CWinDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Win };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	afx_msg void OnPaint();
	CStatic Win;
};
