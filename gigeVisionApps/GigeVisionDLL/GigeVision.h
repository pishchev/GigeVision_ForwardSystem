// GigeVision.h: объявление CGigeVision

#pragma once
#include "resource.h"       // основные символы



#include "GigeVisionDLL_i.h"
#include "GigeManager.hpp"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CGigeVision

class ATL_NO_VTABLE CGigeVision :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGigeVision, &CLSID_GigeVision>,
	public IGigeVision
{
public:
	CGigeVision()
	{
		m_pUnkMarshaler = nullptr;
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CGigeVision)
	COM_INTERFACE_ENTRY(IGigeVision)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

public:
	
	GigeManager _gigeManager;

	STDMETHOD(SetConfig)(BSTR bstrFileName);
	STDMETHOD(Stop)();
	STDMETHOD(Start)();
	STDMETHOD(GetImage)(LONG iImageIndex, eImagePixelFormat iFormat, BYTE* oImage, LONG iImageSize, LONG* oImageTimestamp);
	STDMETHOD(GetImageInfo)(LONG* oWidth, LONG* oHeight);
	STDMETHOD(GetFifoInfo)(LONG* oMinIndex, LONG* oMaxIndex);
};

OBJECT_ENTRY_AUTO(__uuidof(GigeVision), CGigeVision)
