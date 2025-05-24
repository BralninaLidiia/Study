#pragma once
#include <afxcview.h>

// Просмотр CTree
class CMFCApplication1Doc;
class CTree : public CTreeView
{
	DECLARE_DYNCREATE(CTree)

protected:
	CTree();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CTree();

public:
	CMFCApplication1Doc* m_pDoc;
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


