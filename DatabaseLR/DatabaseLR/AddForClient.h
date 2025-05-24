#pragma once
#include "afxdialogex.h"
class AddForClient : public CDialogEx
{
	DECLARE_DYNAMIC(AddForClient)

public:
	AddForClient(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~AddForClient();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FOR_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString id_client;
	CString firstname;
	CString lastname;
	CString patronymic;
};
