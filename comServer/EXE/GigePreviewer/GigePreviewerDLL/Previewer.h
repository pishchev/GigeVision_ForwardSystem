// Previewer.h: объявление CPreviewer

#pragma once
#include "resource.h"       // основные символы



#include "GigePreviewerDLL_i.h"


#include "GigeManager.hpp"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CPreviewer

class ATL_NO_VTABLE CPreviewer :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CPreviewer, &CLSID_Previewer>,
	public IPreviewer
{
public:
	CPreviewer()
	{
		m_pUnkMarshaler = nullptr;
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CPreviewer)
	COM_INTERFACE_ENTRY(IPreviewer)
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



	STDMETHOD(GetImage)(short iLen, BYTE* oImage);

private:
	GigeManager gige;
	Configurator config;
	size_t payloadSize;
public:
	STDMETHOD(StartAquisition)();
	STDMETHOD(GetPayloadSize)(BYTE* oPayloadSize);
};

OBJECT_ENTRY_AUTO(__uuidof(Previewer), CPreviewer)
