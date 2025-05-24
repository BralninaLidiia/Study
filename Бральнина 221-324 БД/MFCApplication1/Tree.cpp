// Tree.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Tree.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

// CTree

IMPLEMENT_DYNCREATE(CTree, CTreeView)

CTree::CTree()
{

}

CTree::~CTree()
{
}

BEGIN_MESSAGE_MAP(CTree, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CTree

#ifdef _DEBUG
void CTree::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hClients = tree.InsertItem(L"Клиенты", -1, -1, NULL, TVI_FIRST);
	m_hRooms = tree.InsertItem(L"Комнаты", -1, -1, NULL, TVI_FIRST);
	m_hBooking = tree.InsertItem(L"Бронирование", -1, -1, NULL, TVI_FIRST);

	tree.SetCheck(m_hClients, m_pDoc->m_bClient);
	tree.SetCheck(m_hRooms, m_pDoc->m_bRooms);
	tree.SetCheck(m_hBooking, m_pDoc->m_bBooking);

	tree.Expand(m_hDataBase, TVE_EXPAND);
}
void CTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CTree


int CTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;

	HTREEITEM hItem = tree.HitTest(point, &nFlags);
	if (hItem == m_hClients)
	{
		if (m_pDoc->m_bClient == false)
		{
			m_pDoc->m_bBooking = false;
			m_pDoc->m_bRooms = false;
		}
		m_pDoc->m_bClient = !m_pDoc->m_bClient;
	}
	if (hItem == m_hRooms)
	{
		if (m_pDoc->m_bRooms == false)
		{
			m_pDoc->m_bBooking = false;
			m_pDoc->m_bClient = false;
		}
		m_pDoc->m_bRooms = !m_pDoc->m_bRooms;
	}
	if (hItem == m_hBooking)
	{
		if (m_pDoc->m_bBooking == false)
		{
			m_pDoc->m_bClient = false;
			m_pDoc->m_bRooms = false;
		}
		m_pDoc->m_bBooking = !m_pDoc->m_bBooking;
	}
	
	m_pDoc->pView->OnDatabaseOn();
	m_pDoc->pView->show();

	CTreeView::OnLButtonDown(nFlags, point);
}
