
// DatabaseLRDoc.h: интерфейс класса CDatabaseLRDoc 
//


#pragma once
class CDatabaseLRView;
class MyTree;

class CDatabaseLRDoc : public CDocument
{
protected: // создать только из сериализации
	CDatabaseLRDoc() noexcept;
	DECLARE_DYNCREATE(CDatabaseLRDoc)

// Атрибуты
public:
	CDatabaseLRView* pView;
	MyTree* pTree;
	bool m_bClient = FALSE, m_bRooms = FALSE, m_bBooking = FALSE;

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CDatabaseLRDoc();
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
};
