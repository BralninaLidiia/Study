
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
	, L1(70)
	, L4(20)
	, L5(80)
	, L11(190)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKursachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, L1);
	DDX_Text(pDX, IDC_EDIT10, L4);
	DDX_Text(pDX, IDC_EDIT11, L5);
	DDX_Text(pDX, IDC_EDIT22, L11);
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
#import "C:\Games\Bin\kAPI5.tlb"
#import "C:\Games\Bin\ksConstants3D.tlb" 
using namespace Kompas6API5;
using namespace Kompas6Constants3D;

bool CKursachDlg::Proverka()
{
	if (L11<=L6+D3+D1)
	{
		MessageBox(L"Недопустимое значение L1");
		return false;
	}

	if (L1<L9+R2)
	{
		MessageBox(L"Недопустимое значение L2");
		return false;
	}
	if (L5<L9)
	{
		MessageBox(L"Недопустимое значение L3");
		return false;
	}
	if (L5 < L8)
	{
		MessageBox(L"Недопустимое значение L4");
		return false;
	}
}

void CKursachDlg::Start()
{
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

	//эскиз главный цилиндр:
	ksEntityPtr sketch1 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch1Def = sketch1->GetDefinition();
	ksEntityPtr basePlane1 = part->GetDefaultEntity(o3d_planeXOY);
	ksPlaneOffsetDefinitionPtr baseplanedef1 = basePlane1->GetDefinition();
	sketch1Def->SetPlane(basePlane1);
	sketch1->Create();
	ksDocument2DPtr doc2D1 = sketch1Def->BeginEdit();
	doc2D1->ksCircle(0, 0, D1/ 2.0, 1);
	sketch1Def->EndEdit();

	//выдавливание первого эскиза
	ksEntityPtr extrusion = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusiondef = extrusion->GetDefinition();
	extrusiondef->directionType=dtNormal;
	extrusiondef->SetSideParam(TRUE, etBlind, H1, 0, TRUE);
	extrusiondef->SetSketch(sketch1);
	extrusion->Create();

    //первая смещенная плоскость
	ksEntityPtr plane1 = part->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr plane1def = plane1->GetDefinition();
	ksEntityPtr basePlane2 = part->GetDefaultEntity(o3d_planeXOZ);
	ksPlaneOffsetDefinitionPtr baseplanedef2 = basePlane2->GetDefinition();
	plane1def->direction = TRUE;
	plane1def->offset = L1;
	plane1def->SetPlane(basePlane2);
	plane1->Create();

    //эскиз ребра жесткости
	ksEntityPtr sketch2 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch2Def = sketch2->GetDefinition();
	sketch2Def->SetPlane(basePlane2);
	sketch2->Create();
	ksDocument2DPtr doc2D2 = sketch2Def->BeginEdit();
	double H3b = ((L6 +(sqrt(pow(R1,2)-pow(H4,2)))) / (L6 - D1 / 2.0 + (sqrt(pow(R1, 2) - pow(H4, 2))))) * H3;
	doc2D2->ksLineSeg(L6 +(sqrt(pow(R1, 2) - pow(H4, 2))), -H4, 0, -H3b - H4, 1);
	doc2D2->ksLineSeg(L6 +(sqrt(pow(R1, 2) - pow(H4, 2))), -H4, 0, -H4, 1);
	doc2D2->ksLineSeg(0, -H4, 0, -H3b - H4, 1);
	sketch2Def->EndEdit();

	//выдавливание ребра жесткости
	ksEntityPtr extrusion2 = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusion2def = extrusion2->GetDefinition();
	extrusion2def->directionType = dtBoth;
	extrusion2def->SetSideParam(false, etBlind, L7, 0, TRUE);
	extrusion2def->SetSideParam(true, etBlind, L7, 0, TRUE);
	extrusion2def->SetSketch(sketch2);
	extrusion2->Create();

	//эскиз вырезание лишнего после выдавливания
	ksEntityPtr sketch3 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch3Def = sketch3->GetDefinition();
	sketch3Def->SetPlane(plane1);
	sketch3->Create();
	ksDocument2DPtr doc2D3 = sketch3Def->BeginEdit();
	doc2D3->ksLineSeg(D1 / 2.0, -H1, D1 / 2.0, -H1-H3b, 1);
	doc2D3->ksLineSeg(D1 / 2.0, -H1, 0, -H1, 1);
	doc2D3->ksLineSeg(0, -H1, 0, -H1 - H3b, 1);
	doc2D3->ksLineSeg(0, -H1 - H3b, D1 / 2.0, -H1 - H3b, 1);
	sketch3Def->EndEdit();

	//убираем лишнее после выдавливания
	ksEntityPtr Cut1 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr Cut1def = Cut1->GetDefinition();
	Cut1def->directionType = dtNormal;
	Cut1def->SetSketch(sketch3);
	Cut1def->SetSideParam(true, etThroughAll, 0, 0, FALSE);
	Cut1->Create();
	
	//эскиз вырезание внутри цилиндра 
	ksEntityPtr sketch4 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch4Def = sketch4->GetDefinition();
	sketch4Def->SetPlane(part->GetDefaultEntity(o3d_planeXOY));
	sketch4->Create();
	ksDocument2DPtr doc2D4 = sketch4Def->BeginEdit();
	doc2D4->ksCircle(0, 0, D2 / 2.0, 1);
	sketch4Def->EndEdit();

	//вырезание полости в цилиндре
	ksEntityPtr Cut2 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr Cut2def = Cut2->GetDefinition();
	Cut2def->directionType = dtReverse;
	Cut2def->SetSketch(sketch4);
	Cut2def->SetSideParam(false, etBlind, H1-(D1 / 2.0 -D2 / 2.0), 0, FALSE);
	Cut2->Create();
	
	//смещенная плоскость для выреза сверху
	ksEntityPtr planeotv = part->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr planeotvdef = planeotv->GetDefinition();
	planeotvdef->direction = TRUE;
	planeotvdef->offset = H1;
	planeotvdef->SetPlane(basePlane1);
	planeotv->Create();

	//эскиз отверстие в цилиндре сверху
	ksEntityPtr sketch5 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch5Def = sketch5->GetDefinition();
	sketch5Def->SetPlane(planeotv);
	sketch5->Create();
	ksDocument2DPtr doc2D5 = sketch5Def->BeginEdit();
	doc2D5->ksArcBy3Points(-L3 / 2, sqrt(pow(R3, 2) - pow(L3 / 2, 2)), 0, R3, L3/2, sqrt(pow(R3, 2) - pow(L3 / 2, 2)), 1);
	doc2D5->ksLineSeg(L3 / 2, sqrt(pow(R3, 2) - pow(L3 / 2, 2)), L3 / 2, -sqrt(pow(R3, 2) - pow(L3 / 2, 2)), 1);
	doc2D5->ksArcBy3Points(-L3 / 2, -sqrt(pow(R3, 2) - pow(L3 / 2, 2)), 0, -R3, L3 / 2, -sqrt(pow(R3, 2) - pow(L3 / 2, 2)), 1);
	doc2D5->ksLineSeg(-L3 / 2, sqrt(pow(R3, 2) - pow(L3 / 2, 2)), -L3 / 2, -sqrt(pow(R3, 2) - pow(L3 / 2, 2)), 1);
	sketch5Def->EndEdit();

	//вырезание отверстия в цилиндре сверху
	ksEntityPtr Cut3 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr Cut3def = Cut3->GetDefinition();
	Cut3def->directionType = dtNormal;
	Cut3def->SetSketch(sketch5);
	Cut3def->SetSideParam(true, etThroughAll, 0, 0, FALSE);
	Cut3->Create();

	//недоухо
	ksEntityPtr sketch6 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch6Def = sketch6->GetDefinition();
	sketch6Def->SetPlane(plane1);
	sketch6->Create();
	ksDocument2DPtr doc2D6 = sketch6Def->BeginEdit();
	doc2D6->ksLineSeg(L2 / 2.0, 0, L2 / 2.0, -H2+L2 / 2.0, 1);
	doc2D6->ksArcBy3Points(L2 / 2.0, -H2 + L2 / 2.0, 0, -H2, -L2 / 2.0, -H2+L2 / 2.0, 1);
	doc2D6->ksLineSeg(-L2 / 2.0, -H2 + L2 / 2.0, -L2 / 2.0, 0, 1);
	doc2D6->ksLineSeg(-L2 / 2.0, 0, L2 / 2.0, 0, 1);
	sketch6Def->EndEdit();

	//выдавливание недоуха
	ksEntityPtr extrusion3 = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusion3def = extrusion3->GetDefinition();
	extrusion3def->directionType = dtReverse;
	extrusion3def->SetSideParam(false, etUpToNearSurface, 2000, 0, TRUE);
	extrusion3def->SetSketch(sketch6);
	extrusion3->Create();

	//отверстие в недоухе
	ksEntityPtr sketch7 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch7Def = sketch7->GetDefinition();
	sketch7Def->SetPlane(plane1);
	sketch7->Create();
	ksDocument2DPtr doc2D7 = sketch7Def->BeginEdit();
    doc2D7->ksCircle(0, -H2 + L2 / 2.0, R4, 1);
	sketch7Def->EndEdit();

	//вырезание отверстия в недоухе
	ksEntityPtr Cut4 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr Cut4def = Cut4->GetDefinition();
	Cut4def->directionType = dtNormal;
	Cut4def->SetSketch(sketch7);
	Cut4def->SetSideParam(true, etUpToNearSurface, 0, 0, FALSE);
	Cut4->Create();

	//эскиз дня полуцилиндра
	ksEntityPtr sketch8 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch8Def = sketch8->GetDefinition();
	sketch8Def->SetPlane(basePlane2);
	sketch8->Create();
	ksDocument2DPtr doc2D8 = sketch8Def->BeginEdit();
	doc2D8->ksArcBy3Points(L6 - D1 / 2.0, 0, L6, -D1 / 2.0, L6 + D1 / 2.0, 0, 1);
	doc2D8->ksLineSeg(L6 - D1 / 2.0, 0, L6 + D1 / 2.0, 0, 1);
	sketch8Def->EndEdit();

	//выдавливание полуцилиндра
	ksEntityPtr extrusion4 = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusion4def = extrusion4->GetDefinition();
	extrusion4def->directionType = dtBoth;
	extrusion4def->SetSideParam(false, etBlind, L4, 0, TRUE);
	extrusion4def->SetSideParam(true, etBlind, L5, 0, TRUE);
	extrusion4def->SetSketch(sketch8);
	extrusion4->Create();

	//касательная плоскость к главному цилиндру
	ksEntityPtr planeplo = part->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr planeplodef = planeplo->GetDefinition();
	ksEntityPtr basePlane3 = part->GetDefaultEntity(o3d_planeYOZ);
	ksPlaneOffsetDefinitionPtr baseplane3def = basePlane3->GetDefinition();
	planeplodef->direction = TRUE;
	planeplodef->offset = -D1 / 2.0;
	planeplodef->SetPlane(basePlane3);
	planeplo->Create();

	//эскиз для площадки
	ksEntityPtr sketch9 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch9Def = sketch9->GetDefinition();
	sketch9Def->SetPlane(planeplo);
	sketch9->Create();
	ksDocument2DPtr doc2D9 = sketch9Def->BeginEdit();
	doc2D9->ksLineSeg(0, L8, -H4, L8, 1);
	doc2D9->ksLineSeg(-H4, L8, -H4, -L9, 1);
	doc2D9->ksLineSeg(-H4, -L9, 0, -L9, 1);
	doc2D9->ksLineSeg(0, -L9, 0, L8, 1);
	sketch9Def->EndEdit();

	//выдавливание площадки
	ksEntityPtr extrusion5 = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusion5def = extrusion5->GetDefinition();
	extrusion5def->directionType = dtBoth;
	extrusion5def->SetSideParam(false, etUpToNearSurface, 0, 0, TRUE);
	extrusion5def->SetSideParam(true, etUpToNearSurface, 0, 0, TRUE);
	extrusion5def->SetSketch(sketch9);
	extrusion5->Create();

	//эскиз левого уха
	ksEntityPtr sketch10 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch10Def = sketch10->GetDefinition();
	sketch10Def->SetPlane(basePlane1);
	sketch10->Create();
	ksDocument2DPtr doc2D10 = sketch10Def->BeginEdit();
	double L11b = (L11 - 2 * D1 / 2.0 - L6)/2+D1 / 2.0;
	doc2D10->ksLineSeg(L6, L9-L10, L6+L11b, L9 - L10, 1);
	doc2D10->ksArcBy3Points(L6 + L11b, L9 - L10, L6 + L11b+L10/2, L9-0.5*L10, L6 + L11b, L9, 1);
	doc2D10->ksLineSeg(L6, L9, L6 + L11b, L9, 1);
	doc2D10->ksLineSeg(L6, L9 - L10, L6, L9, 1);
	doc2D10->ksCircle(L6 + L11b, L9 - 0.5 * L10, D3 / 2.0, 1);
	sketch10Def->EndEdit();

    //выдавливание левого уха
	ksEntityPtr extrusion6 = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusion6def = extrusion6->GetDefinition();
	extrusion6def->directionType = dtNormal;
	extrusion6def->SetSideParam(true, etBlind, H4, 0, TRUE);
	extrusion6def->SetSketch(sketch10);
	extrusion6->Create();

	//эскиз правого уха
	ksEntityPtr sketch11 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch11Def = sketch11->GetDefinition();
	sketch11Def->SetPlane(basePlane1);
	sketch11->Create();
	ksDocument2DPtr doc2D11 = sketch11Def->BeginEdit();
	doc2D11->ksLineSeg(-sqrt(pow(D1 / 2.0, 2) - pow(L10 / 2, 2)), -L10 / 2, -L11b, -L10/2, 1);
	doc2D11->ksArcBy3Points(-L11b, -L10 / 2, -L11b-L10/2, 0,-L11b, L10 / 2, 1);
	doc2D11->ksLineSeg(-sqrt(pow(D1 / 2.0, 2) - pow(L10 / 2, 2)), L10 / 2, -L11b, L10 / 2, 1);
	doc2D11->ksArcBy3Points(-sqrt(pow(D1 / 2.0, 2) - pow(L10 / 2, 2)), -L10 / 2, -D1 / 2.0, 0, -sqrt(pow(D1 / 2.0, 2) - pow(L10 / 2, 2)), L10 / 2, 1);
	doc2D11->ksCircle(-L11b, 0, D3 / 2.0, 1);
	sketch11Def->EndEdit();

	//выдавливание правого уха
	ksEntityPtr extrusion7 = part->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr extrusion7def = extrusion7->GetDefinition();
	extrusion7def->directionType = dtNormal;
	extrusion7def->SetSideParam(true, etBlind, H4, 0, TRUE);
	extrusion7def->SetSketch(sketch11);
	extrusion7->Create();

	//эскиз вырезание в полуцилиндре
	ksEntityPtr sketch12 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketch12Def = sketch12->GetDefinition();
	sketch12Def->SetPlane(basePlane2);
	sketch12->Create();
	ksDocument2DPtr doc2D12 = sketch12Def->BeginEdit();
	doc2D12->ksArcBy3Points(L6 - R1, 0, L6, -R1, L6 + R1, 0, 1);
	doc2D12->ksLineSeg(L6 - R1, 0, L6 + R1, 0, 1);
	sketch12Def->EndEdit();

	//вырезание в полуцилиндре
	ksEntityPtr Cut5 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr Cut5def = Cut5->GetDefinition();
	Cut5def->directionType = dtBoth;
	Cut5def->SetSketch(sketch12);
	Cut5def->SetSideParam(true, etThroughAll, 0, 0, FALSE);
	Cut5def->SetSideParam(false, etThroughAll, 0, 0, FALSE);
	Cut5->Create();

	//добавление скруглений
	ksEntityPtr Rounding1 = part->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr Rounding1Def = Rounding1->GetDefinition();
	Rounding1Def->radius = R2;
	Rounding1Def->tangent = FALSE;
	ksEntityCollectionPtr Rounding1Collection = part->EntityCollection(o3d_edge);
	ksEntityCollectionPtr Rounding1Array = Rounding1Def->array();
	Rounding1Array->Clear();
	for (int i=0; i < Rounding1Collection->GetCount(); i++)
	{
		ksEntityPtr edg = Rounding1Collection->GetByIndex(i);
	    ksEdgeDefinitionPtr def = edg->GetDefinition();
		if (def->GetOwnerEntity() == extrusion)//цилиндр
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			if (z1 == H1 && x1==D1 / 2.0)
			{
				Rounding1Array->Add(edg);
			}
		}
		if (def->GetOwnerEntity() == extrusion6)//левое ухо
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			if (z1 != 0 && z2 != 0 && y1 != L9 - 0.5 * L10 && x1 != L6 + L11b - R4)
			{
				Rounding1Array->Add(edg);
			}
		}
		if (def->GetOwnerEntity() == extrusion7)//правое ухо
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			if (z1 != 0 && z2 != 0 && y1 != 0)
			{
				Rounding1Array->Add(edg);
			}
		}
		if (def->GetOwnerEntity() == extrusion3)//полуухо
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);

			//y1 = (int)(y1 + 0.5);
			//y2 = (int)(y2 + 0.5);
			if (abs(y1-L1)>0.001 && abs(y2-L1)>0.001)
			{
				Rounding1Array->Add(edg);
			}
		}
		if (def->GetOwnerEntity() == extrusion2)//ребро жесткости
		{
			Rounding1Array->Add(edg);
		}
		if (def->GetOwnerEntity() == extrusion5)//платформа
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			if ((y1!=-L8 && y2 != -L8)&&(z2==H4 || (y1==L9 && x2 != L6 - D1 / 2.0 && x1 != L6 - D1 / 2.0)))
			{
				Rounding1Array->Add(edg); 
			}

		}
		if (def->GetOwnerEntity() == extrusion4)
		{
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			p1->GetPoint(&x1, &y1, &z1);
			p2->GetPoint(&x2, &y2, &z2);
			if (y1!=L5 && y1!=-L4 && y2!=L5)
			{
				Rounding1Array->Add(edg);
			}

		}
	}
	
	Rounding1->Create();
	doc->hideAllPlanes = true;
	doc->hideAllAxis = true;
}

void CKursachDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (Proverka())
	{
		Start(); 
	}

}
