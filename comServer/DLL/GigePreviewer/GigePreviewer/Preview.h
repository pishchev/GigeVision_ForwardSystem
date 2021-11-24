// Preview.h: объявление CPreview

#pragma once
#include "resource.h"       // основные символы



#include "GigePreviewer_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CPreview

class ATL_NO_VTABLE CPreview :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPreview, &CLSID_Preview>,
	public IDispatchImpl<IPreview, &IID_IPreview, &LIBID_GigePreviewerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CPreview()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CPreview)
	COM_INTERFACE_ENTRY(IPreview)
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
	STDMETHOD(GetArea)(DOUBLE* Area);

private:
	double m_dRadius;
};

OBJECT_ENTRY_AUTO(__uuidof(Preview), CPreview)
