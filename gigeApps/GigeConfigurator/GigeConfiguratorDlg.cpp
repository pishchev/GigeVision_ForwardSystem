
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
}

BEGIN_MESSAGE_MAP(CGigeConfiguratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(STARTED_CONFIG, &CGigeConfiguratorDlg::OnBnClickedStartConfig)
	ON_BN_CLICKED(NO_START_CONFIG, &CGigeConfiguratorDlg::OnBnClickedNoStartConfig)
	ON_WM_TIMER()
	ON_BN_CLICKED(APPLY_LIB_FILE_, &CGigeConfiguratorDlg::OnBnClickedLibFile)
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
	SetTimer(1, 500, 0);

	_stage = Stage::ConfigStage;

	_configLayout.push_back(&_startConfigButton);
	_configLayout.push_back(&_noStartConfigButton);

	_libFile.SetWindowTextW(_T("TLSimu.cti"));
	_libLayout.push_back(&_libMessage);
	_libLayout.push_back(&_libFile);
	_libLayout.push_back(&_applyLib);

	_interfaceLayout.push_back(&_interfacesComboBox);
	_interfaceLayout.push_back(&_interfacesListMessage);
	_interfaceLayout.push_back(&_applyInterface);

}

void CGigeConfiguratorDlg::Configurate()
{
	HideAll();

	switch (_stage)
	{
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
}


void CGigeConfiguratorDlg::OnBnClickedNoStartConfig()
{
	_stage = LibStage;
}


void CGigeConfiguratorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	Configurate();
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

	_stage = InterfaceStage;
}
