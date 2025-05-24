
// MFCApplication1Doc.h: интерфейс класса CMFCApplication1Doc 
//


#pragma once
class CMyTreeView;
class CMFCApplication1View;

class CMFCApplication1Doc : public CDocument
{
protected: // создать только из сериализации
	CMFCApplication1Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1Doc)

// Атрибуты
public:
	double A =2000.f, B = 1.f;
	double X1 = 0.f;
	bool m_bCoord=FALSE, m_bSin =FALSE, m_bShtrih=FALSE;

	CMFCApplication1View* pView;
	CMyTreeView* pTree;

	

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
//	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnObjectsShtrih();
	afx_msg void OnObjectsSin();
	afx_msg void OnObjectsKoord();
	afx_msg void OnUpdateObjectsShtrih(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectsSin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectsKoord(CCmdUI* pCmdUI);
	afx_msg void OnObjectsDlg();
};
