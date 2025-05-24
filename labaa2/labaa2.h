
// labaa2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Clabaa2App:
// Сведения о реализации этого класса: labaa2.cpp
//

class Clabaa2App : public CWinApp
{
public:
	Clabaa2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Clabaa2App theApp;
