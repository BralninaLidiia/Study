// CObjectsDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CObjectsDlg.h"


// Диалоговое окно CObjectsDlg

IMPLEMENT_DYNAMIC(CObjectsDlg, CDialog)

CObjectsDlg::CObjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_bShtrih(FALSE)
	, m_bSin(FALSE)
	, m_bKoord(FALSE)
{

}

CObjectsDlg::~CObjectsDlg()
{
}

void CObjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SHTRIH, m_bShtrih);
	DDX_Check(pDX, IDC_CHECK_SIN, m_bSin);
	DDX_Check(pDX, IDC_CHECK_KOORD, m_bKoord);
}


BEGIN_MESSAGE_MAP(CObjectsDlg, CDialog)
END_MESSAGE_MAP()


// Обработчики сообщений CObjectsDlg
