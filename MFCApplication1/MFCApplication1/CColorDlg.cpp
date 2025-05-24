// CColorDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CColorDlg.h"
#include "MFCApplication1View.h"

// Диалоговое окно CColorDlg

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorCtrl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_Color_SinCtrl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, m_Color_ShtrihCtrl);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CColorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CColorDlg


void CColorDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	pView->m_Color = m_ColorCtrl.GetColor();
	pView->m_Color_Sin = m_Color_SinCtrl.GetColor();
	pView->m_Color_Shtrih = m_Color_ShtrihCtrl.GetColor();
	pView->Invalidate();
}
