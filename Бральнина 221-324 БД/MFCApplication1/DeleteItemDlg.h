#pragma once
#include "afxdialogex.h"


// Диалоговое окно CDeleteItemDlg

class CDeleteItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteItemDlg)

public:
	CDeleteItemDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CDeleteItemDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELET_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString id_item;
	afx_msg void OnBnClickedOk();
};
