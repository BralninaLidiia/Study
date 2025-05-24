
// MFCApplication1Doc.cpp: реализация класса CMFCApplication1Doc 
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
#include "CObjectsDlg.h"


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "CMyTreeView.h"
// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
	ON_COMMAND(ID_OBJECTS_SHTRIH, &CMFCApplication1Doc::OnObjectsShtrih)
	ON_COMMAND(ID_OBJECTS_SIN, &CMFCApplication1Doc::OnObjectsSin)
	ON_COMMAND(ID_OBJECTS_KOORD, &CMFCApplication1Doc::OnObjectsKoord)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_SHTRIH, &CMFCApplication1Doc::OnUpdateObjectsShtrih)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_SIN, &CMFCApplication1Doc::OnUpdateObjectsSin)
	ON_UPDATE_COMMAND_UI(ID_OBJECTS_KOORD, &CMFCApplication1Doc::OnUpdateObjectsKoord)
	ON_COMMAND(ID_OBJECTS_DLG, &CMFCApplication1Doc::OnObjectsDlg)
END_MESSAGE_MAP()


// Создание или уничтожение CMFCApplication1Doc

CMFCApplication1Doc::CMFCApplication1Doc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;



	pTree->FillTree();
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CMFCApplication1Doc

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CMFCApplication1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CMFCApplication1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CMFCApplication1Doc

#ifdef _DEBUG
void CMFCApplication1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CMFCApplication1Doc


void CMFCApplication1Doc::OnObjectsShtrih()
{
	// TODO: добавьте свой код обработчика команд
	m_bShtrih = !m_bShtrih;
	pView->Invalidate();
	pTree->FillTree();
}


void CMFCApplication1Doc::OnObjectsSin()
{
	// TODO: добавьте свой код обработчика команд
	m_bSin = !m_bSin;
	pView->Invalidate();
	pTree->FillTree();
}


void CMFCApplication1Doc::OnObjectsKoord()
{
	// TODO: добавьте свой код обработчика команд
	m_bCoord = !m_bCoord;
	pView->Invalidate();
	pTree->FillTree();

}


void CMFCApplication1Doc::OnUpdateObjectsShtrih(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bShtrih);
	pView->Invalidate();


}


void CMFCApplication1Doc::OnUpdateObjectsSin(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bSin);
}


void CMFCApplication1Doc::OnUpdateObjectsKoord(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bCoord);
}


void CMFCApplication1Doc::OnObjectsDlg()
{
	// TODO: добавьте свой код обработчика команд
	CObjectsDlg dlg;

	dlg.m_bShtrih = m_bShtrih;
	dlg.m_bSin=m_bSin;
	dlg.m_bKoord = m_bCoord;

	if (dlg.DoModal() == IDOK)
	{
		m_bShtrih=dlg.m_bShtrih;
		m_bSin=dlg.m_bSin;
		m_bCoord=dlg.m_bKoord;

		pView->Invalidate();
		pTree->FillTree();
	}

}
