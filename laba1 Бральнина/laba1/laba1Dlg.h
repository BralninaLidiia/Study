
// laba1Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно Claba1Dlg
class Claba1Dlg : public CDialogEx
{
// Создание
public:
	Claba1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABA1_DIALOG };
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
	int index_of_selected_item;
	afx_msg void OnCbnSelchangeCombo1();
	double Func(double x);
	double step_rasb;
	double verh_gr;
	double niz_gr;
	int h = 10000;
	double x;
	CString result;
};
