#pragma once
#include <afxcview.h>

// Просмотр MyTree
class CDatabaseLRDoc;
class MyTree : public CTreeView
{
	DECLARE_DYNCREATE(MyTree)

protected:
	MyTree();           // защищенный конструктор, используемый при динамическом создании
	virtual ~MyTree();

public:
	CDatabaseLRDoc* m_pDoc;
	HTREEITEM m_hDataBase, m_hClients, m_hRooms, m_hBooking;
	void FillTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


