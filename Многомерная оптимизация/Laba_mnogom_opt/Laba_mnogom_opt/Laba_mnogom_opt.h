
// Laba_mnogom_opt.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLabamnogomoptApp:
// Сведения о реализации этого класса: Laba_mnogom_opt.cpp
//

class CLabamnogomoptApp : public CWinApp
{
public:
	CLabamnogomoptApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLabamnogomoptApp theApp;
