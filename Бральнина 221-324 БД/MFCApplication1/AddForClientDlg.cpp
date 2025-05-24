// AddForClientDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "AddForClientDlg.h"


// Диалоговое окно CAddForClientDlg

IMPLEMENT_DYNAMIC(CAddForClientDlg, CDialog)

CAddForClientDlg::CAddForClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADD_FOR_CLIENT, pParent)
	, id_client(0)
	, firstname(_T(""))
	, lastname(_T(""))
	, patronymic(_T(""))
{

}

CAddForClientDlg::~CAddForClientDlg()
{
}

void CAddForClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_client);
	DDX_Text(pDX, IDC_EDIT2, firstname);
	DDX_Text(pDX, IDC_EDIT3, lastname);
	DDX_Text(pDX, IDC_EDIT4, patronymic);
}


BEGIN_MESSAGE_MAP(CAddForClientDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddForClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CAddForClientDlg


void CAddForClientDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	CDialog::OnOK();
}
