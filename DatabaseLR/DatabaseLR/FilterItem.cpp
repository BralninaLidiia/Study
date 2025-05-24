#include "pch.h"
#include "FilterItem.h"
#include "DataBaseLR.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(FilterItem, CDialogEx)

FilterItem::FilterItem(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTER_ITEM, pParent)
	, atribut(_T(""))
	, value(_T(""))
{

}

FilterItem::~FilterItem()
{
}

void FilterItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, atribut);
	DDX_Text(pDX, IDC_EDIT2, value);

}


BEGIN_MESSAGE_MAP(FilterItem, CDialogEx)
	ON_BN_CLICKED(IDOK, &FilterItem::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDialogAdd2


void FilterItem::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}