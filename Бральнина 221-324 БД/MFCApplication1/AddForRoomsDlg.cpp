// AddForRoomsDlg.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "AddForRoomsDlg.h"


// Диалоговое окно CAddForRoomsDlg

IMPLEMENT_DYNAMIC(CAddForRoomsDlg, CDialog)

CAddForRoomsDlg::CAddForRoomsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADD_FOR_ROOMS, pParent)
	, id_room(0)
	, room_status(_T(""))
{

}

CAddForRoomsDlg::~CAddForRoomsDlg()
{
}

void CAddForRoomsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, id_room);
	DDX_Text(pDX, IDC_EDIT2, room_status);
}


BEGIN_MESSAGE_MAP(CAddForRoomsDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddForRoomsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CAddForRoomsDlg


void CAddForRoomsDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	CDialog::OnOK();
}
