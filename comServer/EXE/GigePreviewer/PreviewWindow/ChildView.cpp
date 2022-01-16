
// ChildView.cpp: реализация класса CChildView
//

#include "pch.h"
#include "framework.h"
#include "PreviewWindow.h"
#include "ChildView.h"
#include "GigeProprtyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
	HRESULT coIn = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
  HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_INPROC_SERVER, IID_IPreviewer, (LPVOID*)&_prev);
	useConfig(_prev);

	_width = 1280;
	_height = 1280;

	setIntNode(_prev, "Width", _width);
	setIntNode(_prev, "Height", _height);

	_payloadSize = (LONG)getIntNode(_prev, "PayloadSize");
	_bitsPerPixel = _payloadSize / (_width * _height);

	_image = new BYTE[(int)_payloadSize];
	_imType = _bitsPerPixel == 1 ? Mono : RGB;

	_prev->startAquisition();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// Обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // контекст устройства для рисования

	CRect rect;
	GetClientRect(&rect);

	dc.DrawText(CString(std::to_string(_payloadSize).data()), rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	CDC* winDC = GetDC();
	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); // используется для проверки версии структуры
	bitmapInfo.bmiHeader.biBitCount = (WORD)_bitsPerPixel*8;           // количество бит на пиксель
	bitmapInfo.bmiHeader.biClrUsed = 0;              // в 24 битных изображениях не нужно
	bitmapInfo.bmiHeader.biClrImportant = 0;      // аналогично
	bitmapInfo.bmiHeader.biPlanes = 1;               // всегда 1 вроде как. Многоплановых bmp ни разу не видел
	bitmapInfo.bmiHeader.biCompression = BI_RGB; // без компрессии
	bitmapInfo.bmiHeader.biSizeImage = 0;         // для 24 бит, можем указать ноль, так как размер
																																 //изображения легко высчитывается. Обычно используется для компрессированных данных
	bitmapInfo.bmiHeader.biHeight = _height; // ширина и высота изображения.
	bitmapInfo.bmiHeader.biWidth = _width;
	
	HDC hdc = winDC->GetSafeHdc();
	_prev->getImage(_image, (LONG)_payloadSize);
	SetDIBitsToDevice(hdc, 0, 0, _width, _height, 0, 0, 0, _width, _image, &bitmapInfo, DIB_RGB_COLORS);

	//Invalidate(0);
	// TODO: Добавьте код обработки сообщений
	
	// Не вызывайте CWnd::OnPaint() для сообщений рисования
}



void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CGigeProprtyDlg dlg(this);
	if (IDOK == dlg.DoModal()) {
		//_prev = dlg.xxx();
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate(FALSE);
	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	SetTimer(101, 100, NULL);
	return 0;
}
