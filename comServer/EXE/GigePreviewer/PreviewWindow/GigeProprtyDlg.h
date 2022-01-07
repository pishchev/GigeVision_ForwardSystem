﻿#pragma once


// Диалоговое окно CGigeProprtyDlg

class CGigeProprtyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGigeProprtyDlg)

public:
	CGigeProprtyDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CGigeProprtyDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CGigeProprtyDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
private:
	CComboBox m_InterfaceList;
};