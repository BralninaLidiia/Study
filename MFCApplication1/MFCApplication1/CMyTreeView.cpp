// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CMyTreeView.h"

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();
	m_hObjects = tree.InsertItem(L"Объекты", -1, -1, NULL, TVI_FIRST);

	m_hCoord = tree.InsertItem(L"Ось координат", -1, -1, m_hObjects, TVI_FIRST);
	m_hSin = tree.InsertItem(L"Синусоида", -1, -1, m_hObjects, TVI_FIRST);
	m_hShtrih = tree.InsertItem(L"Штриховка", -1, -1, m_hObjects, TVI_FIRST);

	tree.SetCheck(m_hCoord, m_pDoc->m_bCoord);
	tree.SetCheck(m_hSin, m_pDoc->m_bSin);
	tree.SetCheck(m_hShtrih, m_pDoc->m_bShtrih);

	tree.Expand(m_hObjects, TVE_EXPAND);



}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;
	
	CTreeView::OnLButtonDown(nFlags, point);

	tree.GetItemRect(m_hObjects, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hObjects);
	}

	tree.GetItemRect(m_hCoord, &rc, false);
	if (rc.PtInRect(point))
		{
		tree.SelectItem(m_hCoord);

	}

	tree.GetItemRect(m_hShtrih, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hShtrih);
	}
	
	tree.GetItemRect(m_hSin, &rc, false);
	if (rc.PtInRect(point))
	{
		tree.SelectItem(m_hSin);
	}
	

	if (tree.GetSelectedItem() == m_hObjects)
	{
		bool check = tree.GetCheck(m_hObjects);
		tree.SetCheck(m_hCoord, check);
		tree.SetCheck(m_hSin, check);
		tree.SetCheck(m_hShtrih, check);
	}

	else
	{
		tree.SetCheck(m_hObjects, false);
	}

	m_pDoc->m_bCoord = tree.GetCheck(m_hCoord);
	m_pDoc->m_bShtrih = tree.GetCheck(m_hShtrih);
	m_pDoc->m_bSin = tree.GetCheck(m_hSin);
	m_pDoc->pView->Invalidate();
	
}
