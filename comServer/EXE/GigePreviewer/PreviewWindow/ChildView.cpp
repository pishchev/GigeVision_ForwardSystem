
// ChildView.cpp: реализация класса CChildView
//

#include "pch.h"
#include "framework.h"
#include "PreviewWindow.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
	CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_INPROC_SERVER, IID_IPreviewer, (LPVOID*)&_prev);

	_prev->AddRef();
	_prev->StartAquisition();
	_prev->GetPayloadSize(&_payloadSize);

	_image = new BYTE[(int)_payloadSize];
	_prev->GetImage((int)_payloadSize, _image);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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

	COLORREF color = RGB(_r, 0, 0);

	CRect rect;
	GetClientRect(&rect);
	_prev->GetImage((int)_payloadSize, _image);

	dc.DrawText(CString(std::to_string(_payloadSize).data()), rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	CDC* winDC = GetDC();
	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); // используется для проверки версии структуры
	bitmapInfo.bmiHeader.biBitCount = 3*8;           // количество бит на пиксель
	bitmapInfo.bmiHeader.biClrUsed = 0;              // в 24 битных изображениях не нужно
	bitmapInfo.bmiHeader.biClrImportant = 0;      // аналогично
	bitmapInfo.bmiHeader.biPlanes = 1;               // всегда 1 вроде как. Многоплановых bmp ни разу не видел
	bitmapInfo.bmiHeader.biCompression = BI_RGB; // без компрессии
	bitmapInfo.bmiHeader.biSizeImage = 0;         // для 24 бит, можем указать ноль, так как размер
																																 //изображения легко высчитывается. Обычно используется для компрессированных данных
	bitmapInfo.bmiHeader.biHeight = 640; // ширина и высота изображения.
	bitmapInfo.bmiHeader.biWidth = 640;
	
	HDC hdc = winDC->GetSafeHdc();
	SetDIBitsToDevice(hdc, 0, 0, 640, 640, 0, 0, 0, 640, _image, &bitmapInfo, DIB_RGB_COLORS);

	Invalidate(0);
	// TODO: Добавьте код обработки сообщений
	
	// Не вызывайте CWnd::OnPaint() для сообщений рисования
}

