
// MFCApplication1View.h: интерфейс класса CMFCApplication1View
//

#pragma once
#include "MFCApplication1Doc.h"
#include <mysql.h>
#include "string"
class CMFCApplication1View : public CListView
{
protected: // создать только из сериализации
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// Атрибуты
public:
	CMFCApplication1Doc* GetDocument() const;

// Операции
public:
	CListCtrl& listCtrl = GetListCtrl();
	
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	void OnDatabaseOn();
	void show();
	void FillList(std::string buff, std::string buff2);
	
	void change();
	void Delet_item();
	void filter();
	void add();
	bool check(CString buff);
	
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в MFCApplication1View.cpp
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

