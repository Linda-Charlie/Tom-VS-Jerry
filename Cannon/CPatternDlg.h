#pragma once
#include "afxdialogex.h"


// CPatternDlg 对话框

class CPatternDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPatternDlg)

public:
	CPatternDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPatternDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PATTERN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDiff();
	afx_msg void OnBnClickedButtonMiddle();
	afx_msg void OnBnClickedButtonEasy();
	int pat;
};
