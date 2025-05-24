#include "pch.h"
#include "AddForClient.h"
#include "DataBaseLR.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(AddForClient, CDialogEx)

AddForClient::AddForClient(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_FOR_CLIENT, pParent)
	, id_client(_T(""))
	, firstname(_T(""))
	, lastname(_T(""))
	, patronymic(_T(""))
{

}

AddForClient::~AddForClient()
{
}

void AddForClient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_client);
	DDX_Text(pDX, IDC_EDIT2, firstname);
	DDX_Text(pDX, IDC_EDIT3, lastname);
	DDX_Text(pDX, IDC_EDIT4, patronymic);
}


BEGIN_MESSAGE_MAP(AddForClient, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddForClient::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDialogAdd2


void AddForClient::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
