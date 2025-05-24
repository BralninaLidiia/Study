#include "pch.h"
#include "AddForRooms.h"
#include "DataBaseLR.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(AddForRooms, CDialogEx)

AddForRooms::AddForRooms(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_FOR_ROOMS, pParent)
	, id_room(_T(""))
	, room_status(_T(""))
{

}

AddForRooms::~AddForRooms()
{
}

void AddForRooms::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_room);
	DDX_Text(pDX, IDC_EDIT2, room_status);

}


BEGIN_MESSAGE_MAP(AddForRooms, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddForRooms::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDialogAdd2


void AddForRooms::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
