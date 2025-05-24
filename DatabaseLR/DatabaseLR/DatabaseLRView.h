
// DatabaseLRView.h: интерфейс класса CDatabaseLRView
//

#pragma once
#include "DatabaseLRDoc.h"
#include <mysql.h>
#include "afxcview.h"


class CDatabaseLRView : public CListView
{
protected: // создать только из сериализации
	CDatabaseLRView() noexcept;
	DECLARE_DYNCREATE(CDatabaseLRView)

// Атрибуты
public:
	CDatabaseLRDoc* GetDocument() const;
	CDatabaseLRDoc* pDoc;
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	bool flag0 = 0, flag1 = 0, flag2 = 0;
// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CDatabaseLRView();
	CListCtrl Table0, Table1, Table2;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDatabaseOn();
	void show();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void change();
	void add();
	void Delet_item();
	void filter();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // версия отладки в DatabaseLRView.cpp
inline CDatabaseLRDoc* CDatabaseLRView::GetDocument() const
   { return reinterpret_cast<CDatabaseLRDoc*>(m_pDocument); }
#endif

