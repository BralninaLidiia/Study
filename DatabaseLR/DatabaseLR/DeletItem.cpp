#include "pch.h"
#include "DeletItem.h"
#include "DataBaseLR.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DeletItem, CDialogEx)

DeletItem::DeletItem(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELET_ITEM, pParent)
	, id_item(_T(""))
{

}

DeletItem::~DeletItem()
{
}

void DeletItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_item);
}


BEGIN_MESSAGE_MAP(DeletItem, CDialogEx)
	ON_BN_CLICKED(IDOK, &DeletItem::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CDialogAdd2


void DeletItem::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
