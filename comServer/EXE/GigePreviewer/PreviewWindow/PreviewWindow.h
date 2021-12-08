
// PreviewWindow.h: основной файл заголовка для приложения PreviewWindow
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CPreviewWindowApp:
// Сведения о реализации этого класса: PreviewWindow.cpp
//

class CPreviewWindowApp : public CWinApp
{
public:
	CPreviewWindowApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPreviewWindowApp theApp;
