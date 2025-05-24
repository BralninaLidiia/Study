
// DatabaseLR.h: основной файл заголовка для приложения DatabaseLR
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CDatabaseLRApp:
// Сведения о реализации этого класса: DatabaseLR.cpp
//

class CDatabaseLRApp : public CWinApp
{
public:
	CDatabaseLRApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDatabaseLRApp theApp;
