
// ChildView.h: интерфейс класса CChildView
//


#pragma once

#include "GigeHelper.hpp"

// Окно CChildView

class CChildView : public CWnd
{
// Создание
public:
	CChildView();

// Атрибуты
public:
	enum ImageType {
		Mono,
		RGB
	};

	ImageType _imType;

	LONG _width;
	LONG _height;
	LONG _payloadSize;

	LONG _bitsPerPixel;

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
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

