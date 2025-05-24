// MyTree.cpp: файл реализации
//

#include "pch.h"
#include "DatabaseLR.h"
#include "MyTree.h"

#include "DatabaseLRDoc.h"
#include "DatabaseLRView.h"

// MyTree
IMPLEMENT_DYNCREATE(MyTree, CTreeView)

MyTree::MyTree()
{

}

MyTree::~MyTree()
{
}

BEGIN_MESSAGE_MAP(MyTree, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика MyTree

#ifdef _DEBUG
void MyTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void MyTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений MyTree


int MyTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS /*| TVS_CHECKBOXES*/;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}
void MyTree::FillTree()
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


void MyTree::OnLButtonDown(UINT nFlags, CPoint point)
{
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

	m_pDoc->pView->Invalidate();
	m_pDoc->pView->OnDatabaseOn();
	m_pDoc->pView->show();

	CTreeView::OnLButtonDown(nFlags, point);
}
