#include <iostream>
#include <objbase.h>
#include <comdef.h>
#include <string>

#include "../GigePreviewerDLL/GigePreviewerDLL_i.h"
#include "../GigePreviewerDLL/GigePreviewerDLL_i.c"


void chooseInterface(IPreviewer* pPrev)
{
  BYTE interfacesSize;
  pPrev->getInterfacesSize(&interfacesSize);
  for (int i = 0; i < (int)interfacesSize; ++i)
  {
    CHAR buffer[50];
    pPrev->getInterfaceName(buffer, (BYTE)i);
    std::cout << i << ")" << buffer << std::endl;
  }

  uint32_t intIndex;
  std::cin >> intIndex;
  CHAR buffer[50];
  pPrev->getInterfaceName(buffer, (BYTE)intIndex);
  pPrev->setInterface(buffer);
}
void chooseDevice(IPreviewer* pPrev)
{
  BYTE devicesSize;
  pPrev->getDevicesSize(&devicesSize);
  for (int i = 0; i < (int)devicesSize; ++i)
  {
    CHAR buffer[50];
    pPrev->getDeviceName(buffer, (BYTE)i);
    std::cout << i << ")" << buffer << std::endl;
  }

  CHAR buffer[50];
  uint32_t devIndex;
  std::cin >> devIndex;
  pPrev->getDeviceName(buffer, (BYTE)devIndex);
  pPrev->setDevice(buffer);
}
void chooseStream(IPreviewer* pPrev)
{
  BYTE streamsSize;
  pPrev->getStreamsSize(&streamsSize);
  for (int i = 0; i < (int)streamsSize; ++i)
  {
    CHAR buffer[50];
    pPrev->getStreamName(buffer, (BYTE)i);
    std::cout << i << ")" << buffer << std::endl;
  }

  CHAR buffer[50];
  uint32_t devIndex;
  std::cin >> devIndex;
  pPrev->getStreamName(buffer, (BYTE)devIndex);
  pPrev->setStream(buffer);
}


void noConfig(IPreviewer* pPrev)
{
  CHAR lib[] = "TLSimu.cti";
  pPrev->useLibrary(lib);

  chooseInterface(pPrev);
  chooseDevice(pPrev);
  chooseStream(pPrev);
}

int main() {

  CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);

  IPreviewer* pPrev;

  HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_INPROC_SERVER, IID_IPreviewer, (LPVOID*)&pPrev);
  if (SUCCEEDED(hr)) {
    pPrev->AddRef();
    std::cout << "Instance: OK" << std::endl;

    noConfig(pPrev);
    
    pPrev->cameraInit();


    pPrev->Release();
  }
  else {
    std::cout << "Instance: FAIL" << std::endl;
    return 1;
  }

  CoUninitialize();

  return 0;
}