
// Laba_mnogom_optDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Laba_mnogom_opt.h"
#include "Laba_mnogom_optDlg.h"
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
//	afx_msg void OnFileOpen();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_FILE_OPEN, &CAboutDlg::OnFileOpen)
END_MESSAGE_MAP()


// Диалоговое окно CLabamnogomoptDlg



CLabamnogomoptDlg::CLabamnogomoptDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABA_MNOGOM_OPT_DIALOG, pParent)
	, BF(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLabamnogomoptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, BF);
}

BEGIN_MESSAGE_MAP(CLabamnogomoptDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CLabamnogomoptDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CLabamnogomoptDlg

BOOL CLabamnogomoptDlg::OnInitDialog()
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

void CLabamnogomoptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLabamnogomoptDlg::OnPaint()
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
HCURSOR CLabamnogomoptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double CLabamnogomoptDlg::MSQ(double a, double b, double c, double r)
{
	double res = 0;
	for (int i = 0; i < Points.GetSize(); i++)
	{
		double delta = sqrt(pow(Points[i].x - a, 2) + pow(Points[i].y - b, 2) + pow(Points[i].z - c, 2)) - r;
		res += delta*delta; 
	}
	return res; 
}

void CLabamnogomoptDlg::LinearDixotomy(double& value1, double value2, double value3, double value4, int type)
{
	double epsilon = 0.000001f; //погрешность вычисления

	double step = epsilon * 100; //шаг

	double V_Left, V_Right, MSQ1 = 0.0, MSQ2 = 0.0; //значения на границах интервала и СКО

	switch (type) //переключатель по типам расчета
	{
	case 1: //расчет по а
		MSQ1 = MSQ(value1, value2, value3, value4);
		MSQ2 = MSQ(value1 - step, value2, value3, value4);
		break;
	case 2: //расчет по b
		MSQ1 = MSQ(value2, value1, value3, value4);
		MSQ2 = MSQ(value2, value1 - step, value3, value4);
		break;
	case 3: //расчет по с
		MSQ1 = MSQ(value2, value3, value1, value4);
		MSQ2 = MSQ(value2, value3, value1 - step, value4);
		break;
	case 4: //расчет по r
		MSQ1 = MSQ(value2, value3, value4, value1);
		MSQ2 = MSQ(value2, value3, value4, value1 - step);
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
				MSQ1 = MSQ(V_Left, value2, value3, value4);
				MSQ2 = MSQ(V_Left + step, value2, value3, value4);
				break;
			case 2: //расчет по b
				MSQ1 = MSQ(value2, V_Left, value3, value4);
				MSQ2 = MSQ(value2, V_Left + step, value3, value4);
				break;
			case 3: //расчет по с 
				MSQ1 = MSQ(value2, value3, V_Left,  value4);
				MSQ2 = MSQ(value2, value3, V_Left + step,  value4);
				break;
			case 4: //расчет по r
				MSQ1 = MSQ(value2, value3, value4, V_Left);
				MSQ2 = MSQ(value2, value3, value4, V_Left + step);
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
				MSQ1 = MSQ(V_Right, value2, value3, value4);
				MSQ2 = MSQ(V_Right + step, value2, value3, value4);
				break;
			case 2: //расчет по b
				MSQ1 = MSQ(value2, V_Right, value3, value4);
				MSQ2 = MSQ(value2, V_Right + step, value3, value4);
				break;
			case 3: //расчет по с
				MSQ1 = MSQ(value2, value3, V_Right, value4);
				MSQ2 = MSQ(value2, value3, V_Right + step, value4);
				break;
			case 4: //расчет по r
				MSQ1 = MSQ(value2, value3, value4, V_Right);
				MSQ2 = MSQ(value2, value3, value4, V_Right + step);
				break;
			}
			if (MSQ1 < MSQ2)
				break;
		}
	}

	double V_Mid; //значение в середине интервала

	//финальная дихотомия	
	while (abs(V_Right - V_Left) <= epsilon) //цикл дихотомии
	{
		V_Mid = (V_Right + V_Left) / 2.f; //вычисление середины интервала
		switch (type) //переключатель по типам расчета
		{
		case 1: //расчет по а
			MSQ1 = MSQ(V_Mid + epsilon, value2, value3, value4);
			MSQ2 = MSQ(V_Mid - epsilon, value2, value3, value4);
			break;
		case 2: //расчет по b
			MSQ1 = MSQ(value2, V_Mid + epsilon, value3, value4);
			MSQ2 = MSQ(value2, V_Mid - epsilon, value3, value4);
			break;
		case 3: //расчет по с
			MSQ1 = MSQ(value2, value3, V_Mid + epsilon, value4);
			MSQ2 = MSQ(value2, value3, V_Mid - epsilon, value4);
			break;
		case 4: //расчет по r
			MSQ1 = MSQ(value2, value3, value4, V_Mid + epsilon);
			MSQ2 = MSQ(value2, value3, value4, V_Mid - epsilon);
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


CString CLabamnogomoptDlg::Start()
{
		double A, B, R, C; //переменные под координаты центра и радиус окружности
		A = B = R = 0.0; //обнуляем 
		//находим начальные приближения
		for (int i = 0; i < Points.GetSize(); i++)//цикл по всем точкам
		{
			A += Points[i].x; //суммируем х
			B += Points[i].y; //суммируем y
		}
		
		C = Points[0].z;
		for (int i = 0; i < Points.GetSize(); i++)
		{
			if (Points[i].z < C)
				C = Points[i].z; //находим наименьшее значение z
		}
		A /= Points.GetSize();//находим среднее значения
		B /= Points.GetSize();//находим среднее значения
		for (int i = 0; i < Points.GetSize(); i++)
		{//радиус каждой точки
			R += sqrt(pow(Points[i].x - A, 2) + pow(Points[i].y - B, 2) + pow(Points[i].z - C, 2));
		}

		R /= Points.GetSize();//вычисляем среднее значение радиуса

		double A_old, B_old, C_old, R_old; //буфер под предыдущие значения

		while (true) //цикл пока не достигнем требуемой точности
		{
			A_old = A; //запоминаем старое значение А
			B_old = B; //запоминаем старое значение B
			C_old = C; //запоминаем старое значение С
			R_old = R; //запоминаем старое значение R
			
			LinearDixotomy(A, B, C, R,1); //запускаем дихотомию по А
			LinearDixotomy(B, A, C, R, 2); //запускаем дихотомию по B
			LinearDixotomy(C, A, B, R, 3); //запускаем дихотомию по С
			LinearDixotomy(R, A, B, C, 4); //запускаем дихотомию по R
			
			//вычисляем «длину» интервала и сравниваем с допустимой погрешностью
			if (sqrt(pow(A - A_old, 2) + pow(B - B_old, 2) + pow(R - R_old, 2) + pow(C - C_old, 2)) < 0.0001)
				break; //если достигли требуемой точности - выходим
		}
		CString str;
		str.Format(L"\r\nXс = %f\tYc = %f\tZc = %f\tR = %f\r\n", A, B, C, R);
		this->A = A;
		this->B = B;
		this->C = C;
		this->R = R;
		return str;
}

//CString CLabamnogomoptDlg::Otklon(double x, double y, double z)
//{ 
//	double Max, Min = Points[0].z;
//	Max = Min;
//	for (int i = 0; i < Points.size(); i++)
//	{
//		double ab = sqrt(pow(Points[i].x - x, 2) + pow(Points[i].y - y, 2) + pow(Points[i].z - z, 2));
//		if (ab < Min)
//			Min = ab;
//		if (ab > Max)
//			Max = ab;
//	}
//	CString str;
//	str.Format(L"Отклонение от округлости %f\r\n\r\n", (Max - Min) / 2.0);
//	return str;
//}

void CLabamnogomoptDlg::OnBnClickedButton1()
{
	CFileDialog fileDialog(TRUE);
	int result = fileDialog.DoModal();	
	if (result == IDOK)	
	{
		CStdioFile File(fileDialog.GetPathName(), CFile::modeRead);
		if (File != NULL)
		{
			int count = 0;
			CString s;
			while (File.ReadString(s))
			{
				CString buff;
				double x = 0.0, y = 0.0, z = 0.0;
				for (int i = 0; i < s.GetLength(); i++)
				{
					char bf = s[i];
					if (bf == '\t')
					{
						if (count == 0)
						{
							x = _wtof(buff);
							buff.Empty();
							count++;
							continue;
						}
						if (count == 1)
						{
							y = _wtof(buff);
							buff.Empty();
							count++;
							continue;
						}
					}
					buff += bf;
				}
				z = _wtof(buff);
				Point pt; 
				pt.x = x; 
				pt.y = y; 
				pt.z = z;
				Points.Add(pt);
				count = 0;
			}
		}
	}
	BF += L"Для данных из файла " + fileDialog.GetFileName() + L", путь к файлу " + fileDialog.GetPathName() + Start();
	BF+=L"Данные получены при Xс = 7 Yc = 6 Z = 7 R = 4 \r\n";
	CString str;
	//BF += Otklon(A, B, C);
	UpdateData(FALSE);
	Points.RemoveAll();
}