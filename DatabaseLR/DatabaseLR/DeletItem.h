#pragma once
#include "afxdialogex.h"
class DeletItem : public CDialogEx
{
	DECLARE_DYNAMIC(DeletItem)

public:
	DeletItem(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~DeletItem();


	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELET_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString id_item;
};

