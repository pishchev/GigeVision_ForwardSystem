#include <iostream>
#include <iomanip>
#include <objbase.h>
#include <comdef.h>
#include <string>

#include "../GigeVisionDLL/GigeVisionDLL_i.h"
#include "../GigeVisionDLL/GigeVisionDLL_i.c"

int main()
{
  std::cout << "Start client" << std::endl;

  HRESULT coIn = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
  if (!SUCCEEDED(coIn)) {
    std::cout << "CoInitializeEx error" << std::endl;
    return 1;
  }

  IGigeVision* gige;
  HRESULT hr = CoCreateInstance(CLSID_GigeVision, nullptr, CLSCTX_INPROC_SERVER, IID_IGigeVision, (LPVOID*)&gige);
  if (!SUCCEEDED(hr)) {
    std::cout << "Instance fail" << std::endl;
    return 1;
  }

  char test[] = "ttst";
  gige->TestMethod(test);
  std::cout << test << std::endl;

  return 0;
}