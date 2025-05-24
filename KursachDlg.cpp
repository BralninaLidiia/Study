
// KursachDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"
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


// Диалоговое окно CKursachDlg



CKursachDlg::CKursachDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KURSACH_DIALOG, pParent)
	, D_1(100)
	, D_2(75)
	, D_3(10)
	, H_1(7)
	, H_2(20)
	, L(20)
	, Alfa(40)
	, Count(7)
	, R1(2)
	, R2(3.5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKursachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, D_1);
	DDX_Text(pDX, IDC_EDIT2, D_2);
	DDX_Text(pDX, IDC_EDIT3, D_3);
	DDX_Text(pDX, IDC_EDIT4, H_1);
	DDX_Text(pDX, IDC_EDIT5, H_2);
	DDX_Text(pDX, IDC_EDIT6, L);
	DDX_Text(pDX, IDC_EDIT7, Alfa);
	DDX_Text(pDX, IDC_EDIT8, Count);
	DDX_Text(pDX, IDC_EDIT9, R1);
	DDX_Text(pDX, IDC_EDIT10, R2);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT3, edit3);
	DDX_Control(pDX, IDC_EDIT4, edit4);
	DDX_Control(pDX, IDC_EDIT5, edit5);
	DDX_Control(pDX, IDC_EDIT6, edit6);
	DDX_Control(pDX, IDC_EDIT7, edit7);
	DDX_Control(pDX, IDC_EDIT8, edit8);
	DDX_Control(pDX, IDC_EDIT9, edit9);
	DDX_Control(pDX, IDC_EDIT10, edit10);
}

BEGIN_MESSAGE_MAP(CKursachDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CKursachDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CKursachDlg

BOOL CKursachDlg::OnInitDialog()
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

void CKursachDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKursachDlg::OnPaint()
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
HCURSOR CKursachDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <atlbase.h>
#import "C:\\Program Files\\ASCON\\KOMPAS-3D v21 Study\\Bin\\kAPI5.tlb"
#import "C:\\Program Files\\ASCON\\KOMPAS-3D v21 Study\\Bin\\ksConstants3D.tlb" 
using namespace Kompas6API5;
using namespace Kompas6Constants3D;


bool CKursachDlg::Proverka()
{
	UpdateData(TRUE);
	if (D_1 <= 0)
	{
		MessageBox(L"Введите положительное значение для D1");
		SelAndFocus(edit1);
		return false;
	}
	if (D_2 <= 0)
	{
		MessageBox(L"Введите положительное значение для D2");
		SelAndFocus(edit2);
		return false;
	}
	if (D_3 <= 0)
	{
		MessageBox(L"Введите положительное значение для D3");
		SelAndFocus(edit3);
		return false;
	}
	if (H_1 <= 0)
	{
		MessageBox(L"Введите положительное значение для H1");
		SelAndFocus(edit4);
		return false;
	}
	if (H_2 <= 0)
	{
		MessageBox(L"Введите положительное значение для H2");
		SelAndFocus(edit5);
		return false;
	}
	if (L <= 0)
	{
		MessageBox(L"Введите положительное значение для L");
		SelAndFocus(edit6);
		return false;
	}
	if (Alfa <= 0)
	{
		MessageBox(L"Введите положительное значение для угла a");
		SelAndFocus(edit7);
		return false;
	}
	if (Count <= 0)
	{
		MessageBox(L"Введите положительное значение для кол-ва отверстий");
		SelAndFocus(edit8);
		return false;
	}
	if (R1 <= 0)
	{
		MessageBox(L"Введите положительное значение для R1");
		SelAndFocus(edit9);
		return false;
	}
	if (R2 <= 0)
	{
		MessageBox(L"Введите положительное значение для R2");
		SelAndFocus(edit10);
		return false;
	}
	if (D_1 <= D_2)
	{
		MessageBox(L"Диаметр D2 недопустим");
		SelAndFocus(edit2);
		return false;
	}
	if (D_3 >= D_2 || D_3 >= D_1)
	{
		MessageBox(L"Извините, диаметр D3 недопустим");
		SelAndFocus(edit3);
		return false;
	}
	double Beta = Alfa;
	Beta = Beta * PI / 180.0;
	double S = 0.5 * L * L * sin(Beta);
	Alfa /= 2.0;
	Alfa = Alfa * PI / 180.0;
	double y = 90 - 360.0 / (float)Count;
	y = y * PI / 180.0;
	double Bx= -1 * sin(Alfa) * L;
	double By = cos(Alfa) * L + D_3;
	double Ax = sin(Alfa) * L;
	double Ay = cos(Alfa) * L + D_3;
	double AB = sqrt(pow(Ax - Bx, 2) + pow(Ay - By, 2));
	double rad = 2 * S / (L + L + AB);
	if (R2 > rad)
	{
		MessageBox(L"Извините, радиус R2 недопустим");
		SelAndFocus(edit10);
		return false;
	}
	if (R1 > rad)
	{
		MessageBox(L"Извините, радиус R1 недопустим");
		SelAndFocus(edit9);
		return false;
	}
	double OB = sqrt(pow(sin(Alfa) * L, 2) + pow(-1 * cos(Alfa) * L - D_3 / 2.0, 2));
	double y2 = acos((OB * OB + pow(D_3 / 2.0, 2) - L * L) / (2 * OB * D_3 / 2.0));
	double X1 = OB * cos(y2) * cos(y) - OB * sin(y2) * sin(y);
	double X = sin(Alfa) * L;
	if (X > X1)
	{
		MessageBox(L"Извините, кол-во отверстий недопустимо");
		SelAndFocus(edit8);
		return false;
	}
	if (OB > D_2 / 2.0)
	{
		MessageBox(L"Извините, длина L недопустима");
		SelAndFocus(edit6);
		return false;
	}
	return true;
}


void CKursachDlg::Start()
{
	D_1 /= 2.0;
	D_2 /= 2.0;
	D_3 /= 2.0;

	//подключение к компасу:
	CoInitialize(NULL);
    KompasObjectPtr kompas;
	HRESULT hRes;
	hRes = kompas.GetActiveObject(L"Kompas.Application.5");
	if (FAILED(hRes))
		kompas.CreateInstance(L"Kompas.Application.5");
	kompas->Visible = true; 

	//создание документа КОМПАС:
	ksDocument3DPtr doc;
	doc = kompas->Document3D();
	doc->Create(false, true);
	doc = kompas->ActiveDocument3D();
	ksPartPtr part;
	part = doc->GetPart(pTop_Part);
	
	//эскиз под вращение:
	ksEntityPtr sketch = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
	sketchDef->SetPlane(part->GetDefaultEntity(o3d_planeXOY));
	sketch->Create();
	ksDocument2DPtr doc2D = sketchDef->BeginEdit();
	doc2D->ksLineSeg(0, 0, 0, D_1, 1);
	doc2D->ksLineSeg(0, D_1, H_1, D_1, 1);
	doc2D->ksLineSeg(H_1, D_1, H_1, D_2, 1);
	doc2D->ksLineSeg(H_1, D_2, H_2 + H_1, D_2, 1);
	doc2D->ksLineSeg(H_2 + H_1, D_2, H_2 + H_1, 0, 1);
	doc2D->ksLineSeg(H_2 + H_1, 0, 0, 0, 1);
	doc2D->ksLineSeg(H_2 + H_1, 0, 0, 0, 3); //осевая
	sketchDef->EndEdit();
	
	//операция вращения:
	ksEntityPtr rotation = part->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr rotationDef = rotation->GetDefinition();
	rotationDef->SetSideParam(TRUE, 360);
	rotationDef->directionType = dtNormal;
	rotationDef->SetSketch(sketch);
	rotation->Create();

	//эскиз под треугольные штуки:
	ksEntityPtr sketch3 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef3 = sketch3->GetDefinition();
	sketchDef3->SetPlane(part->GetDefaultEntity(o3d_planeYOZ));
	sketch3->Create();
	ksDocument2DPtr doc2D_2 = sketchDef3->BeginEdit();
	doc2D_2->ksLineSeg(0, D_3, -1 * sin(Alfa) * L, cos(Alfa) * L + D_3, 1);
	doc2D_2->ksLineSeg(-1 * sin(Alfa) * L, cos(Alfa) * L + D_3, sin(Alfa) * L, cos(Alfa) * L + D_3, 1);
	doc2D_2->ksLineSeg(0, D_3, sin(Alfa) * L, cos(Alfa) * L + D_3, 1);
	sketchDef3->EndEdit();

	//операция вырез выдавливанием:
	ksEntityPtr CutExtr2 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr CutExtrDef2 = CutExtr2->GetDefinition();
	CutExtrDef2->directionType = dtNormal;
	CutExtrDef2->SetSketch(sketch3);
	CutExtrDef2->SetSideParam(TRUE, etThroughAll, 0, 0, FALSE);
	CutExtr2->Create();

	//операция скругление R2:	
	ksEntityPtr Rounding = part->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr RoundingDef = Rounding->GetDefinition();
	RoundingDef->radius = R2;
	RoundingDef->tangent = FALSE;
	ksEntityCollectionPtr RoundingCollection = part->EntityCollection(o3d_face);
	ksEntityCollectionPtr RoundingArray = RoundingDef->array();
	RoundingArray->Clear();
	for (int i = 0; i < RoundingCollection->GetCount(); i++)
	{
		ksEntityPtr ed = RoundingCollection->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == CutExtr2)
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			double rast = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
			if (rast == H_1 + H_2 && abs(y1) > D_3 && abs(y2) > D_3)
			{
				RoundingArray->Add(ed);
			}
		}
	}
	Rounding->Create();
	ksEntityPtr Rounding2 = part->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr RoundingDef2 = Rounding2->GetDefinition();
	RoundingDef2->radius = R1;
	RoundingDef2->tangent = FALSE;
	ksEntityCollectionPtr RoundingCollection2 = part->EntityCollection(o3d_edge);
	ksEntityCollectionPtr RoundingArray2 = RoundingDef2->array();
	RoundingArray2->Clear();
	for (int i = 0; i < RoundingCollection2->GetCount(); i++)
	{
		ksEntityPtr ed = RoundingCollection2->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == CutExtr2)
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			double rast = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
			if (rast == H_1 + H_2 && abs(y1) == D_3 && abs(y2) == D_3)
			{
				RoundingArray2->Add(ed);
			}
		}
	}
	Rounding2->Create();

	//операция ось для массива:
	ksEntityPtr PlaneXOZ = part->GetDefaultEntity(o3d_planeXOZ);
	ksEntityPtr PlaneXOY = part->GetDefaultEntity(o3d_planeXOY);
	ksEntityPtr Axis = part->NewEntity(o3d_axis2Planes);
	ksAxis2PlanesDefinitionPtr AxisDef = Axis->GetDefinition();
	AxisDef->SetPlane(1, PlaneXOZ);
	AxisDef->SetPlane(2, PlaneXOY);
	Axis->Create();

	//операция массив:
	ksEntityPtr Array = part->NewEntity(o3d_circularCopy);
	ksCircularCopyDefinitionPtr ArrayDef = Array->GetDefinition();
	ArrayDef->count1 = 1;
	ArrayDef->SetAxis(Axis);
	ArrayDef->geomArray = FALSE;
	ArrayDef->SetCopyParamAlongDir(Count, 360.0 / (float)Count, FALSE, FALSE);
	ksEntityCollectionPtr EntityCollection = ArrayDef->GetOperationArray();
	EntityCollection->Clear();
	EntityCollection->Add(CutExtr2);
	EntityCollection->Add(Rounding);
	EntityCollection->Add(Rounding2);
	Array->Create();

	//эскиз под отверстие:
	ksEntityPtr sketch2 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef2 = sketch2->GetDefinition();
	sketchDef2->SetPlane(part->GetDefaultEntity(o3d_planeYOZ));
	sketch2->Create();
	ksDocument2DPtr doc2D_1 = sketchDef2->BeginEdit();
	doc2D_1->ksCircle(0, 0, D_3, 1);
	sketchDef2->EndEdit();

	//операция вырез выдавливанием:
	ksEntityPtr CutExtr = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr CutExtrDef = CutExtr->GetDefinition();
	CutExtrDef->directionType = dtNormal;
	CutExtrDef->SetSketch(sketch2);
	CutExtrDef->SetSideParam(TRUE, etThroughAll, 0, 0, FALSE);
	CutExtr->Create();

	//сохранить как:
	doc->SaveAs("C:\\Users\\grigo\\Desktop\\Деталь.m3d");
	CoUninitialize();
}

void CKursachDlg::OnBnClickedButton1()
{
	if (Proverka())
		Start();
}
