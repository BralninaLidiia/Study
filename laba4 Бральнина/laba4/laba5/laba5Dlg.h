
// laba5Dlg.h: файл заголовка
//

#pragma once

// Диалоговое окно Claba5Dlg
class Claba5Dlg : public CDialogEx
{
// Создание
public:
	Claba5Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABA5_DIALOG };
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
	double MSQ(double a, double b, double r);
	void LinearDixotomy(double& value1, double value2, double value3, int type);
	CString result();
	CString Otklonenie(double x, double y);
	afx_msg void OnBnClickedButton1();
	CString answer;
	double a, b;
};
