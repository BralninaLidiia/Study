
// KursachDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CKursachDlg
class CKursachDlg : public CDialogEx
{
// Создание
public:
	CKursachDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KURSACH_DIALOG };
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
	void Start();
	void SelAndFocus(CEdit& edit)
	{
		edit.SetFocus();
		edit.SetSel(0, -1, false);
	};
	bool Proverka();
	afx_msg void OnBnClickedButton1();
	double D_1;
	double D_2;
	double D_3;
	double H_1;
	double H_2;
	double L;
	double Alfa;
	double PI = 3.14159265358979323846;
	int Count;
	double R1;
	double R2;
	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	CEdit edit4;
	CEdit edit5;
	CEdit edit6;
	CEdit edit7;
	CEdit edit8;
	CEdit edit9;
	CEdit edit10;
};
