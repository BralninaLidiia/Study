#pragma once
#include "afxdialogex.h"


// Диалоговое окно CAddForRoomsDlg

class CAddForRoomsDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddForRoomsDlg)

public:
	CAddForRoomsDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAddForRoomsDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FOR_ROOMS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int id_room;
	CString room_status;
	afx_msg void OnBnClickedOk();
};
