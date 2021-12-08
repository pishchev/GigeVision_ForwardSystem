#include <iostream>
#include <objbase.h>

#include "../GigePreviewerDLL/GigePreviewerDLL_i.h"
#include "../GigePreviewerDLL/GigePreviewerDLL_i.c"


int main() {

  CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);

  IPreviewer* pPrev;

  HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_INPROC_SERVER, IID_IPreviewer, (LPVOID*)&pPrev);
  if (SUCCEEDED(hr)) {
    pPrev->AddRef();

    pPrev->StartAquisition();

    BYTE payloadSize = 0;
    pPrev->GetPayloadSize(&payloadSize);
    std::cout << "PayloadSize " << (int)payloadSize << std::endl;

    BYTE* image = new BYTE[(int)payloadSize];

    for (int rep = 0; rep < 4; rep++) {
      std::cout << pPrev->GetImage((int)payloadSize, image) << std::endl;
      for (int i = 0; i < (int)payloadSize; i++)
        std::cout << (int)image[i] << " ";
    }

    std::cout << std::endl;

    pPrev->Release();
  }
  else {
    return 1;
  }

  CoUninitialize();

  return 0;
}