#include <iostream>
#include <objbase.h>

#include "../GigePreviewer/GigePreviewer_i.h"
#include "../GigePreviewer/GigePreviewer_i.c"


int main() {

  CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);

  IPreviewer* pPrev;

  HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_LOCAL_SERVER, IID_IPreviewer, (LPVOID*)&pPrev);
  if (SUCCEEDED(hr)) {
    pPrev->AddRef();

    pPrev->StartAcquisition();
    BYTE payloadSize;
    pPrev->GetPayloadSize(&payloadSize);

    std::cout << "Payload size: " << (int)payloadSize << std::endl;

    unsigned char* image = new unsigned char[(int)payloadSize];
    for (int i = 0; i < payloadSize; i++)
    {
      std::cout << ' ' << (int)(image[i]);
    }

    for (int i = 0; i < 3; i++) {
      std::cout << std::endl << std::endl;
      std::cout << pPrev->GetImage(image) << std::endl;
      for (int i = 0; i < payloadSize; i++)
      {
        std::cout << ' ' << (int)(image[i]);
      }
    }

    delete[] image;
    pPrev->Release();
  }
  else {
    return 1;
  }

  CoUninitialize();

  return 0;
}