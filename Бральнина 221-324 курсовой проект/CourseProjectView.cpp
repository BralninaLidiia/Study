
// CourseProjectView.cpp: реализация класса CCourseProjectView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CourseProject.h"
#endif

#include "CourseProjectDoc.h"
#include "CourseProjectView.h"
#include "resource.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Gr_to_Rad(angle) ((angle) * (4 * atan(1) / 180.0))


// CCourseProjectView

IMPLEMENT_DYNCREATE(CCourseProjectView, CView)

BEGIN_MESSAGE_MAP(CCourseProjectView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_NEST_1, IDC_BUTTON_NEST_6, &CCourseProjectView::OnButtonClick)
END_MESSAGE_MAP()

// Создание или уничтожение CCourseProjectView

CCourseProjectView::CCourseProjectView() noexcept
{
	// TODO: добавьте код создания

}

CCourseProjectView::~CCourseProjectView()
{
}

BOOL CCourseProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CCourseProjectView

void CCourseProjectView::CreatePartNest(stNest& st)
{
	CoInitialize(NULL);
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
	doc2D->ksLineSeg(0, st.d / 2.f, 0, st.D / 2.f, 1);
	doc2D->ksLineSeg(0, st.D / 2.f, st.l, st.D / 2.f, 1);
	doc2D->ksLineSeg(st.l, st.D / 2.f, st.l, st.d / 2.f, 1);
	doc2D->ksLineSeg(st.l, st.d / 2.f, 0, st.d / 2.f, 1);
	doc2D->ksLineSeg(0, 0, 10, 0, 3); //осевая
	sketchDef->EndEdit();

	//операция вращения:
	ksEntityPtr rotation = part->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr rotationDef = rotation->GetDefinition();
	rotationDef->SetSideParam(TRUE, 360);
	rotationDef->directionType = dtNormal;
	rotationDef->SetSketch(sketch);
	rotation->Create();

	//операция резьба
	ksEntityPtr pTHread = part->NewEntity(o3d_thread);
	ksThreadDefinitionPtr pTHreadDef = pTHread->GetDefinition();
	pTHreadDef->length = st.l;
	pTHreadDef->dr = st.DRez;
	pTHreadDef->faceValue = true;
	pTHreadDef->p = st.Step;
	ksEntityCollectionPtr Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(0, st.d / 2.f, 0);
	pTHreadDef->SetBaseObject(Collection->First());
	pTHread->Create();

	//операция фаска
	ksEntityPtr Chamfers = part->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr ChamfersDef = Chamfers->GetDefinition();
	ChamfersDef->SetChamferParam(true, st.Step, st.Step);
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(0, st.d / 2.f, 0);
	ksEntityCollectionPtr CollectionChamfers = ChamfersDef->array();
	CollectionChamfers->Add(Collection->First());
	Chamfers->Create();

	//операция сохранения детали
	CString name = L"Гнездо сальника типа СКПТ";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".m3d";
	doc->SaveAs(_bstr_t(st.filePath));
	
}

void CCourseProjectView::CreatePartNutBolt(stNutBolt& st)
{
	CoInitialize(NULL);
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
	doc2D->ksLineSeg(0, st.d / 2.f, 0, st.D / 2.f, 1);
	doc2D->ksLineSeg(0, st.D / 2.f, 0.4f * st.l / 2.f, st.D / 2.f, 1);
	doc2D->ksLineSeg(0.4f * st.l / 2.f, st.D / 2.f, 0.4f * st.l / 2.f, st.d / 2.f + (st.DRez-st.d) / 4.f, 1);
	doc2D->ksLineSeg(0.4f * st.l / 2.f, st.d / 2.f + (st.DRez - st.d) / 4.f, 0.4f * st.l, st.d / 2.f + (st.DRez - st.d) / 4.f, 1);
	doc2D->ksLineSeg(0.4f * st.l, st.d / 2.f + (st.DRez - st.d) / 4.f, 0.4f * st.l, st.DRez / 2.f, 1);
	doc2D->ksLineSeg(0.4f * st.l, st.DRez / 2.f, st.l, st.DRez / 2.f, 1);
	doc2D->ksLineSeg(st.l, st.DRez / 2.f, st.l, st.d / 2.f, 1);
	doc2D->ksLineSeg(st.l, st.d / 2.f, 0, st.d / 2.f, 1);
	doc2D->ksLineSeg(0, 0, 10, 0, 3); //осевая
	sketchDef->EndEdit();

	//операция вращения:
	ksEntityPtr rotation = part->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr rotationDef = rotation->GetDefinition();
	rotationDef->SetSideParam(TRUE, 360);
	rotationDef->directionType = dtNormal;
	rotationDef->SetSketch(sketch);
	rotation->Create();

	//операция резьба
	ksEntityPtr pTHread = part->NewEntity(o3d_thread);
	ksThreadDefinitionPtr pTHreadDef = pTHread->GetDefinition();
	pTHreadDef->length = st.l - st.l * 0.4;
	pTHreadDef->dr = st.DRez;
	pTHreadDef->faceValue = true;
	pTHreadDef->p = st.Step;
	ksEntityCollectionPtr Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(st.l, st.DRez / 2.f, 0);
	pTHreadDef->SetBaseObject(Collection->First());
	pTHread->Create();

	//операция фаска
	ksEntityPtr Chamfers = part->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr ChamfersDef = Chamfers->GetDefinition();
	ChamfersDef->SetChamferParam(true, st.Step, st.Step);
	Collection->Clear();
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(st.l, st.DRez / 2.f, 0);
	ksEntityCollectionPtr CollectionChamfers = ChamfersDef->array();
	CollectionChamfers->Add(Collection->First());
	Chamfers->Create();

	//эскиз для вырезания шестиугольника
	ksEntityPtr sketch2 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef2 = sketch2->GetDefinition();
	sketchDef2->SetPlane(part->GetDefaultEntity(o3d_planeYOZ));
	sketch2->Create();
	ksDocument2DPtr doc2D2 = sketchDef2->BeginEdit();
	doc2D2->ksLineSeg(0, st.D / 2.f, cos(Gr_to_Rad(30)) * (st.D / 2.f), sin(Gr_to_Rad(30)) * (st.D / 2.f), 1);
	doc2D2->ksLineSeg(cos(Gr_to_Rad(30)) * (st.D / 2.f), sin(Gr_to_Rad(30)) * (st.D / 2.f), cos(Gr_to_Rad(30)) * (st.D / 2.f), -1 * sin(Gr_to_Rad(30)) * (st.D / 2.f), 1);
	doc2D2->ksLineSeg(cos(Gr_to_Rad(30)) * (st.D / 2.f), -1 * sin(Gr_to_Rad(30)) * (st.D / 2.f), 0, -st.D / 2.f, 1);
	doc2D2->ksLineSeg(0, -st.D / 2.f, -cos(Gr_to_Rad(30)) * (st.D / 2.f), -sin(Gr_to_Rad(30)) * (st.D / 2.f), 1);
	doc2D2->ksLineSeg(-cos(Gr_to_Rad(30)) * (st.D / 2.f), -sin(Gr_to_Rad(30)) * (st.D / 2.f), -cos(Gr_to_Rad(30)) * (st.D / 2.f), sin(Gr_to_Rad(30)) * (st.D / 2.f), 1);
	doc2D2->ksLineSeg(-cos(Gr_to_Rad(30)) * (st.D / 2.f), sin(Gr_to_Rad(30)) * (st.D / 2.f), 0, st.D / 2.f, 1);
	doc2D2->ksCircle(0, 0, st.D / 2.f + 0.001f, 1);
	sketchDef2->EndEdit();

	//операция вырез выдавливание
	ksEntityPtr CutExtr2 = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr CutExtrDef2 = CutExtr2->GetDefinition();
	CutExtrDef2->directionType = dtNormal;
	CutExtrDef2->SetSketch(sketch2);
	CutExtrDef2->SetSideParam(TRUE, etBlind, 0.4f * st.l / 2.f, 0, FALSE);
	CutExtr2->Create();

	//операция фаска
	ksEntityPtr Chamfers2 = part->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr ChamfersDef2 = Chamfers2->GetDefinition();
	ChamfersDef2->SetChamferParam(true, st.Step, st.Step);
	Collection->Clear();
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(0, st.d / 2.f, 0);
	ksEntityCollectionPtr CollectionChamfers2 = ChamfersDef2->array();
	CollectionChamfers2->Add(Collection->First());
	Chamfers2->Create();

	//операция сохранения детали
	CString name = L"Гайка нажимная";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".m3d";
	doc->SaveAs(_bstr_t(st.filePath));
}

void CCourseProjectView::CreatePartPuck(stPuck& st)
{
	CoInitialize(NULL);
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

	//операция эскиз
	ksEntityPtr sketch = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
	sketchDef->SetPlane(part->GetDefaultEntity(o3d_planeXOY));
	sketch->Create();
	ksDocument2DPtr doc2D = sketchDef->BeginEdit();
	doc2D->ksLineSeg(0, st.d / 2.f, 0, st.D / 2.f, 1);
	doc2D->ksLineSeg(0, st.D / 2.f, st.s, st.D / 2.f, 1);
	doc2D->ksLineSeg(st.s, st.D / 2.f, st.s, st.d / 2.f, 1);
	doc2D->ksLineSeg(st.s, st.d / 2.f, 0, st.d / 2.f, 1);
	doc2D->ksLineSeg(0, 0, 10, 0, 3); //осевая
	sketchDef->EndEdit();

	//операция вращения
	ksEntityPtr rotation = part->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr rotationDef = rotation->GetDefinition();
	rotationDef->SetSideParam(TRUE, 360);
	rotationDef->directionType = dtNormal;
	rotationDef->SetSketch(sketch);
	rotation->Create();

	//операция сохранения детали
	CString name = L"Шайба";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".m3d";
	doc->SaveAs(_bstr_t(st.filePath));
}

void CCourseProjectView::CreateOilSeal(stNest stNest, stNutBolt stNutBolt, stPuck stPuck, stOilSeal& st)
{
	CoInitialize(NULL);
	HRESULT hRes;
	hRes = kompas.GetActiveObject(L"Kompas.Application.5");
	if (FAILED(hRes))
		kompas.CreateInstance(L"Kompas.Application.5");
	kompas->Visible = true;

	//создание документа КОМПАС:
	ksDocument3DPtr doc;
	doc = kompas->Document3D();
	doc->Create(false, false);
	doc = kompas->ActiveDocument3D();
	ksPartPtr part;
	part = doc->GetPart(pTop_Part);

	//добавление детали "гнездо"
	doc->SetPartFromFile(_bstr_t(stNest.filePath), part, TRUE);
	//грань
	ksPartPtr partNest = doc->GetPart(0);
	ksEntityCollectionPtr nestCollection = partNest->EntityCollection(o3d_face);
	ksEntityPtr nestEntity;
	nestCollection->SelectByPoint(0, stNest.D / 2.f - 0.001f, 0);
	nestEntity = nestCollection->First();
	//ребро
	nestCollection->Clear();
	nestCollection = partNest->EntityCollection(o3d_edge);
	ksEntityPtr nestEdge;
	nestCollection->SelectByPoint(0, stNest.D / 2.f, 0);
	nestEdge = nestCollection->First();

	//добавление детали "гайка"
	doc->SetPartFromFile(_bstr_t(stNutBolt.filePath), part, TRUE);
	//грань
	ksPartPtr partNutBolt = doc->GetPart(1); 
	ksEntityCollectionPtr NutBoltCollection = partNutBolt->EntityCollection(o3d_face);
	ksEntityPtr NutBoltEntity;
	NutBoltCollection->SelectByPoint(stNutBolt.l * 0.2f, stNutBolt.DRez / 2.f, 0);
	NutBoltEntity = NutBoltCollection->First();
	//грань 2
	ksEntityPtr NutBoltEntity2;
	NutBoltCollection->Clear();
	NutBoltCollection = partNutBolt->EntityCollection(o3d_face);
	NutBoltCollection->SelectByPoint(stNutBolt.l, stNutBolt.d / 2.f + 0.1f, 0);
	NutBoltEntity2 = NutBoltCollection->First();
	
	//ребро
	NutBoltCollection->Clear();
	NutBoltCollection = partNutBolt->EntityCollection(o3d_edge);
	ksEntityPtr NutBoltEdge;
	NutBoltCollection->SelectByPoint(stNutBolt.l, stNutBolt.d / 2.f, 0);
	NutBoltEdge = NutBoltCollection->First();

	//добавление детали "шайба"
	doc->SetPartFromFile(_bstr_t(stPuck.filePath), part, TRUE);
	//грань 
	ksPartPtr partPuck = doc->GetPart(2);
	ksEntityCollectionPtr PuckCollection = partPuck->EntityCollection(o3d_face);
	ksEntityPtr PuckEntity;
	PuckCollection->SelectByPoint(0, stPuck.D / 2.f - 0.001f, 0);
	PuckEntity = PuckCollection->First();
	//ребро
	PuckCollection->Clear();
	PuckCollection = partPuck->EntityCollection(o3d_edge);
	ksEntityPtr PuckEdge;
	PuckCollection->SelectByPoint(0, stPuck.D / 2.f, 0);
	PuckEdge = PuckCollection->First();

	//устанавливаем сопряжения
	doc->AddMateConstraint(mc_Concentric, nestEdge, NutBoltEdge, -1, 1, NULL);
	doc->AddMateConstraint(mc_Coincidence, nestEntity, NutBoltEntity, 0, 0, NULL);
	doc->AddMateConstraint(mc_Concentric, PuckEdge, NutBoltEdge, -1, 0, NULL);
	doc->AddMateConstraint(mc_Coincidence, PuckEntity, NutBoltEntity2, -1, 0, NULL);

	//операция сохранения детали
	CString name = L"Сальник трубный типа СКПТ";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".a3d";
	doc->SaveAs(_bstr_t(st.filePath));
}

void CCourseProjectView::OnDraw(CDC* pDC)
{
	CCourseProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	CRect clientRect;
	GetClientRect(&clientRect);
	
	int Height = clientRect.Height();	//Высота окна
	int Width = clientRect.Width();		//Ширина окна

	auto ImageCreate = [pDC, Width](CString name_file) ->int
	{
			CImage image;
			image.Load(name_file);

			if (image.IsNull())
			{
				AfxMessageBox(L"Ошибка загрузки картинки");
				return 0;
			}

			int imageWidth = image.GetWidth();		//Ширина картинки
			int imageHeight = image.GetHeight();	//Высота картинки

			image.StretchBlt
			(
				pDC->GetSafeHdc(), Width / 2.f - imageWidth / 2.f, 0, 
				imageWidth, imageHeight, 0, 0, 
				imageWidth, imageHeight, SRCCOPY
			);

			return imageHeight;
	};

	if (pDoc->m_bNest)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);
		
		int imageHeight = ImageCreate(L"res\\Nest.jpg");
		int x = 0;
		int y = imageHeight + 15;
		double cellWidth = Width / 5.f;
		int cellHeight = 30;
		
		// шапка
		{
			CString NutBoltBuff[5] = { L"№ исполнения", L"Обозначение резьбы", L"D", L"L", L"Macca" };

			for (int i = 0; i < 5; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(NutBoltBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение
		{
			for (int i = 0; i < 6; i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + cellWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += cellWidth;

				for (int g = 0; g < 5; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecNest[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}

		pDC->SelectObject(pOldFont);
	}
	else if (pDoc->m_bNutBolt)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);

		int imageHeight = ImageCreate(L"res\\NutBolt.jpg");
		int x = 0;
		int y = imageHeight + 10;
		double cellWidth = Width / 7.f;
		int cellHeight = 30;

		//шапка
		{
			CString NutBoltBuff[7] = { L"№ исполнения", L"d", L"Обозначение резьбы", L"D", L"s", L"l", L"Macca, кг"};

			for (int i = 0; i < 7; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(NutBoltBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение
		{
			for (int i = 0; i < 6; i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + cellWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += cellWidth;

				for (int g = 0; g < 6; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecNutBolt[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}

		pDC->SelectObject(pOldFont);
	}
	else if (pDoc->m_bPuck)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);

		int imageHeight = ImageCreate(L"res\\Puck.jpg");
		int x = 0;
		int y = imageHeight + 15;
		double cellWidth = Width / 5.f;
		int cellHeight = 30;

		// шапка
		{
			CString PuckBuff[5] = { L"№ исполнения", L"d", L"D", L"s", L"Macca 100шт., кг, не более" };

			for (int i = 0; i < 5; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(PuckBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение
		{
			for (int i = 0; i < 6; i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + cellWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += cellWidth;

				for (int g = 0; g < 4; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecPuck[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}

		pDC->SelectObject(pOldFont);
	}
	else if (pDoc->m_bOilSeal)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);

		int imageHeight = ImageCreate(L"res\\OilSeal.jpg");
		int x = 0;
		int y = imageHeight + 15;
		double cellWidth = Width / 9.f;
		int cellHeight = 30;

		// Рисование шапки таблицы
		{
			CString OilSealBuff[9] = { L"№ исполнения", L"Типоразмер", L"Наружные D", L"d", L"Обозначение резьбы", L"D", L"L, не более", L"Шайба", L"Macca, кг" };

			for (int i = 0; i < 9; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(OilSealBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение таблицы
		{
			for (int i = 0; i < 6; i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + cellWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += cellWidth;

				for (int g = 0; g < 8; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecOilSeal[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}
		pDC->SelectObject(pOldFont);
	}
	else
	{
		CFont font;
		font.CreatePointFont(300, L"Times New Roman");
		CFont* pOldFont = pDC->SelectObject(&font);
		pDC->DrawText(L"Курсовой проект\r\nБральнина Л.С. гр.221-324", CRect(0, 0, Width, Height), DT_CENTER | DT_VCENTER);
		pDC->SelectObject(pOldFont);
	}

}


// Печать CCourseProjectView

BOOL CCourseProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CCourseProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CCourseProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CCourseProjectView

#ifdef _DEBUG
void CCourseProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CCourseProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCourseProjectDoc* CCourseProjectView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCourseProjectDoc)));
	return (CCourseProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CCourseProjectView


int CCourseProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	
	for (int i = 0; i < 6; i++)
	{
		CString NumberButton;
		NumberButton.Format(L"Исполнение %i", i + 1);
		m_Buttons[i].Create(NumberButton, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, IDC_BUTTON_NEST_1 + i);
	}

	//Исполнение 1
	{
		stNest stn1;
		stn1.D = 20.f;
		stn1.l = 15.f;
		stn1.d = 14.917468f;
		stn1.Step = 1.f;
		stn1.DRez = 16.f;
		stn1.name[0] = L"M16x1";
		stn1.name[1] = L"20";
		stn1.name[2] = L"15";
		stn1.name[3] = L"0,02";
		vecNest.push_back(stn1);

		stNutBolt stnb1;
		stnb1.d = 10.f;
		stnb1.D = 21.9;
		stnb1.l = 17.f;
		stnb1.DRez = 16.f;
		stnb1.Step = 1.f;
		stnb1.name[0] = L"10";
		stnb1.name[1] = L"M16x1";
		stnb1.name[2] = L"21,9";
		stnb1.name[3] = L"19";
		stnb1.name[4] = L"17";
		stnb1.name[5] = L"0,02";
		vecNutBolt.push_back(stnb1);

		stPuck stp1;
		stp1.d = 8.f;
		stp1.D = 14.f;
		stp1.s = 1.5;
		stp1.name[0] = L"8";
		stp1.name[1] = L"14";
		stp1.name[2] = L"1,5";
		stp1.name[3] = L"0,22";
		vecPuck.push_back(stp1);

		stOilSeal stos1;
		stos1.name[0] = L"СКПТ16";
		stos1.name[1] = L"От 4 до 8";
		stos1.name[2] = L"10";
		stos1.name[3] = L"M16x1";
		stos1.name[4] = L"21,9''";
		stos1.name[5] = L"29";
		stos1.name[6] = L"8x14";
		stos1.name[7] = L"0,03";
		vecOilSeal.push_back(stos1);
	}

	//Исполнение 2
	{
		stNest stn2;
		stn2.D = 32.f;
		stn2.l = 23.f;
		stn2.d = 25.376202f;
		stn2.Step = 1.5f;
		stn2.DRez = 27.f;
		stn2.name[0] = L"M27x1,5";
		stn2.name[1] = L"32";
		stn2.name[2] = L"23";
		stn2.name[3] = L"0,05";
		vecNest.push_back(stn2);

		stNutBolt stnb2;
		stnb2.d = 20.f;
		stnb2.D = 36.9f;
		stnb2.l = 23.f;
		stnb2.DRez = 27.f;
		stnb2.Step = 1.5f;
		stnb2.name[0] = L"20";
		stnb2.name[1] = L"M27x1,5"; 
		stnb2.name[2] = L"36,9";
		stnb2.name[3] = L"32";
		stnb2.name[4] = L"23";
		stnb2.name[5] = L"0,04";
		vecNutBolt.push_back(stnb2);

		stPuck stp2;
		stp2.d = 16.f;
		stp2.D = 24.f;
		stp2.s = 2.f;
		stp2.name[0] = L"16";
		stp2.name[1] = L"24";
		stp2.name[2] = L"2";
		stp2.name[3] = L"0.39";
		vecPuck.push_back(stp2);

		stOilSeal stos2;
		stos2.name[0] = L"СКПТ27";
		stos2.name[1] = L"От 8 до 18";
		stos2.name[2] = L"20";
		stos2.name[3] = L"M27x1,5";
		stos2.name[4] = L"36,9";
		stos2.name[5] = L"41";
		stos2.name[6] = L"16x24";
		stos2.name[7] = L"0,09";
		vecOilSeal.push_back(stos2);
	}

	//Исполнение 3
	{
		stNest stn3;
		stn3.D = 48.f;
		stn3.l = 31.f;
		stn3.d = 39.834936;
		stn3.Step = 2.f;
		stn3.DRez = 42.f;
		stn3.name[0] = L"M42x2";
		stn3.name[1] = L"48";
		stn3.name[2] = L"31";
		stn3.name[3] = L"0,12";
		vecNest.push_back(stn3);

		stNutBolt stnb3;
		stnb3.d = 32.f;
		stnb3.D = 53.f;
		stnb3.l = 32.f;
		stnb3.DRez = 42.f;
		stnb3.Step = 2.f;
		stnb3.name[0] = L"32";
		stnb3.name[1] = L"M42x2";
		stnb3.name[2] = L"53,0";
		stnb3.name[3] = L"46";
		stnb3.name[4] = L"32";
		stnb3.name[5] = L"0,13";
		vecNutBolt.push_back(stnb3);

		stPuck stp3;
		stp3.d = 30.f;
		stp3.D = 38.f;
		stp3.s = 3.f;
		stp3.name[0] = L"30";
		stp3.name[1] = L"38";
		stp3.name[2] = L"3";
		stp3.name[3] = L"1,69";
		vecPuck.push_back(stp3);
		
		stOilSeal stos3;
		stos3.name[0] = L"СКПТ42";
		stos3.name[1] = L"От 18 до 30";
		stos3.name[2] = L"32";
		stos3.name[3] = L"M42x2";
		stos3.name[4] = L"53,0";
		stos3.name[5] = L"56";
		stos3.name[6] = L"30x38";
		stos3.name[7] = L"0,27";
		vecOilSeal.push_back(stos3);
	}

	//Исполнение 4
	{
		stNest stn4;
		stn4.D = 68.f;
		stn4.l = 35.f;
		stn4.d = 56.752405f;
		stn4.Step = 3.f;
		stn4.DRez = 60.f;
		stn4.name[0] = L"M60x3";
		stn4.name[1] = L"68";
		stn4.name[2] = L"35";
		stn4.name[3] = L"0,33";
		vecNest.push_back(stn4);

		stNutBolt stnb4;
		stnb4.d = 45.f;
		stnb4.D = 75.f;
		stnb4.l = 37.f;
		stnb4.DRez = 60.f;
		stnb4.Step = 3.f;
		stnb4.name[0] = L"45";
		stnb4.name[1] = L"M60x3";
		stnb4.name[2] = L"75,0";
		stnb4.name[3] = L"65";
		stnb4.name[4] = L"37";
		stnb4.name[5] = L"0,34";
		vecNutBolt.push_back(stnb4);

		stPuck stp4;
		stp4.d = 36.f;
		stp4.D = 55.f;
		stp4.s = 3.f;
		stp4.name[0] = L"36";
		stp4.name[1] = L"55";
		stp4.name[2] = L"3";
		stp4.name[3] = L"3,20";
		vecPuck.push_back(stp4);

		stOilSeal stos4;
		stos4.name[0] = L"СКПТ60";
		stos4.name[1] = L"От 30 до 40";
		stos4.name[2] = L"45";
		stos4.name[3] = L"M60x3";
		stos4.name[4] = L"75,0";
		stos4.name[5] = L"64";
		stos4.name[6] = L"36x55";
		stos4.name[7] = L"0,71";
		vecOilSeal.push_back(stos4);
	}

	//Исполнение 5
	{
		stNest stn5;
		stn5.D = 85.f;
		stn5.l = 38.f;
		stn5.d = 72.752405f;
		stn5.Step = 3.f;
		stn5.DRez = 76.f;
		stn5.name[0] = L"M76x3";
		stn5.name[1] = L"85";
		stn5.name[2] = L"38";
		stn5.name[3] = L"0,33";
		vecNest.push_back(stn5);

		stNutBolt stnb5;
		stnb5.d = 60.f;
		stnb5.D = 92.4f;
		stnb5.l = 40.f;
		stnb5.DRez = 76.f;
		stnb5.Step = 3.f;
		stnb5.name[0] = L"60";
		stnb5.name[1] = L"M76x3";
		stnb5.name[2] = L"92,4";
		stnb5.name[3] = L"80";
		stnb5.name[4] = L"40";
		stnb5.name[5] = L"0,51";
		vecNutBolt.push_back(stnb5);

		stPuck stp5;
		stp5.d = 48.f;
		stp5.D = 71.f;
		stp5.s = 3.f;
		stp5.name[0] = L"48";
		stp5.name[1] = L"71";
		stp5.name[2] = L"3";
		stp5.name[3] = L"5,06";
		vecPuck.push_back(stp5);

		stOilSeal stos5;
		stos5.name[0] = L"СКПТ76";
		stos5.name[1] = L"От 40 до 56";
		stos5.name[2] = L"60";
		stos5.name[3] = L"M76x3";
		stos5.name[4] = L"92,4";
		stos5.name[5] = L"69";
		stos5.name[6] = L"48x71";
		stos5.name[7] = L"0,90";
		vecOilSeal.push_back(stos5);
	}

	//Исполнение 6
	{
		stNest stn6;
		stn6.D = 100.f;
		stn6.l = 40.f;
		stn6.d = 86.752405f;
		stn6.Step = 3.f;
		stn6.DRez = 90.f;
		stn6.name[0] = L"M90x3";
		stn6.name[1] = L"100";
		stn6.name[2] = L"40";
		stn6.name[3] = L"0,65";
		vecNest.push_back(stn6);

		stNutBolt stnb6;
		stnb6.d = 80.f;
		stnb6.D = 103.9f;
		stnb6.l = 41.f;
		stnb6.DRez = 90.f;
		stnb6.Step = 3.f;
		stnb6.name[0] = L"80";
		stnb6.name[1] = L"M90x3";
		stnb6.name[2] = L"103,9";
		stnb6.name[3] = L"90";
		stnb6.name[4] = L"41";
		stnb6.name[5] = L"0,35";
		vecNutBolt.push_back(stnb6);

		stPuck stp6;
		stp6.d = 70.f;
		stp6.D = 84.f;
		stp6.s = 3.f;
		stp6.name[0] = L"70";
		stp6.name[1] = L"84";
		stp6.name[2] = L"3";
		stp6.name[3] = L"3,99";
		vecPuck.push_back(stp6);

		stOilSeal stos6;
		stos6.name[0] = L"СКПТ90";
		stos6.name[1] = L"От 56 до 70";
		stos6.name[2] = L"80";
		stos6.name[3] = L"M90x3";
		stos6.name[4] = L"103,9";
		stos6.name[5] = L"72";
		stos6.name[6] = L"70x84";
		stos6.name[7] = L"1,06";
		vecOilSeal.push_back(stos6);
	}

	return 0;
}

void CCourseProjectView::OnButtonClick(UINT nID)
{
	int buttonIndex = nID - IDC_BUTTON_NEST_1;
	m_sfilePath = L"C:\\Users\\ЦИФРОСКУПКА\\Desktop\\курсач";
	CString numberIsp;
	numberIsp.Format(L"Исполнение %i", buttonIndex + 1);
	CString targetPath = m_sfilePath + L"\\" + numberIsp;
	if (!CreateDirectory(targetPath, NULL))
	{
		DWORD error = GetLastError();
		if (error == ERROR_ALREADY_EXISTS)
		{
			int index = 1;
			while (true)
			{
				CString indexStr;
				indexStr.Format(L"%i", index);
				CString newFolderName = numberIsp + L" (" + indexStr + L")";
				CString newPath = m_sfilePath + L"\\" + newFolderName;
				if (CreateDirectory(newPath, NULL))
				{
					m_sfilePath = newPath;
					break;
				}
				index++;
			}
		}
		else
			AfxMessageBox(L"Ошибка при создании папки");
	}
	else
	{
		CreateDirectory(targetPath, NULL);
		m_sfilePath = targetPath;
	}

	switch (buttonIndex)
	{
	case 0:
		CreatePartNest(vecNest[0]);
		CreatePartNutBolt(vecNutBolt[0]);
		CreatePartPuck(vecPuck[0]);
		CreateOilSeal(vecNest[0], vecNutBolt[0], vecPuck[0], vecOilSeal[0]);
		break;
	case 1:
		CreatePartNest(vecNest[1]);
		CreatePartNutBolt(vecNutBolt[1]);
		CreatePartPuck(vecPuck[1]);
		CreateOilSeal(vecNest[1], vecNutBolt[1], vecPuck[1], vecOilSeal[1]);
		break;
	case 2:
		CreatePartNest(vecNest[2]);
		CreatePartNutBolt(vecNutBolt[2]);
		CreatePartPuck(vecPuck[2]);
		CreateOilSeal(vecNest[2], vecNutBolt[2], vecPuck[2], vecOilSeal[2]);
		break;
	case 3:
		CreatePartNest(vecNest[3]);
		CreatePartNutBolt(vecNutBolt[3]);
		CreatePartPuck(vecPuck[3]);
		CreateOilSeal(vecNest[3], vecNutBolt[3], vecPuck[3], vecOilSeal[3]);
		break;
	case 4:
		CreatePartNest(vecNest[4]);
		CreatePartNutBolt(vecNutBolt[4]);
		CreatePartPuck(vecPuck[4]);
		CreateOilSeal(vecNest[4], vecNutBolt[4], vecPuck[4], vecOilSeal[4]);
		break;
	case 5:
		CreatePartNest(vecNest[5]);
		CreatePartNutBolt(vecNutBolt[5]);
		CreatePartPuck(vecPuck[5]);
		CreateOilSeal(vecNest[5], vecNutBolt[5], vecPuck[5], vecOilSeal[5]);
		break;
	}
}
