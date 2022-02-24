
// GigePreviewDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "GigePreview.h"
#include "GigePreviewDlg.h"
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


// Диалоговое окно CGigePreviewDlg



CGigePreviewDlg::CGigePreviewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GIGEPREVIEW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGigePreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, _configMessage);
	DDX_Control(pDX, IDC_EDIT1, _configFile);
	DDX_Control(pDX, IDC_BUTTON1, _configApply);
	DDX_Control(pDX, IDOK, _exitButton);
}

BEGIN_MESSAGE_MAP(CGigePreviewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGigePreviewDlg::OnBnClickedApplyConfig)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Обработчики сообщений CGigePreviewDlg

BOOL CGigePreviewDlg::OnInitDialog()
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

	Init();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CGigePreviewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGigePreviewDlg::OnPaint()
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
HCURSOR CGigePreviewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGigePreviewDlg::Init()
{
	_exitButton.ShowWindow(HIDE_WINDOW);
	SetTimer(100, 100, 0);
	InitDialogComponents();
	InitGigeDLL();
}

void CGigePreviewDlg::InitGigeDLL()
{
	HRESULT coIn = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	if (!SUCCEEDED(coIn)) {
		PostQuitMessage(0);
	}

	HRESULT hr = CoCreateInstance(CLSID_GigeVision, nullptr, CLSCTX_INPROC_SERVER, IID_IGigeVision, (LPVOID*)&_gige);
	if (!SUCCEEDED(hr)) {
		PostQuitMessage(0);
	}
}

void CGigePreviewDlg::InitDialogComponents()
{
	_configMessage.SetWindowTextW(_T("Config file:"));
	_configFile.SetWindowTextW(_T("config.txt"));
}

void CGigePreviewDlg::HideDialogComponents()
{
	_configMessage.ShowWindow(HIDE_WINDOW);
	_configFile.ShowWindow(HIDE_WINDOW);
	_configApply.ShowWindow(HIDE_WINDOW);
	_exitButton.ShowWindow(SW_SHOW);
}

void CGigePreviewDlg::OnBnClickedApplyConfig()
{
	CString configFile;
	_configFile.GetWindowTextW(configFile);

	std::string config = CT2A(configFile.GetString());
	HideDialogComponents();

	_gige->SetConfig(config.data());
	_gige->PayloadSize((LONG*)&_payloadSize);
	_gige->GetWidth((LONG*)&_width);
	_gige->GetHeight((LONG*)&_height);
	_bitsPerPixel = _payloadSize / (_width * _height);

	_image = new BYTE[(int)_payloadSize];
	_started = true;

	_gige->StartCapturing();
}

void CGigePreviewDlg::ShowImage()
{
	CDC* winDC = GetDC();
	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); // используется для проверки версии структуры
	bitmapInfo.bmiHeader.biBitCount = (WORD)_bitsPerPixel * 8;           // количество бит на пиксель
	bitmapInfo.bmiHeader.biClrUsed = 0;              // в 24 битных изображениях не нужно
	bitmapInfo.bmiHeader.biClrImportant = 0;      // аналогично
	bitmapInfo.bmiHeader.biPlanes = 1;               // всегда 1 вроде как. Многоплановых bmp ни разу не видел
	bitmapInfo.bmiHeader.biCompression = BI_RGB; // без компрессии
	bitmapInfo.bmiHeader.biSizeImage = 0;         // для 24 бит, можем указать ноль, так как размер
																																 //изображения легко высчитывается. Обычно используется для компрессированных данных
	bitmapInfo.bmiHeader.biHeight = _height; // ширина и высота изображения.
	bitmapInfo.bmiHeader.biWidth = _width;

	HDC hdc = winDC->GetSafeHdc();
	_gige->GetImage(_image, (LONG)_payloadSize);
	SetDIBitsToDevice(hdc, 0, 0, _width, _height, 0, 0, 0, _height, _image, &bitmapInfo, DIB_RGB_COLORS);
}

void CGigePreviewDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (_started)
	{
		Invalidate(FALSE);
		ShowImage();
	}
	CDialogEx::OnTimer(nIDEvent);
}
