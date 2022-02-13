// dllmain.h: объявление класса модуля.

class CGigeVisionDLLModule : public ATL::CAtlDllModuleT< CGigeVisionDLLModule >
{
public :
	DECLARE_LIBID(LIBID_GigeVisionDLLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GIGEVISIONDLL, "{07277cb7-d484-433a-a226-bc5cf676ff0a}")
};

extern class CGigeVisionDLLModule _AtlModule;
