// GigePreviewer.cpp: реализация WinMain


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "GigePreviewer_i.h"
#include "xdlldata.h"


using namespace ATL;


class CGigePreviewerModule : public ATL::CAtlExeModuleT< CGigePreviewerModule >
{
public :
	DECLARE_LIBID(LIBID_GigePreviewerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GIGEPREVIEWER, "{d6744a0b-28a2-4840-99cc-8656a3337006}")
};

CGigePreviewerModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

