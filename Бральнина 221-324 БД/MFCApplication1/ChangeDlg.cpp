// ChangeDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "ChangeDlg.h"


// Диалоговое окно CChangeDlg

IMPLEMENT_DYNAMIC(CChangeDlg, CDialog)

CChangeDlg::CChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CHANGE, pParent)
	, id_string(_T(""))
	, atribut(_T(""))
	, value(_T(""))
{

}

CChangeDlg::~CChangeDlg()
{
}

void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_string);
	DDX_Text(pDX, IDC_EDIT2, atribut);
	DDX_Text(pDX, IDC_EDIT3, value);
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CChangeDlg

void CChangeDlg::OnBnClickedOk()
{
	UpdateData();
	CDialog::OnOK();
}