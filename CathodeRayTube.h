
// CathodeRayTube.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCathodeRayTubeApp:
// Сведения о реализации этого класса: CathodeRayTube.cpp
//

class CCathodeRayTubeApp : public CWinApp
{
public:
	CCathodeRayTubeApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCathodeRayTubeApp theApp;
