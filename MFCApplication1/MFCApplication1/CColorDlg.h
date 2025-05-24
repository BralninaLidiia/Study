#pragma once
#include "afxdialogex.h"

class CMFCApplication1View;
// Диалоговое окно CColorDlg

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CColorDlg();

	CMFCApplication1View* pView;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CMFCColorButton m_ColorCtrl;
	CMFCColorButton m_Color_SinCtrl;
	CMFCColorButton m_Color_ShtrihCtrl;
};
