
// labaa2Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно Clabaa2Dlg
class Clabaa2Dlg : public CDialogEx
{
// Создание
public:
	Clabaa2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABAA2_DIALOG };
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
	CSliderCtrl Slyder;
	CString result;
	CString Metod_Dihotomii(double a, double b, int f);
	CString Horda(double a, double b, int f);
	CString Newton(double a, double b, int f);
	int index;
	double Func(double a, int f);
	double a = 0, b;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	double e;
	afx_msg void OnEnChangeEdit5();
};
