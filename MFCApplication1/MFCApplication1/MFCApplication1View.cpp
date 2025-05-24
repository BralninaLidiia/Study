
// MFCApplication1View.cpp: реализация класса CMFCApplication1View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 4*atan(1)

// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_OBJECTS_COLOR, &CMFCApplication1View::OnObjectsColor)
END_MESSAGE_MAP()

// Создание или уничтожение CMFCApplication1View

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: добавьте код создания

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMFCApplication1View

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rc;
	GetClientRect(&rc);
	CPen pen(PS_SOLID, 6, m_Color);
	CPen* oldpen = pDC->SelectObject(&pen);

	int Width = rc.right;
	int Heigth = rc.bottom;
	double ScaleX = 2 * PI / Width;
	double ScaleY = 2.f / Heigth;

	auto f = [ScaleX, ScaleY, Heigth, pDoc](double x)
		{
			return pDoc->A / 2000.f * sin(-x * ScaleX * pDoc->B + pDoc->X1) / ScaleY + Heigth / 2.f;
		};

	if (pDoc->m_bCoord)
	{
		pDC->MoveTo(0, Heigth / 2.0);
		pDC->LineTo(Width, Heigth / 2.0);

	}
	
	if (pDoc->m_bShtrih)
	{
		CBrush brush(HS_BDIAGONAL, m_Color_Shtrih);
		CBrush* oldbrush = pDC->SelectObject(&brush);
		CPoint* points = new CPoint[Width + 2];

		points[0].x = 0;
		points[0].y = Heigth / 2.f;

		for (int i = 1; i <= Width; i++)
		{
			points[i].x = i;
			points[i].y = f(i);
		}

		points[Width + 1].x = Width;
		points[Width + 1].y = Heigth / 2.f;

		CRgn rg;
		rg.CreatePolygonRgn(points, Width + 2, ALTERNATE);
		pDC->FillRgn(&rg, &brush);

		pDC->SelectObject(oldbrush);

		delete[] points;
	}
	
	pDC->MoveTo(0, f(0));


	if (pDoc->m_bSin)
	{
		CPen pen1(PS_SOLID, 4, m_Color_Sin);
		CPen* oldpen1 = pDC->SelectObject(&pen1);
		for (int i = 0; i < Width; i++)
		{
			pDC->LineTo(i, f(i));

		}

	}
	pDC->SelectObject(oldpen);

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CMFCApplication1View

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CMFCApplication1View

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMFCApplication1View




void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	static int buff_x = -1;

	if (GetKeyState(VK_LBUTTON) < 0)
	{
		CMFCApplication1Doc* pDoc = GetDocument();
		if (buff_x == -1)
			buff_x = point.x;
		else
		{
			if (buff_x > point.x)
				pDoc->X1 -= 0.1;
			else
				pDoc->X1 += 0.1;
			buff_x = point.x;
			Invalidate(TRUE);
		}
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CMFCApplication1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CMFCApplication1Doc* pDoc = GetDocument();

	if (GetKeyState(VK_SHIFT) < 0)
	{
		if (zDelta > 0)
			pDoc->B += 1;
		else
			pDoc->B -= 1;
		Invalidate(TRUE);
	}
	else
	{
		pDoc->A += zDelta;
		Invalidate(TRUE);
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	ClientToScreen(&point);
	CCmdUI state;

	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(3);

	state.m_pMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < state.m_nIndexMax; i++)
	{
		state.m_nIndex = i;
		state.m_nID = pMenu->GetMenuItemID(i);
		state.DoUpdate(this, FALSE);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	CView::OnRButtonDown(nFlags, point);
}


void CMFCApplication1View::OnObjectsColor()
{
	// TODO: добавьте свой код обработчика команд

	if(!m_ColorDlg)
		m_ColorDlg.Create(IDD_DIALOG2, this);
	m_ColorDlg.m_ColorCtrl.SetColor(m_Color);
	m_ColorDlg.m_Color_SinCtrl.SetColor(m_Color_Sin);
	m_ColorDlg.m_Color_ShtrihCtrl.SetColor(m_Color_Shtrih);
	m_ColorDlg.pView = this;
	
	m_ColorDlg.ShowWindow(SW_SHOW);

}
