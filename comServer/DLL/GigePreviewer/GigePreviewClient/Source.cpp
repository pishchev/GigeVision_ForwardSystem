#include <iostream>
#include <objbase.h>
#include "../GigePreviewer/GigePreviewer_i.c"
#include "../GigePreviewer/GigePreviewer_i.h"

int main() {
  std::cout << "Start..." << std::endl;

  CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);

  IPreview* pPrev;
  HRESULT hr = CoCreateInstance(CLSID_Preview, nullptr, CLSCTX_INPROC_SERVER, IID_IPreview, (LPVOID*)&pPrev);

  if (SUCCEEDED(hr)) {
    pPrev->AddRef();
    pPrev->put_Radius(5);
    double rad, area;
    pPrev->get_Radius(&rad);
    pPrev->GetArea(&area);
    std::cout << "Radius: " << rad <<"\nArea: " << area << std::endl;
    pPrev->Release();
  }

  CoUninitialize();

  return 0;
}