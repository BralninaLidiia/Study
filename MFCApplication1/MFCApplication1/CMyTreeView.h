#pragma once
#include <afxcview.h>

// Просмотр CMyTreeView

class CMFCApplication1Doc;

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CMyTreeView();

public:
	CMFCApplication1Doc* m_pDoc;

	HTREEITEM m_hObjects, m_hCoord, m_hSin, m_hShtrih;

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


