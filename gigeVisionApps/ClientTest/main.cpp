#include <iostream>
#include <iomanip>
#include <objbase.h>
#include <comdef.h>
#include <string>
#include <chrono>
#include <atlbase.h>

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

  wchar_t file[] = L"configHS.txt";
  gige->SetConfig(CComBSTR(file));

  size_t width = 0;
  size_t height = 0;
  gige->GetImageInfo((LONG*)&width, (LONG*)&height);
  size_t payloadSize = width * height * 2;

  std::cout << "PayloadSize: " << payloadSize << "; Width: " << width << "; Height: " << height << std::endl;
  gige->Start();

  unsigned char* image = new unsigned char[payloadSize];

  size_t i = 0;
  size_t min = 0;
  size_t max = 0;
  LONG timestamp = 0;
  LONG lastTimestamp = 0;
  auto chrono = std::chrono::steady_clock::now();
  
  while (i < 200) {
    
    gige->GetFifoInfo((LONG*)&min, (LONG*)&max);

    if (i < min + 2) {
      std::cout << "SLOW " << i << "->" << i + 2 << std::endl;
      i = min + 2;
    }

    if (gige->GetImage((LONG)i, eImagePixelFormat::eIP_UYVY_FAST, image, (LONG)payloadSize, &timestamp) == S_OK) {
      const auto lastChrono = chrono;
      chrono = std::chrono::steady_clock::now();
      std::cout << "Image[" << i
        << "] " << min << "-" << max
        << "; DeltaTimestamp: " << (int)(timestamp - lastTimestamp)
        << "; DeltaChrono: " << std::chrono::duration_cast<std::chrono::microseconds>(chrono - lastChrono).count()
        << std::endl;
      i++;
      lastTimestamp = timestamp;
    }
    else Sleep(1);
  }

  return 0;
}