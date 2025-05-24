#pragma once
#include "afxdialogex.h"
class CDialogChange : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogChange)

public:
	CDialogChange(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CDialogChange();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString id_string;
	CString atribut;
	CString value;
};

