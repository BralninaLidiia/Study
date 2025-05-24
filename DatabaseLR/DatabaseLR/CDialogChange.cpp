
#include "pch.h"
#include "DatabaseLR.h"
#include "afxdialogex.h"
#include "CDialogChange.h"


// Диалоговое окно CDialogChange

IMPLEMENT_DYNAMIC(CDialogChange, CDialogEx)

CDialogChange::CDialogChange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGE, pParent)
	, id_string(_T(""))
	, atribut(_T(""))
	, value(_T(""))
{

}

CDialogChange::~CDialogChange()
{
}

void CDialogChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_string);
	DDX_Text(pDX, IDC_EDIT2, atribut);
	DDX_Text(pDX, IDC_EDIT3, value);
}


BEGIN_MESSAGE_MAP(CDialogChange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogChange::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDialogChange


void CDialogChange::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}