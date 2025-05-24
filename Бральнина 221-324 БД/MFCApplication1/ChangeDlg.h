#pragma once
#include "afxdialogex.h"


// Диалоговое окно CChangeDlg

class CChangeDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangeDlg)

public:
	CChangeDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CChangeDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString id_string;
	CString atribut;
	CString value;
	afx_msg void OnBnClickedOk();
};
