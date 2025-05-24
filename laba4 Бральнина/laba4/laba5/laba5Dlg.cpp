
// laba5Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "laba5.h"
#include "laba5Dlg.h"
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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно Claba5Dlg



Claba5Dlg::Claba5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABA5_DIALOG, pParent)
	, answer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Claba5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, answer);
}

BEGIN_MESSAGE_MAP(Claba5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Claba5Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений Claba5Dlg

BOOL Claba5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void Claba5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Claba5Dlg::OnPaint()
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
HCURSOR Claba5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
struct Point//структура для описания точки
{
	double x, y; //координаты точки в двумерном пространстве
};

CArray <Point, Point> Points;

double Claba5Dlg::MSQ(double a, double b, double r)
{
	double res = 0;
	//цикл по всем точкам 
	for (int i = 0; i < Points.GetSize(); i++)
	{
		//отклонение по нормали к дуге окружности
		double delta = pow(Points[i].x - a, 2) + pow(Points[i].y - b, 2) - r * r;
		res += delta * delta; //возводим отклонение в квадрат
	}
	return res; //возвращаем результат в программу верхнего уровня

}

void Claba5Dlg::LinearDixotomy(double& value1, double value2, double value3, int type)
{
	double epsilon = 0.000001f; //погрешность вычисления

	double step = epsilon * 100; //шаг

	double V_Left, V_Right, MSQ1, MSQ2; //значения на границах интервала и СКО

	switch (type) //переключатель по типам расчета
	{
	case 1: //расчет по а
		MSQ1 = MSQ(value1, value2, value3);
		MSQ2 = MSQ(value1 - step, value2, value3);
		break;
	case 2: //расчет по b
		MSQ1 = MSQ(value2, value1, value3);
		MSQ2 = MSQ(value2, value1 - step, value3);
		break;
	case 3: //расчет по r
		MSQ1 = MSQ(value2, value3, value1);
		MSQ2 = MSQ(value2, value3, value1 - step);
		break;
	}
	if (MSQ1 > MSQ2)
	{
		V_Right = V_Left = value1;
		while (true)
		{
			V_Left = V_Left - step;

			switch (type)
			{
			case 1: //расчет по а
				MSQ1 = MSQ(V_Left, value2, value3);
				MSQ2 = MSQ(V_Left + step, value2, value3);
				break;
			case 2: //расчет по b
				MSQ1 = MSQ(value2, V_Left, value3);
				MSQ2 = MSQ(value2, V_Left + step, value3);
				break;
			case 3: //расчет по r
				MSQ1 = MSQ(value2, value3, V_Left);
				MSQ2 = MSQ(value2, value3, V_Left + step);
				break;
			}

			if (MSQ1 > MSQ2)
				break;
		}
	}
	else
	{
		V_Right = V_Left = value1;
		while (true)
		{
			V_Right = V_Right + step;
			switch (type)
			{
			case 1: //расчет по а
				MSQ1 = MSQ(V_Right, value2, value3);
				MSQ2 = MSQ(V_Right + step, value2, value3);
				break;
			case 2: //расчет по b
				MSQ1 = MSQ(value2, V_Right, value3);
				MSQ2 = MSQ(value2, V_Right + step, value3);
				break;
			case 3: //расчет по c
				MSQ1 = MSQ(value2, value3, V_Right);
				MSQ2 = MSQ(value2, value3, V_Right + step);
				break;
			}
			if (MSQ1 < MSQ2)
				break;
		}
	}

	double V_Mid; //значение в середине интервала

	//финальная дихотомия	
	while (V_Right - V_Left > epsilon) //цикл дихотомии
	{
		V_Mid = (V_Right + V_Left) / 2.f; //вычисление середины интервала
		switch (type) //переключатель по типам расчета
		{
		case 1: //расчет по а
			MSQ1 = MSQ(V_Mid + epsilon / 3, value2, value3);
			MSQ2 = MSQ(V_Mid - epsilon / 3, value2, value3);
			break; case 2: //расчет по b
				MSQ1 = MSQ(value2, V_Mid + epsilon / 3, value3);
				MSQ2 = MSQ(value2, V_Mid - epsilon / 3, value3);
				break;
			case 3: //расчет по r
				MSQ1 = MSQ(value2, value3, V_Mid + epsilon / 3);
				MSQ2 = MSQ(value2, value3, V_Mid - epsilon / 3);
				break;
		}
		if (MSQ1 < MSQ2)
		{
			V_Left = V_Mid;
		}
		else
		{
			V_Right = V_Mid;
		}

	}

	value1 = (V_Right + V_Left) / 2.f; //середина интервала

}

CString Claba5Dlg::result()
{
	double A, B, R; //переменные под координаты центра и радиус окружности
	A = B = R = 0.f; //обнуляем 
	//находим начальные приближения
	for (int i = 0; i < Points.GetSize(); i++)//цикл по всем точкам
	{
		A += Points[i].x; //суммируем х
		B += Points[i].y; //суммируем y
	}

	A /= Points.GetSize();//находим среднее значения
	B /= Points.GetSize();//находим среднее значения

	for (int i = 0; i < Points.GetSize(); i++)
	{//радиус каждой точки
		R += sqrt(pow(Points[i].x - A, 2) + pow(Points[i].y - B, 2));
	}

	R /= Points.GetSize();//вычисляем среднее значение радиуса

	double A_old, B_old, R_old; //буфер под предыдущие значения

	while (true) //цикл пока не достигнем требуемой точности
	{
		A_old = A; //запоминаем старое значение А
		B_old = B; //запоминаем старое значение B
		R_old = R; //запоминаем старое значение R

		LinearDixotomy(A, B, R, 1); //запускаем дихотомию по А
		LinearDixotomy(B, A, R, 2); //запускаем дихотомию по B
		LinearDixotomy(R, A, B, 3); //запускаем дихотомию по R
		//вычисляем «длину» интервала и сравниваем с допустимой погрешностью
		if (sqrt(pow(A - A_old, 2) + pow(B - B_old, 2) + pow(R - R_old, 2)) < 0.0001)
			break; //если достигли требуемой точности - выходим
	}
	CString res;
	res.Format(L" Xс = %f Yc = %f R = %f\r\n", A, B, R);
	a = A;
	b = B;
	return res;
}

CString Claba5Dlg::Otklonenie(double x, double y)
{
	double Max_ud = -1, Min_ud = 100;
	for (int i = 0; i < Points.GetSize(); i++)
	{
		double rasst = sqrt(pow(Points[i].x - x, 2) + pow(Points[i].y - y, 2));
		if (Max_ud < rasst)
		{
			Max_ud = rasst;
		}
		else if (Min_ud > rasst)
		{
			Min_ud = rasst;
		}
	}
	CString str;
	str.Format(L"Отклонение от округлости %f\r\n", (Max_ud - Min_ud) / 2.0);
	return str;
}




void Claba5Dlg::OnBnClickedButton1()
{
	CFileDialog fileDialog(TRUE);
	int res = fileDialog.DoModal();	
	if (res == IDOK)	
	{
		CStdioFile File(fileDialog.GetPathName(), CFile::modeRead);
		if (File != NULL)
		{
			CString str;
			while (File.ReadString(str))
			{
				CString num;
				double x = 0.0, y = 0.0;
				for (int i = 0; i < str.GetLength(); i++)
				{
					char n = str[i];
					if (n == '\t')
					{
						x = _wtof(num);
						num.Empty();
						continue;
					}
					num+= n;
				}
				y = _wtof(num);
				Point pt; 
				pt.x = x; 
				pt.y = y; 
				Points.Add(pt);
			}
		}
	}
	answer += L"Для данных из файла " + fileDialog.GetFileName() + L", путь к файлу " + fileDialog.GetPathName() + result();
	answer += Otklonenie(a, b);
	answer += L"Данные получены при Xс = 7 Yc = 6 R = 4\r\n";
	UpdateData(FALSE);
	Points.RemoveAll();
}
