
// MFCApplication6Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMFCApplication6Dlg
class CMFCApplication6Dlg : public CDialogEx
{
// Создание
public:
	CMFCApplication6Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl spisok;
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CString res;
	double Func(double x);
	CString Zolotoe_sechenie(double a, double b);
	double a = 0.001, b, e = 0.001, F = 1.6180339887, x1, x2;
};
