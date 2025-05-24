
// Laba_mnogom_optDlg.h: файл заголовка
//

#pragma once

#include <vector>
using namespace std;
// Диалоговое окно CLabamnogomoptDlg
class CLabamnogomoptDlg : public CDialogEx
{
// Создание
public:
	CLabamnogomoptDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABA_MNOGOM_OPT_DIALOG };
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
	struct Point
	{
		double x, y, z;
	};
	CArray <Point, Point> Points;
	double MSQ(double a, double b, double c, double r);
	void LinearDixotomy(double& value1, double value2, double value3, double value4, int type);
	CString Start();
	double A, B, C, R;
	//CString Otklon(double x, double y, double z);
	CString BF;
	afx_msg void OnBnClickedButton1();
};