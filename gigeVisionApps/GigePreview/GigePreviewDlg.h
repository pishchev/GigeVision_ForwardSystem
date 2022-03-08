
// GigePreviewDlg.h: файл заголовка
//

#pragma once

#include <iostream>
#include <iomanip>
#include <objbase.h>
#include <comdef.h>
#include <string>

#include "../GigeVisionDLL/GigeVisionDLL_i.h"
#include "../GigeVisionDLL/GigeVisionDLL_i.c"

// Диалоговое окно CGigePreviewDlg
class CGigePreviewDlg : public CDialogEx
{
// Создание
public:
	CGigePreviewDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GIGEPREVIEW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	enum Stage { ConfigChoosing, Play };

	void Init();
	void InitGigeDLL();
	void InitDialogComponents();
	void HideDialogComponents();
	void ShowImage();
	
	

	IGigeVision* _gige;
	size_t _payloadSize;
	size_t _width;
	size_t _height;
	size_t _bitsPerPixel;
	unsigned char* _buffer;
	unsigned char* _image;
	bool _started;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit _configMessage;
	CEdit _configFile;
	CButton _configApply;
	afx_msg void OnBnClickedApplyConfig();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton _exitButton;
};
