
// OpenGlView.cpp: реализация класса COpenGlView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "OpenGl.h"
#endif

#include "OpenGlDoc.h"
#include "OpenGlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGlView

IMPLEMENT_DYNCREATE(COpenGlView, CView)

BEGIN_MESSAGE_MAP(COpenGlView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
//	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение COpenGlView

COpenGlView::COpenGlView() noexcept
{
	// TODO: добавьте код создания

}

COpenGlView::~COpenGlView()
{
}

BOOL COpenGlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	//cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// Рисование COpenGlView

void COpenGlView::OnDraw(CDC* /*pDC*/)
{
	COpenGlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rt;
	GetClientRect(&rt);

	double Widht = rt.right;
	double Height = rt.bottom;

	ScaleX = 6.f / Widht;
	ScaleY = 6.f / Height;

	// TODO: добавьте здесь код отрисовки для собственных данных
	opengl.Render(pDoc);
}


// Печать COpenGlView

BOOL COpenGlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void COpenGlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void COpenGlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика COpenGlView

#ifdef _DEBUG
void COpenGlView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGlDoc* COpenGlView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGlDoc)));
	return (COpenGlDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений COpenGlView


void COpenGlView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: добавьте специализированный код или вызов базового класса
	
	opengl.SetupPixelFormat(::GetDC(GetSafeHwnd()));
	opengl.Init();
}


void COpenGlView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
	if (cx == 0)
	{
		cx = 1;
	}
	opengl.Reshape(cx, cy);
}


void COpenGlView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL COpenGlView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	COpenGlDoc* pDoc = GetDocument();
	
	float  del = (abs(zDelta) / (100.f * zDelta));
	pDoc->m_Scale += del;
	if (pDoc->m_Scale <= 0)
	{
		pDoc->m_Scale -= del;
	}
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}




void COpenGlView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	COpenGlDoc* pDoc = GetDocument();
	static int buff_x = 0;
	static int buff_y = 0;

	if (GetKeyState(VK_LBUTTON) < 0)
	{
		
		if (buff_x == 0 && buff_y == 0)
		{
			buff_x = point.x;
			buff_y = point.y;
		}
		if (buff_x < point.x && buff_y < point.y)
		{
			pDoc->trans.x += (point.x - buff_x) * ScaleX;
			pDoc->trans.y -= (point.y - buff_y) * ScaleY;
		}
		else
		{
			pDoc->trans.x -= (buff_x - point.x) * ScaleX;
			pDoc->trans.y += (buff_y - point.y) * ScaleY;
		}
		buff_x = point.x;
		buff_y = point.y;
		
		opengl.Render(pDoc);
	}
	else
	{
		buff_x = 0;
		buff_y = 0;
	}
	static int buff_x1 = 0;
	static int buff_y1 = 0;
	static int buff_z = 0;
	static int buff_z1 = 0;

	if (GetKeyState(VK_SHIFT) < 0)
	{
		if (buff_x1 == 0)
		{
			buff_x1 = point.x;
		}
		if (buff_x1 < point.x)
		{
			pDoc->Rotation.x += (point.x - buff_x1) * 0.2;
		}
		else
		{
			pDoc->Rotation.x -= (buff_x1 - point.x) * 0.2;
		}
		buff_x1 = point.x;

		opengl.Render(pDoc);

	}
	else
	{
		buff_x1 = 0;
	}

	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (buff_y1 == 0)
		{
			buff_y1 = point.y;
		}
		if (buff_y1 < point.y)
		{
			pDoc->Rotation.y -= (point.y - buff_y1) * 0.2;
		}
		else
		{
			pDoc->Rotation.y += (buff_y1 - point.y) * 0.2;
		}
		buff_y1 = point.y;

		opengl.Render(pDoc);
	}
	else
	{
		buff_y1 = 0;
	}
	if (GetKeyState(VK_SPACE) < 0)
	{
		if (buff_z == 0)
		{
			buff_z = point.y;
		}
		else
		{
			pDoc->Rotation.z += (buff_y1 - point.y) * 0.001;
		}
		buff_z = point.y;

		opengl.Render(pDoc);
	}
	else
	{
		buff_z = 0;
	}
	if (GetKeyState(VK_LMENU) < 0)
	{
		if (buff_z1 == 0)
		{
			buff_z1 = point.y;
		}
		else
		{
			pDoc->Rotation.z += (point.y - buff_y1) * 0.001;
		}
		buff_z1 = point.y;

		opengl.Render(pDoc);
	}
		else
	{
		buff_z1 = 0;
	}
	CView::OnMouseMove(nFlags, point);
}

