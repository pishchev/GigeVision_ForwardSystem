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
    pPrev->put_Radius(5);
    double rad, area;

    pPrev->get_Radius(&rad);
    pPrev->GetArea(&area);
    std::cout << "Radius: " << rad << " | Area: " << area << std::endl;

    pPrev->Release();
  }
  else {
    return 1;
  }

  CoUninitialize();

  return 0;
}