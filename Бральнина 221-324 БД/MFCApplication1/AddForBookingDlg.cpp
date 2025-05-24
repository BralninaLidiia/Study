// AddForBookingDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "AddForBookingDlg.h"


// Диалоговое окно CAddForBookingDlg

IMPLEMENT_DYNAMIC(CAddForBookingDlg, CDialog)

CAddForBookingDlg::CAddForBookingDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADD_FOR_BOOKING, pParent)
	, id_booking(0)
	, id_client(0)
	, check_in_date(_T(""))
	, eviction_date(_T(""))
	, cost(0)
{

}

CAddForBookingDlg::~CAddForBookingDlg()
{
}

void CAddForBookingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_booking);
	DDX_Text(pDX, IDC_EDIT2, id_client);
	DDX_Text(pDX, IDC_EDIT3, check_in_date);
	DDX_Text(pDX, IDC_EDIT4, eviction_date);
	DDX_Text(pDX, IDC_EDIT5, cost);
}


BEGIN_MESSAGE_MAP(CAddForBookingDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddForBookingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CAddForBookingDlg


void CAddForBookingDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	CDialog::OnOK();
}
