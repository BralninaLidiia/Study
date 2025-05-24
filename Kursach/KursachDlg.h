
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
	afx_msg void OnBnClickedButton1();
	double D1=72;//диаметр цилиндра
	double D2=58;//диаметр отверстия в главном цилиндре
	double H1=110;//высота главного цилиндра
	double H2=95;//высота недоуха
	double L1;//расстояние на которое выдавливается недоухо, на чертеже обозначено как L2
	double L2=50;//ширина недоуха
	double L3=20;//ширина выреза на крышке цилиндра 
	double R3=25;//радиус для выреза в цилиндре сверху
	double L4;//выдавливание полуцилиндра в отрицательном направлении, на чертеже обозначено как L4
	double L5;//выдавливание полуцилиндра в положительном направлении, на чертеже обозначено как L3
	double R1=32;//радиус выреза в полуцилиндра
	double L6=90;//расстояние от оси цилиндра до оси полуцилиндра
	double H3=70;//высота ребра жесткости от платформы
	double H4=15;//высота платформы
	double L7=4;//толщина ребра жесткоости
	double L8=10;//длина платформы в отрицательном направлении
	double L9=60;//длина платформы в полижительном направлении
	double L10=36;//ширина ушей
	double L11;//межосевое расстояние отвестий в ушах, на чертеже обозначено как L1
	double D3=18;//диаметр отверстий в ушах
	double R2=2.5;//радиус скругления
	double R4=11.5;//радиус отверстия в недоухе
	bool Proverka();
	
	
};
