#pragma once
#include "afxdialogex.h"


// Диалоговое окно CAddForBookingDlg

class CAddForBookingDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddForBookingDlg)

public:
	CAddForBookingDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAddForBookingDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FOR_BOOKING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int id_booking;
	int id_client;
	CString check_in_date;
	CString eviction_date;
	double cost;
	afx_msg void OnBnClickedOk();
};
