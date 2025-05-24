#pragma once
#include "afxdialogex.h"


// Диалоговое окно CFilterItemDlg

class CFilterItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterItemDlg)

public:
	CFilterItemDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CFilterItemDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTER_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString atribut;
	CString value;
	afx_msg void OnBnClickedOk();
};
