// FilterItemDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "FilterItemDlg.h"


// Диалоговое окно CFilterItemDlg

IMPLEMENT_DYNAMIC(CFilterItemDlg, CDialog)

CFilterItemDlg::CFilterItemDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FILTER_ITEM, pParent)
	, atribut(_T(""))
	, value(_T(""))
{

}

CFilterItemDlg::~CFilterItemDlg()
{
}

void CFilterItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, atribut);
	DDX_Text(pDX, IDC_EDIT2, value);
}


BEGIN_MESSAGE_MAP(CFilterItemDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CFilterItemDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CFilterItemDlg


void CFilterItemDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	CDialog::OnOK();
}
