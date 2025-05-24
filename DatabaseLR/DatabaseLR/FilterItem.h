#pragma once
#include "afxdialogex.h"
class FilterItem : public CDialogEx
{
	DECLARE_DYNAMIC(FilterItem)

public:
	FilterItem(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~FilterItem();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTER_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString atribut;
	CString value;

};

