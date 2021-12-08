
// ChildView.h: интерфейс класса CChildView
//


#pragma once

#include "../GigePreviewerDLL/GigePreviewerDLL_i.c"
#include "../GigePreviewerDLL/GigePreviewerDLL_i.h"
#include <objbase.h>
#include <string>

// Окно CChildView

class CChildView : public CWnd
{
// Создание
public:
	CChildView();

// Атрибуты
public:
	size_t _r;
	LONG _payloadSize;
	BYTE* _image;
	IPreviewer* _prev;
// Операции
public:

// Переопределение
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildView();

	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

