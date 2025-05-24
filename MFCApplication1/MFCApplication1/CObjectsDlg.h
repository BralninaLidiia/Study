#pragma once
#include "afxdialogex.h"


// Диалоговое окно CObjectsDlg

class CObjectsDlg : public CDialog
{
	DECLARE_DYNAMIC(CObjectsDlg)

public:
	CObjectsDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CObjectsDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bShtrih;
	BOOL m_bSin;
	BOOL m_bKoord;
};
