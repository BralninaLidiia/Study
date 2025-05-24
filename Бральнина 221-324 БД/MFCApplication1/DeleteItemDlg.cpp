// DeleteItemDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DeleteItemDlg.h"


// Диалоговое окно CDeleteItemDlg

IMPLEMENT_DYNAMIC(CDeleteItemDlg, CDialog)

CDeleteItemDlg::CDeleteItemDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DELET_ITEM, pParent)
	, id_item(_T(""))
{

}

CDeleteItemDlg::~CDeleteItemDlg()
{
}

void CDeleteItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_item);
}


BEGIN_MESSAGE_MAP(CDeleteItemDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDeleteItemDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDeleteItemDlg


void CDeleteItemDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	CDialog::OnOK();
}
