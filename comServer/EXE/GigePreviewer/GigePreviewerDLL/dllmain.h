// dllmain.h: объявление класса модуля.

class CGigePreviewerDLLModule : public ATL::CAtlDllModuleT< CGigePreviewerDLLModule >
{
public :
	DECLARE_LIBID(LIBID_GigePreviewerDLLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GIGEPREVIEWERDLL, "{91122f49-007b-4c2c-bd1e-9eec38eae568}")
};

extern class CGigePreviewerDLLModule _AtlModule;
