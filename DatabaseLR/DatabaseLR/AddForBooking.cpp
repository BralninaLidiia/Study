#include "pch.h"
#include "AddForBooking.h"
#include "DataBaseLR.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(AddForBooking, CDialogEx)

AddForBooking::AddForBooking(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_FOR_BOOKING, pParent)
	, id_booking(_T(""))
	, id_client(_T(""))
	, check_in_date(_T(""))
	, eviction_date(_T(""))
	, cost(_T(""))
{

}

AddForBooking::~AddForBooking()
{
}

void AddForBooking::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_booking);
	DDX_Text(pDX, IDC_EDIT2, id_client);
	DDX_Text(pDX, IDC_EDIT3, check_in_date);
	DDX_Text(pDX, IDC_EDIT4, eviction_date);
	DDX_Text(pDX, IDC_EDIT5, cost);
}


BEGIN_MESSAGE_MAP(AddForBooking, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddForBooking::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDialogAdd2


void AddForBooking::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}