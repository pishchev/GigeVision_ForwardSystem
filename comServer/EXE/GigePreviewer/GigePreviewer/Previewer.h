// Previewer.h: объявление CPreviewer

#pragma once
#include "resource.h"       // основные символы



#include "GigePreviewer_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CPreviewer

class ATL_NO_VTABLE CPreviewer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPreviewer, &CLSID_Previewer>,
	public IDispatchImpl<IPreviewer, &IID_IPreviewer, &LIBID_GigePreviewerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CPreviewer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CPreviewer)
	COM_INTERFACE_ENTRY(IPreviewer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(get_Radius)(DOUBLE* pVal);
	STDMETHOD(put_Radius)(DOUBLE newVal);
	STDMETHOD(GetArea)(DOUBLE* pArea);

private:
	double _rad;
};

OBJECT_ENTRY_AUTO(__uuidof(Previewer), CPreviewer)
