#pragma once
#include "afxdialogex.h"


// Диалоговое окно CAddForClientDlg

class CAddForClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddForClientDlg)

public:
	CAddForClientDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAddForClientDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FOR_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int id_client;
	CString firstname;
	CString lastname;
	CString patronymic;
	afx_msg void OnBnClickedOk();
};
