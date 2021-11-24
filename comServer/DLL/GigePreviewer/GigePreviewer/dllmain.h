// dllmain.h: объявление класса модуля.

class CGigePreviewerModule : public ATL::CAtlDllModuleT< CGigePreviewerModule >
{
public :
	DECLARE_LIBID(LIBID_GigePreviewerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GIGEPREVIEWER, "{ff68c777-c91e-4f6e-aec0-4a771b607c6c}")
};

extern class CGigePreviewerModule _AtlModule;
