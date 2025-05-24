
// labaa2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "labaa2.h"
#include "labaa2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
public:
	/*afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);*/
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Диалоговое окно Clabaa2Dlg



Clabaa2Dlg::Clabaa2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABAA2_DIALOG, pParent)
	, result(_T(""))
	, e(0.001)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clabaa2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, Slyder);
	DDX_Text(pDX, IDC_EDIT1, result);
	DDX_Text(pDX, IDC_EDIT5, e);
}

BEGIN_MESSAGE_MAP(Clabaa2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT5, &Clabaa2Dlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// Обработчики сообщений Clabaa2Dlg

BOOL Clabaa2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Slyder.SetRange(0, 2);
	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Clabaa2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Clabaa2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Clabaa2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString Clabaa2Dlg::Metod_Dihotomii(double a, double b, int f)
{

	double c;
	CString str;
	while (true)
	{
		c = (a + b) / 2.0;
		if (Func(a, 0) * Func(c, 0) < 0)
			b = c;
		else
			a = c;

		if (abs(b - a) < e)
		{
			str.Format(L"%f \r\n", (a + b) / 2.0);
			return str;
		}
	}
	return CString();
}
CString Clabaa2Dlg::Horda(double a, double b, int f)
{
	double c1 = a;
	CString str;
	while (true)
	{
		double c2 = a - ((b - a) * Func(a, 0)) / (Func(b, 0) - Func(a, 0));
		if (abs(c1 - c2) <= e)
		{
			str.Format(L"%f \r\n", c2);
			return str;
		}
		if (Func(a, 0) * Func(c2, 0) < 0)
			b = c2;
		else
			a = c2;
		c1 = c2;
	}

}
CString Clabaa2Dlg::Newton(double a, double b, int f)
{
	CString str;
	double a1, b1;
	if (Func(a, 0) * Func(a, 2) > 0)
		a1 = a;
	else
		a1 = b;
	while (true)
	{
		b1 = a1 - Func(a1, 0) / Func(a1, 1);
		if (abs(b1 - a1) < e)
		{
			str.Format(L"%f \r\n", (a1 + b1) / 2.0);
			return str;
		}
	}
	return 0;
}

double Clabaa2Dlg::Func(double x, int f)
{
	if (f == 1)
		return 4 - 5 / x;
	else if (f == 2)
		return -5 / pow(x, 2);
	else
		return 4 * x - 5 * log(x) - 5;
}



void Clabaa2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (pScrollBar == (CScrollBar*)&Slyder && LVN_ENDSCROLL)
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	while (true)
	{
		b = a + e;
		if (Func(a, 0) * Func(b, 0) < 0)
			break;
		a += e;
	}
	if (pScrollBar == (CScrollBar*)&Slyder)
	{
		if (nSBCode == SB_ENDSCROLL)
		{
			index = Slyder.GetPos();
			if (index == 0)
			{
				result += Metod_Dihotomii(a, b, 0);
				UpdateData(FALSE);
				a = b = 0;
			}
			else if (index == 1)
			{
				result += Horda(a, b, 0);
				UpdateData(FALSE);
				a = b = 0;
			}
			else
			{
				result += Newton(a, b, 0);
				UpdateData(FALSE);
				a = b = 0;
			}
		}
	}
}




void Clabaa2Dlg::OnEnChangeEdit5()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
