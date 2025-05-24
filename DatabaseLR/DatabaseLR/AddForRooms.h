#pragma once
#include "afxdialogex.h"
class AddForRooms : public CDialogEx
{
	DECLARE_DYNAMIC(AddForRooms)

public:
	AddForRooms(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~AddForRooms();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FOR_ROOMS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString id_room;
	CString room_status;
};

