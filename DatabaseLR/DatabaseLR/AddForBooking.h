#pragma once
#include "afxdialogex.h"
class AddForBooking : public CDialogEx
{
	DECLARE_DYNAMIC(AddForBooking)

public:
	AddForBooking(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~AddForBooking();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FOR_BOOKING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString id_booking;
	CString id_client;
	CString check_in_date;
	CString eviction_date;
	CString cost;
};

