
// MFCApplication1View.cpp: реализация класса CMFCApplication1View
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

#include "ChangeDlg.h"
#include "DeleteItemDlg.h"	
#include "FilterItemDlg.h"
#include "AddForBookingDlg.h"
#include "AddForClientDlg.h"
#include "AddForRoomsDlg.h"
#include <regex>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CListView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CListView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CMFCApplication1View

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: добавьте код создания

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}


void CMFCApplication1View::OnDatabaseOn()
{

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		// Если дескриптор не получен – выводим сообщение об ошибке
		AfxMessageBox(L"Error: can't create MySQL-descriptor");
	}
	// Подключаемся к серверу

	if (!mysql_real_connect(conn, "localhost", "Sateshy", "chrt", "hotel", NULL, NULL, 0))
	{
		// Если нет возможности установить соединение с сервером
		// базы данных выводим сообщение об ошибке
		AfxMessageBox(L"Error: can't connect to database");
	}
}

void CMFCApplication1View::show()
{
	CMFCApplication1Doc* pDoc = GetDocument();

	if (pDoc->m_bBooking)
		FillList("booking", "");

	if (pDoc->m_bRooms)
		FillList("rooms", "");

	if (pDoc->m_bClient)
		FillList("client", "");
}

void CMFCApplication1View::FillList(std::string buff, std::string buff2)
{
	listCtrl.DeleteAllItems();				//удаляем все элементы кроме заголовка
	while (listCtrl.DeleteColumn(0));		//удаляем все столбцы

	std::string r_columns = "SHOW COLUMNS FROM ";
	r_columns += buff + ";";
	mysql_query(conn, r_columns.c_str());
	res = mysql_use_result(conn);

	CString resultString;
	int columns = 0;

	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		resultString = row[0];
		listCtrl.InsertColumn(columns, resultString, LVCFMT_LEFT, -1);
		columns++;
	}

	mysql_free_result(res);
	
	std::string query;
	if (buff2.length() == 0)
	{
		query = "SELECT* FROM ";
		query += buff + ";";
	}
	else
		query = buff2;

	if (mysql_query(conn, query.c_str()))
	{
		AfxMessageBox(L"Ошибка запроса");
		return;
	}

	res = mysql_use_result(conn);
	int columns2 = 0;

	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		resultString = row[0];
		listCtrl.InsertItem(columns2, resultString);
		for (int i = 1; i < columns + 1; i++)
		{
			resultString = row[i];
			listCtrl.SetItemText(columns2, i, resultString);
		}
		columns2++;
	}

	for (int i = 0; i < columns; i++)
		listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	mysql_free_result(res);
}

void CMFCApplication1View::change()
{
	CMFCApplication1Doc* pDoc = GetDocument();
	
	CChangeDlg dlg;
	dlg.DoModal();

	CString command = L"UPDATE ";
	CString command0;
	if (pDoc->m_bBooking) 
	{
		command += "booking SET ";
		command0 = L"id_booking";
	}
	if (pDoc->m_bRooms) 
	{
		command += "rooms SET ";
		command0 = L"id_room";
	}
	if (pDoc->m_bClient) 
	{
		command += "client SET ";
		command0 = L"id_client";
	}

	command += dlg.atribut;
	command += " = '";
	command += dlg.value;
	command += "' WHERE ";
	command += command0;
	command += " = ";
	command += dlg.id_string;
	command += ";";
	if ((dlg.atribut == L"eviction_date" || dlg.atribut == L"check_in_date") && !check(dlg.value)) {
		AfxMessageBox(L"Некорректные данные");
		return;
	}
	CT2A res(command);
	mysql_query(conn, res);
	mysql_use_result(conn);
	show();
}

void CMFCApplication1View::Delet_item()
{
	CMFCApplication1Doc* pDoc = GetDocument();

	CDeleteItemDlg dlg;
	dlg.DoModal();

	CString command = L"DELETE FROM ";
	if (pDoc->m_bBooking == 1) {

		command += "booking WHERE id_booking = '";
		command += dlg.id_item;
		command += "';";
		CT2A res(command);
		mysql_query(conn, res);
		mysql_use_result(conn);
	}
	if (pDoc->m_bRooms == 1) {

		command += "rooms WHERE id_room = '";
		command += dlg.id_item;
		command += "';";
		CT2A res(command);
		mysql_query(conn, res);
		mysql_use_result(conn);
	}
	if (pDoc->m_bClient == 1) {

		command += "client WHERE id_client = '";
		command += dlg.id_item;
		command += "';";
		CT2A res(command);
		mysql_query(conn, res);
		mysql_use_result(conn);
	}
	show();
}

void CMFCApplication1View::filter()
{
	CMFCApplication1Doc* pDoc = GetDocument();
	
	CFilterItemDlg dlg;
	dlg.DoModal();

	CString command = L"SELECT * FROM ";
	if (pDoc->m_bBooking)
		command += "booking WHERE ";

	if (pDoc->m_bRooms)
		command += "rooms WHERE ";

	if (pDoc->m_bClient)
		command += "client WHERE ";

	command += dlg.atribut;
	command += " = '";
	command += dlg.value;
	command += "';";

	CT2A command_char(command);
	std::string buff(command_char);

	if (pDoc->m_bBooking)
		FillList("booking", buff);

	if (pDoc->m_bRooms)
		FillList("rooms", buff);

	if (pDoc->m_bClient)
		FillList("client", buff);
}

void CMFCApplication1View::add()
{
	CMFCApplication1Doc* pDoc = GetDocument();

	std::string command = "INSERT INTO ";
	if (pDoc->m_bBooking) 
	{
		CAddForBookingDlg dlg;
		dlg.DoModal();
		command += "booking (id_booking, id_client, check_in_date, eviction_date, cost) VALUES ('";
		command += std::to_string(dlg.id_booking);
		command += "', '";
		command += std::to_string(dlg.id_client);
		command += "', '";
		command += CT2A(dlg.check_in_date);
		command += "', '";
		command += CT2A(dlg.eviction_date);
		command += "', '";
		command += std::to_string(dlg.cost);
		command += "');";
		if (!check(dlg.check_in_date) && (!check(dlg.eviction_date))) {
			AfxMessageBox(L"Некорректные данные");
			return;
		}
		mysql_query(conn, command.c_str());
		mysql_use_result(conn);
	}
	if (pDoc->m_bClient) 
	{
		CAddForClientDlg dlg;
		dlg.DoModal();
		command += "client (id_client, firstname, lastname, patronymic) VALUES ('";
		command += std::to_string(dlg.id_client);
		command += "', '";
		command += CT2A(dlg.firstname);
		command += "', '";
		command += CT2A(dlg.lastname);
		command += "', '";
		command += CT2A(dlg.patronymic);
		command += "');";
		mysql_query(conn, command.c_str());
		mysql_use_result(conn);
	}
	if (pDoc->m_bRooms) 
	{
		CAddForRoomsDlg dlg;
		dlg.DoModal();
		command += "rooms (id_room, room_status) VALUES ('";
		command += std::to_string(dlg.id_room);
		command += "', '";
		command += CT2A(dlg.room_status);
		command += "');";
		mysql_query(conn, command.c_str());
		mysql_use_result(conn);
	}
	show();
}

bool CMFCApplication1View::check(CString buff)
{
	std::regex dateTimeRegex("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}");
	std::string f = CW2A(buff);
	if (!std::regex_match(f, dateTimeRegex))
	{
		return false;
	}
	return true;
}

void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: добавьте здесь код отрисовки для собственных данных
}



void CMFCApplication1View::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	// TODO: ListView можно заполнить элементами посредством непосредственного обращения
	//  к элементам управления этого списка через вызов GetListCtr().
	
}


// Печать CMFCApplication1View

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CMFCApplication1View

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CListView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMFCApplication1View



void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CMFCApplication1Doc* pDoc = GetDocument();

	if (pDoc->m_bClient || pDoc->m_bRooms || pDoc->m_bBooking) 
	{
		CCmdUI state;
		CMenu SubMenu;
		ClientToScreen(&point);
		SubMenu.CreatePopupMenu();
		SubMenu.AppendMenu(MF_STRING, 1, _T("Добавить данные"));
		SubMenu.AppendMenu(MF_STRING, 2, _T("Изменить данные"));
		SubMenu.AppendMenu(MF_STRING, 3, _T("Удалить данные"));
		SubMenu.AppendMenu(MF_STRING, 4, _T("Фильтровать"));
		SubMenu.AppendMenu(MF_STRING, 5, _T("Отменить фильтрацию"));
		UINT nCmdID = SubMenu.TrackPopupMenu(TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, this);

		if (nCmdID == 1) { // Обработка для Добавить данные
			add();
		}
		else if (nCmdID == 2) { // Обработка для Добавить данные
			change();
		}
		else if (nCmdID == 3) { // Обработка для Удалить данные
			Delet_item();
		}
		else if (nCmdID == 4) {// Обработка фильтровать
			filter();
		}
		else if (nCmdID == 5) {// Обработка фильтровать
			show();
		}
	}
	CListView::OnRButtonDown(nFlags, point);
}
