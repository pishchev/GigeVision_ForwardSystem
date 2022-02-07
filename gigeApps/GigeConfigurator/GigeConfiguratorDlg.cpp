
// GigeConfiguratorDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "GigeConfigurator.h"
#include "GigeConfiguratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CGigeConfiguratorDlg



CGigeConfiguratorDlg::CGigeConfiguratorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GIGECONFIGURATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGigeConfiguratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STARTED_CONFIG, _startConfigButton);
	DDX_Control(pDX, NO_START_CONFIG, _noStartConfigButton);
	DDX_Control(pDX, EDIT_LIB_FILE, _libFile);
	DDX_Control(pDX, APPLY_LIB_FILE_, _applyLib);
	DDX_Control(pDX, INPUT_LIB_TEXT, _libMessage);
	DDX_Control(pDX, IDC_COMBO1, _interfacesComboBox);
	DDX_Control(pDX, IDC_BUTTON4, _applyInterface);
	DDX_Control(pDX, INTERFACES_LIST_MESSAGE, _interfacesListMessage);
	DDX_Control(pDX, DEVICES_MESSAGE, _devicesMessage);
	DDX_Control(pDX, IDC_COMBO2, _devicesComboBox);
	DDX_Control(pDX, IDC_BUTTON1, _applyDevice);
	DDX_Control(pDX, IDC_COMBO3, _streamsComboBox);
	DDX_Control(pDX, IDC_BUTTON2, _applyStream);
	DDX_Control(pDX, STREAM_MESSAGE, _streamsMessage);
	DDX_Control(pDX, IDC_EDIT2, _properties[0]);
	DDX_Control(pDX, IDC_EDIT3, _properties[1]);
	DDX_Control(pDX, IDC_EDIT4, _properties[2]);
	DDX_Control(pDX, IDC_EDIT5, _properties[3]);
	DDX_Control(pDX, IDC_EDIT6, _properties[4]);
	DDX_Control(pDX, IDC_EDIT7, _properties[5]);
	DDX_Control(pDX, IDC_EDIT8, _properties[6]);
	DDX_Control(pDX, IDC_EDIT9, _properties[7]);
	DDX_Control(pDX, IDC_EDIT10, _properties[8]);
	DDX_Control(pDX, IDC_EDIT11, _properties[9]);
	DDX_Control(pDX, IDC_EDIT12, _properties[10]);
	DDX_Control(pDX, IDC_EDIT13, _properties[11]);
	DDX_Control(pDX, IDC_EDIT14, _properties[12]);
	DDX_Control(pDX, IDC_EDIT15, _properties[13]);
	DDX_Control(pDX, IDC_EDIT16, _properties[14]);
	DDX_Control(pDX, IDC_EDIT17, _properties[15]);
	DDX_Control(pDX, IDC_EDIT18, _values[0]);
	DDX_Control(pDX, IDC_EDIT19, _values[1]);
	DDX_Control(pDX, IDC_EDIT20, _values[2]);
	DDX_Control(pDX, IDC_EDIT21, _values[3]);
	DDX_Control(pDX, IDC_EDIT22, _values[4]);
	DDX_Control(pDX, IDC_EDIT23, _values[5]);
	DDX_Control(pDX, IDC_EDIT24, _values[6]);
	DDX_Control(pDX, IDC_EDIT25, _values[7]);
	DDX_Control(pDX, IDC_EDIT26, _values[8]);
	DDX_Control(pDX, IDC_EDIT27, _values[9]);
	DDX_Control(pDX, IDC_EDIT28, _values[10]);
	DDX_Control(pDX, IDC_EDIT29, _values[11]);
	DDX_Control(pDX, IDC_EDIT30, _values[12]);
	DDX_Control(pDX, IDC_EDIT31, _values[13]);
	DDX_Control(pDX, IDC_EDIT32, _values[14]);
	DDX_Control(pDX, IDC_EDIT33, _values[15]);
	DDX_Control(pDX, IDC_SCROLLBAR1, _propertyScroll);
}

BEGIN_MESSAGE_MAP(CGigeConfiguratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(STARTED_CONFIG, &CGigeConfiguratorDlg::OnBnClickedStartConfig)
	ON_BN_CLICKED(NO_START_CONFIG, &CGigeConfiguratorDlg::OnBnClickedNoStartConfig)
	ON_WM_TIMER()
	ON_BN_CLICKED(APPLY_LIB_FILE_, &CGigeConfiguratorDlg::OnBnClickedLibFile)
	ON_BN_CLICKED(IDC_BUTTON1, &CGigeConfiguratorDlg::OnBnClickedDeviceApply)
	ON_BN_CLICKED(IDC_BUTTON4, &CGigeConfiguratorDlg::OnBnClickedInterfaceApply)
	ON_BN_CLICKED(IDC_BUTTON2, &CGigeConfiguratorDlg::OnBnClickedStreamApply)
END_MESSAGE_MAP()


// Обработчики сообщений CGigeConfiguratorDlg

BOOL CGigeConfiguratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	InitConfigurator();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CGigeConfiguratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CGigeConfiguratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CGigeConfiguratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGigeConfiguratorDlg::InitConfigurator()
{
	SetTimer(1, 1000, 0);

	_configLayout.push_back(&_startConfigButton);
	_configLayout.push_back(&_noStartConfigButton);

	_libFile.SetWindowTextW(_T("bgapi2_gige.cti"));
	_libLayout.push_back(&_libMessage);
	_libLayout.push_back(&_libFile);
	_libLayout.push_back(&_applyLib);

	_interfaceLayout.push_back(&_interfacesComboBox);
	_interfaceLayout.push_back(&_interfacesListMessage);
	_interfaceLayout.push_back(&_applyInterface);

	_deviceLayout.push_back(&_devicesComboBox);
	_deviceLayout.push_back(&_devicesMessage);
	_deviceLayout.push_back(&_applyDevice);

	_streamLayout.push_back(&_streamsComboBox);
	_streamLayout.push_back(&_applyStream);
	_streamLayout.push_back(&_streamsMessage);


	for (size_t i = 0; i < 16; ++i)
	{
		_propertyLayout.push_back(&_properties[i]);
		_propertyLayout.push_back(&_values[i]);
	}
	_propertyLayout.push_back(&_propertyScroll);


	_stage = Stage::ConfigStage;
	ShowConfigStage();
}

void CGigeConfiguratorDlg::ShowConfigStage()
{
	HideAll();

	switch (_stage)
	{
	case Stage::PropertiesStage:
		ShowLayout(_propertyLayout);
	case Stage::StreamStage:
		ShowLayout(_streamLayout);
	case Stage::DeviceStage:
		ShowLayout(_deviceLayout);
	case Stage::InterfaceStage:
		ShowLayout(_interfaceLayout);
	case Stage::LibStage:
		ShowLayout(_libLayout);
	case Stage::ConfigStage:
		ShowLayout(_configLayout);
	}

}

void CGigeConfiguratorDlg::HideAll()
{
	HideLayout(_configLayout);
	HideLayout(_libLayout);
	HideLayout(_interfaceLayout);
	HideLayout(_deviceLayout);
	HideLayout(_streamLayout);
	HideLayout(_propertyLayout);
}

void CGigeConfiguratorDlg::HideLayout(const std::vector<CWnd*>& iLayout)
{
	for (size_t i = 0; i < iLayout.size(); ++i)
		(*iLayout[i]).ShowWindow(SW_HIDE);
}

void CGigeConfiguratorDlg::ShowLayout(const std::vector<CWnd*>& iLayout)
{
	for (size_t i = 0; i < iLayout.size(); ++i)
		(*iLayout[i]).ShowWindow(SW_SHOW);
}


void CGigeConfiguratorDlg::OnBnClickedStartConfig()
{
	_stage = LibStage;
	ShowConfigStage();
}


void CGigeConfiguratorDlg::OnBnClickedNoStartConfig()
{
	_stage = LibStage;
	ShowConfigStage();
}


void CGigeConfiguratorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CDialogEx::OnTimer(nIDEvent);
}


void CGigeConfiguratorDlg::OnBnClickedLibFile()
{
	CString libFile;
	_libFile.GetWindowTextW(libFile);

	std::string libStr(CT2A(libFile.GetString()));
	_gigeManager.UseLib(libStr);

	for (uint32_t i = 0; i < _gigeManager.GetIntefacesSize(); i++) 
	{
		std::string iface = _gigeManager.GetInterfaceName(i);
		_interfacesComboBox.AddString(CA2T(iface.c_str()));
	}

	if (_gigeManager.GetIntefacesSize() != 0)
		_interfacesComboBox.SetCurSel(0);

	_stage = InterfaceStage;
	ShowConfigStage();
}


void CGigeConfiguratorDlg::OnBnClickedDeviceApply()
{
	const auto index = _devicesComboBox.GetCurSel();
	_gigeManager.UseDevice(index);

	for (uint32_t i = 0; i < _gigeManager.GetStreamsSize(); i++)
	{
		std::string stream = _gigeManager.GetStreamName(i);
		_streamsComboBox.AddString(CA2T(stream.c_str()));
	}

	if (_gigeManager.GetStreamsSize() != 0)
		_streamsComboBox.SetCurSel(0);

	_stage = Stage::StreamStage;
	ShowConfigStage();
}


void CGigeConfiguratorDlg::OnBnClickedInterfaceApply()
{
	const auto index = _interfacesComboBox.GetCurSel();
	_gigeManager.UseInterface(index);

	for (uint32_t i = 0; i < _gigeManager.GetDevicesSize(); i++)
	{
		std::string dev = _gigeManager.GetDeviceName(i);
		_devicesComboBox.AddString(CA2T(dev.c_str()));
	}

	if (_gigeManager.GetDevicesSize() != 0)
		_devicesComboBox.SetCurSel(0);

	_stage = Stage::DeviceStage;
	ShowConfigStage();
}


void CGigeConfiguratorDlg::OnBnClickedStreamApply()
{
	const auto index = _streamsComboBox.GetCurSel();
	_gigeManager.UseStream(index);

	_stage = Stage::PropertiesStage;
	ShowConfigStage();
}
