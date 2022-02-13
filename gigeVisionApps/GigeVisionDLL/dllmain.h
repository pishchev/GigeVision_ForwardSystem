// dllmain.h: объявление класса модуля.

class CGigeVisionDLLModule : public ATL::CAtlDllModuleT< CGigeVisionDLLModule >
{
public :
	DECLARE_LIBID(LIBID_GigeVisionDLLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GIGEVISIONDLL, "{07277cb7-d484-433a-a226-bc5cf676ff0a}")
	STDMETHOD(SetConfig)(CHAR* iFile);
	STDMETHOD(PayloadSize)(LONG* oPayloadSize);
	STDMETHOD(StartCapturing)();
	STDMETHOD(GetImage)(BYTE* oImage, LONG iBufferSize);
	STDMETHOD(GetWidth)(LONG* oWidth);
	STDMETHOD(GetHeight)(LONG* oHeight);
};

extern class CGigeVisionDLLModule _AtlModule;
