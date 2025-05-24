
// DatabaseLRView.cpp: реализация класса CDatabaseLRView
//

#include "pch.h"
#include "framework.h"
#include <mysql.h>
#include <cstring> //?
#include <vector>
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "DatabaseLR.h"
#endif

#include "DatabaseLRDoc.h"
#include "DatabaseLRView.h"
#include "CDialogChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "AddForBooking.h"
#include "AddForClient.h"
#include "AddForRooms.h"
#include "DeletItem.h"
#include "FilterItem.h"
using namespace std;


// CDatabaseLRView

IMPLEMENT_DYNCREATE(CDatabaseLRView, CListView)

BEGIN_MESSAGE_MAP(CDatabaseLRView, CListView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_COMMAND(ID_DATABASE_ON, &CDatabaseLRView::OnDatabaseOn)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Создание или уничтожение CDatabaseLRView

CDatabaseLRView::CDatabaseLRView() noexcept
{
	// TODO: добавьте код создания

}

CDatabaseLRView::~CDatabaseLRView()
{
}

BOOL CDatabaseLRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CDatabaseLRView

void CDatabaseLRView::OnDraw(CDC* /*pDC*/)
{
	CDatabaseLRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CDatabaseLRView

BOOL CDatabaseLRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CDatabaseLRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CDatabaseLRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CDatabaseLRView

#ifdef _DEBUG
void CDatabaseLRView::AssertValid() const
{
	CView::AssertValid();
}

void CDatabaseLRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDatabaseLRDoc* CDatabaseLRView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDatabaseLRDoc)));
	return (CDatabaseLRDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CDatabaseLRView



void CDatabaseLRView::OnDatabaseOn()
{
	pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

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


void CDatabaseLRView::show()
{
	CListCtrl& list = GetListCtrl();
	CString resultString;
	vector <CString> bufer;
	for (int i = -1; i < 100; i++)
	{
		list.DeleteColumn(0);
	}
	if (pDoc->m_bBooking == 1) {

		int columns = -1;
		int rows = -1;

		Table0.DestroyWindow();
		const char* r_columns = "SHOW COLUMNS FROM booking;";
		mysql_query(conn, r_columns);
		res = mysql_use_result(conn);

		CRect rectListCtrl(0, 0, 1000, 1000); // Задаем координаты и размер List Control

		Table0.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectListCtrl, this, 0);

		while ((row = mysql_fetch_row(res)) != nullptr) {
			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			columns++;
			Table0.InsertColumn(columns, resultString, LVCFMT_LEFT, 150);
		}
		mysql_free_result(res);
		bufer.clear();


		const char* query = "SELECT* FROM booking;";//возвращает 0 при успешном запросе
		if (mysql_query(conn, query)) {
			AfxMessageBox(L"Ошибка запроса");
		}
		res = mysql_use_result(conn);
		int j = 0;
		while ((row = mysql_fetch_row(res)) != nullptr) {

			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			rows++;
			Table0.InsertItem(j, resultString); // Добавление элементов в List Control
			for (int i = 1; i < columns + 1; i++)
			{
				resultString = row[i];
				Table0.SetItemText(j, i, resultString);//номер строки номер столбца
			}
			j++;

		}
		mysql_free_result(res);
		bufer.clear();
		flag0 = 1;
		flag1 = flag2 = 0;

	}
	else {
		if (flag0 == 1) {
			Table0.DestroyWindow();
			flag0 = 0;
		}
	}
	if (pDoc->m_bClient == 1) {

		int columns = -1;
		int rows = -1;

		const char* r_columns = "SHOW COLUMNS FROM client;";
		mysql_query(conn, r_columns);
		res = mysql_use_result(conn);

		CRect rectListCtrl(0, 0, 1000, 1000); // Задаем координаты и размер List Control
		Table1.DestroyWindow();
		Table1.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectListCtrl, this, 0);

		while ((row = mysql_fetch_row(res)) != nullptr) {
			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			columns++;
			Table1.InsertColumn(columns, resultString, LVCFMT_LEFT, 100);
		}
		mysql_free_result(res);
		bufer.clear();


		const char* query = "SELECT* FROM client;";//возвращает 0 при успешном запросе
		if (mysql_query(conn, query)) {
			AfxMessageBox(L"Ошибка запроса");
		}
		res = mysql_use_result(conn);
		int j = 0;
		while ((row = mysql_fetch_row(res)) != nullptr) {

			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			rows++;
			Table1.InsertItem(j, resultString); // Добавление элементов в List Control
			for (int i = 1; i < columns + 1; i++)
			{
				resultString = row[i];
				Table1.SetItemText(j, i, resultString);//номер строки номер столбца
			}
			j++;

		}
		mysql_free_result(res);
		bufer.clear();
		flag1 = 1;
		flag0 = flag2 = 0;

	}
	else {
		if (flag1 == 1) {
			Table1.DeleteAllItems();
			Table1.DestroyWindow();
			flag1 = 0;
		}
	}
	if (pDoc->m_bRooms == 1) {

		int columns = -1;
		int rows = -1;

		const char* r_columns = "SHOW COLUMNS FROM rooms;";
		mysql_query(conn, r_columns);
		res = mysql_use_result(conn);

		CRect rectListCtrl(0, 0, 1000, 1000); // Задаем координаты и размер List Control
		Table2.DestroyWindow();
		Table2.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectListCtrl, this, 0);

		while ((row = mysql_fetch_row(res)) != nullptr) {
			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			columns++;
			Table2.InsertColumn(columns, resultString, LVCFMT_LEFT, 100);
		}
		mysql_free_result(res);
		bufer.clear();


		const char* query = "SELECT* FROM rooms;";//возвращает 0 при успешном запросе
		if (mysql_query(conn, query)) {
			AfxMessageBox(L"Ошибка запроса");
		}
		res = mysql_use_result(conn);
		int j = 0;
		while ((row = mysql_fetch_row(res)) != nullptr) {

			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			rows++;
			Table2.InsertItem(j, resultString); // Добавление элементов в List Control
			for (int i = 1; i < columns + 1; i++)
			{
				resultString = row[i];
				Table2.SetItemText(j, i, resultString);//номер строки номер столбца
			}
			j++;

		}
		mysql_free_result(res);
		bufer.clear();
		flag2 = 1;
		flag1 = flag0 = 0;

	}
	else {
		if (flag2 == 1) {
			Table2.DeleteAllItems();
			Table2.DestroyWindow();
			flag2 = 0;
		}
	}
}



void CDatabaseLRView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if ((pDoc->m_bClient == 1) || (pDoc->m_bRooms == 1) || (pDoc->m_bBooking == 1)) {
		CCmdUI state;


		CMenu SubMenu, MainMenu;

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
}


void CDatabaseLRView::change()
{
	CDialogChange dlg;
	dlg.DoModal();

	CString command = L"UPDATE ";
	CString command0;
	if (pDoc->m_bBooking == 1) {

		command += "booking SET ";
		command0 = L"id_booking";
	}
	if (pDoc->m_bRooms == 1) {
		command += "rooms SET ";
		command0 = L"id_room";

	}
	if (pDoc->m_bClient == 1) {
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

	CT2A res(command);
	mysql_query(conn, res);
	mysql_use_result(conn);
	show();
}



void CDatabaseLRView::add()
{
	CString command = L"INSERT INTO ";
	if (pDoc->m_bBooking == 1) {
		AddForBooking dlg;
		dlg.DoModal();
		command += "booking (id_booking, id_client, check_in_date, eviction_date, cost) VALUES ('";
		command += dlg.id_booking;
		command += L"', '";
		command += dlg.id_client;
		command += L"', '";
		command += dlg.check_in_date;
		command += L"', '";
		command += dlg.eviction_date;
		command += L"', '";
		command += dlg.cost;
		command += "');";
		CT2A res(command);
		mysql_query(conn, res);
		mysql_use_result(conn);
	}
	if (pDoc->m_bClient == 1) {
		AddForClient dlg;
		dlg.DoModal();
		command += "client (id_client, firstname, lastname, patronymic) VALUES ('";
		command += dlg.id_client;
		command += L"', '";
		command += dlg.firstname;
		command += L"', '";
		command += dlg.lastname;
		command += L"', '";
		command += dlg.patronymic;
		command += "');";
		CT2A res(command);
		mysql_query(conn, res);
		mysql_use_result(conn);
	}
	if (pDoc->m_bRooms == 1) {

		AddForRooms dlg;
		dlg.DoModal();
		command += "rooms (id_room, room_status) VALUES ('";
		command += dlg.id_room;
		command += L"', '";
		command += dlg.room_status;
		command += "');";
		CT2A res(command);
		mysql_query(conn, res);
		mysql_use_result(conn);
	}
	show();
}


void CDatabaseLRView::Delet_item()
{
	DeletItem dlg;
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



void CDatabaseLRView::filter()
{
	FilterItem dlg;
	dlg.DoModal();
	CString resultString;
	vector <CString> bufer;

	CString command = L"SELECT * FROM ";
	if (pDoc->m_bBooking == 1) {

		command += "booking WHERE ";
	}
	if (pDoc->m_bRooms == 1) {
		command += "rooms WHERE ";

	}
	if (pDoc->m_bClient == 1) {
		command += "client WHERE ";
	}
	command += dlg.atribut;
	command += " = '";
	command += dlg.value;
	command += "';";

	CT2A command_char(command);

	if (pDoc->m_bBooking == 1) {

		int columns = -1;
		int rows = -1;

		Table0.DestroyWindow();
		const char* r_columns = "SHOW COLUMNS FROM booking;";
		mysql_query(conn, r_columns);
		res = mysql_use_result(conn);

		CRect rectListCtrl(0, 0, 1000, 1000); // Задаем координаты и размер List Control

		Table0.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectListCtrl, this, 0);

		while ((row = mysql_fetch_row(res)) != nullptr) {
			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			columns++;
			Table0.InsertColumn(columns, resultString, LVCFMT_LEFT, 150);
		}
		mysql_free_result(res);
		bufer.clear();

		const char* query = command_char;//возвращает 0 при успешном запросе
		if (mysql_query(conn, query)) {
			AfxMessageBox(L"Ошибка");
		}

		res = mysql_use_result(conn);
		int j = 0;
		while ((row = mysql_fetch_row(res)) != nullptr) {

			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			rows++;
			Table0.InsertItem(j, resultString); // Добавление элементов в List Control
			for (int i = 1; i < columns + 1; i++)
			{
				resultString = row[i];
				Table0.SetItemText(j, i, resultString);//номер строки номер столбца
			}
			j++;

		}
		mysql_free_result(res);
		bufer.clear();
		flag0 = 1;
		flag1 = flag2 = 0;

	}
	else {
		if (flag0 == 1) {
			Table0.DestroyWindow();
			flag0 = 0;
		}
	}
	if (pDoc->m_bRooms == 1) {

		int columns = -1;
		int rows = -1;

		const char* r_columns = "SHOW COLUMNS FROM rooms;";
		mysql_query(conn, r_columns);
		res = mysql_use_result(conn);

		CRect rectListCtrl(0, 0, 1500, 1000); // Задаем координаты и размер List Control
		Table1.DestroyWindow();
		Table1.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectListCtrl, this, 0);

		while ((row = mysql_fetch_row(res)) != nullptr) {
			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			columns++;
			Table1.InsertColumn(columns, resultString, LVCFMT_LEFT, 100);
		}
		mysql_free_result(res);
		bufer.clear();


		const char* query = command_char;//возвращает 0 при успешном запросе
		if (mysql_query(conn, query)) {
			AfxMessageBox(L"Ошибка");
		}
		res = mysql_use_result(conn);
		int j = 0;
		while ((row = mysql_fetch_row(res)) != nullptr) {

			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			rows++;
			Table1.InsertItem(j, resultString); // Добавление элементов в List Control
			for (int i = 1; i < columns + 1; i++)
			{
				resultString = row[i];
				Table1.SetItemText(j, i, resultString);//номер строки номер столбца
			}
			j++;

		}
		mysql_free_result(res);
		bufer.clear();
		flag1 = 1;
		flag0 = flag2 = 0;

	}
	else {
		if (flag1 == 1) {
			Table1.DeleteAllItems();
			Table1.DestroyWindow();
			flag1 = 0;
		}
	}
	if (pDoc->m_bClient == 1) {

		int columns = -1;
		int rows = -1;

		const char* r_columns = "SHOW COLUMNS FROM client;";
		mysql_query(conn, r_columns);
		res = mysql_use_result(conn);

		CRect rectListCtrl(0, 0, 1000, 1000); // Задаем координаты и размер List Control
		Table2.DestroyWindow();
		Table2.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT, rectListCtrl, this, 0);

		while ((row = mysql_fetch_row(res)) != nullptr) {
			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			columns++;
			Table2.InsertColumn(columns, resultString, LVCFMT_LEFT, 100);
		}
		mysql_free_result(res);
		bufer.clear();


		const char* query = command_char;//возвращает 0 при успешном запросе
		if (mysql_query(conn, query)) {
			AfxMessageBox(L"Ошибка");
		}
		res = mysql_use_result(conn);
		int j = 0;
		while ((row = mysql_fetch_row(res)) != nullptr) {

			resultString = row[0]; // Первый столбец извлеченной строки
			bufer.push_back(resultString);
			rows++;
			Table2.InsertItem(j, resultString); // Добавление элементов в List Control
			for (int i = 1; i < columns + 1; i++)
			{
				resultString = row[i];
				Table2.SetItemText(j, i, resultString);//номер строки номер столбца
			}
			j++;

		}
		mysql_free_result(res);
		bufer.clear();
		flag2 = 1;
		flag1 = flag0 = 0;

	}
	else {
		if (flag2 == 1) {
			Table2.DeleteAllItems();
			Table2.DestroyWindow();
			flag2 = 0;
		}
	}
}


int CDatabaseLRView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style = WS_VISIBLE | WS_CHILD | LVS_REPORT;
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}
