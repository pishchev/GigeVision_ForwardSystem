// dllmain.cpp: реализация DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "GigeVisionDLL_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CGigeVisionDLLModule _AtlModule;

// Точка входа DLL
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}


STDMETHODIMP CGigeVisionDLLModule::SetConfig(CHAR* iFile)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::PayloadSize(LONG* oPayloadSize)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::StartCapturing()
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::GetImage(BYTE* oImage, LONG iBufferSize)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::GetWidth(LONG* oWidth)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::GetHeight(LONG* oHeight)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::GetBufferInfo(LONG* oMinIndex, LONG* oMaxIndex)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}


STDMETHODIMP CGigeVisionDLLModule::GetTimestamp(LONG* iIndexTimestamp, LONG* oTimestamp)
{
	// TODO: Добавьте сюда код реализации

	return S_OK;
}
