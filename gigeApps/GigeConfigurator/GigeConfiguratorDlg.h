
// GigeConfiguratorDlg.h: файл заголовка
//

#pragma once
#include "GigeManager.hpp"

// Диалоговое окно CGigeConfiguratorDlg
class CGigeConfiguratorDlg : public CDialogEx
{
// Создание
public:
	CGigeConfiguratorDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GIGECONFIGURATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// GigeConfiguration
private:
	enum Stage
	{
		ConfigStage,
		LibStage,
		InterfaceStage
	};

	void InitConfigurator();
	void Configurate();
	void HideAll();
	void HideLayout(const std::vector<CWnd*>& iLayout);
	void ShowLayout(const std::vector<CWnd*>& iLayout);

	GigeManager _gigeManager;

	

	Stage _stage;
	bool _useStartedConfig;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedStartConfig();
	afx_msg void OnBnClickedNoStartConfig();
	CButton _startConfigButton;
	CButton _noStartConfigButton;
	std::vector<CWnd*> _configLayout;

	afx_msg void OnBnClickedLibFile();
	CEdit _libFile;
	CButton _applyLib;
	CStatic _libMessage;
	std::vector<CWnd*> _libLayout;


	CComboBox _interfacesComboBox;
	CButton _applyInterface;
	CStatic _interfacesListMessage;
	std::vector<CWnd*> _interfaceLayout;
};
