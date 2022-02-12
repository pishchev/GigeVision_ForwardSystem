
// GigeConfiguratorDlg.h: файл заголовка
//

#pragma once
#include "GigeManager.hpp"

namespace Convert
{
	static std::string CStringToString(const CString& iCStr);
	static LPCTSTR StringToLPCTSTR(const std::string& iStr);
	static std::string IntToString(const int& iInt);
}

class Property
{
public:
	enum Type { Undefined, Int, Str, Enum };
	enum Visibility { Begginer, Expert, Guru, Invisible };
	enum AccessMode { RW, RO, WO, NA, NI };

	std::string _name;
	std::string _strValue;

	Type _type;
	Visibility _visibility;
	AccessMode _accessMode;

	bool _isChanged = false;
	bool _canBeChanged = true;
};

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
		InterfaceStage,
		DeviceStage,
		StreamStage,
		PropertiesStage
	};

	void InitConfigurator();
	void ShowConfigStage();
	void HideAll();
	void HideLayout(const std::vector<CWnd*>& iLayout);
	void ShowLayout(const std::vector<CWnd*>& iLayout);
	void FillProperties(size_t iStartIndex);
	void UpdateProperties();
	void GetProperties();

	GigeManager _gigeManager;

	std::vector<Property> _properties;
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

	afx_msg void OnBnClickedInterfaceApply();
	CComboBox _interfacesComboBox;
	CButton _applyInterface;
	CStatic _interfacesListMessage;
	std::vector<CWnd*> _interfaceLayout;

	afx_msg void OnBnClickedDeviceApply();
	CStatic _devicesMessage;
	CComboBox _devicesComboBox;
	CButton _applyDevice;
	std::vector<CWnd*> _deviceLayout;

	afx_msg void OnBnClickedStreamApply();
	CComboBox _streamsComboBox;
	CButton _applyStream;
	CStatic _streamsMessage;
	std::vector<CWnd*> _streamLayout;

	CEdit _propertyEdits[16];
	CEdit _valueEdits[16];
	CScrollBar _propertyScroll;
	std::vector<CWnd*> _propertyLayout;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
