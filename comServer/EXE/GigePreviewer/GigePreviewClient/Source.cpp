#include "GigeHelper.hpp"

int main() {

  HRESULT coIn = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
  if (!SUCCEEDED(coIn)) {
    std::cout << "CoInitializeEx error" << std::endl;
    return 1;
  }

  IPreviewer* pPrev;
  HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_INPROC_SERVER, IID_IPreviewer, (LPVOID*)&pPrev);
  if (!SUCCEEDED(hr)) {
    std::cout << "Instance fail" << std::endl;
    return 1;
  }

  pPrev->AddRef();
  std::cout << "Instance: OK" << std::endl;

  std::cout << "Use config: ";
  int conf;
  std::cin >> conf;

  conf ? useConfig(pPrev) : noConfig(pPrev);

  setIntNode(pPrev, "Width", 8);
  setIntNode(pPrev, "Height", 8);

  int64_t payloadSize = getIntNode(pPrev, "PayloadSize");

  showNodes(pPrev);
  saveConfig(pPrev, "config.txt");

  pPrev->startAquisition();
  gettingImage(pPrev, payloadSize);

  pPrev->Release();

  CoUninitialize();

  return 0;
}