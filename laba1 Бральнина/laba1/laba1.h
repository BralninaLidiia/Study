
// laba1.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Claba1App:
// Сведения о реализации этого класса: laba1.cpp
//

class Claba1App : public CWinApp
{
public:
	Claba1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Claba1App theApp;
