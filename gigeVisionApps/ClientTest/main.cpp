#include <iostream>
#include <iomanip>
#include <objbase.h>
#include <comdef.h>
#include <string>
#include <chrono>

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

  char file[] = "configHS.txt";
  gige->SetConfig(file);

  size_t payloadSize = 0;
  gige->PayloadSize((LONG*)&payloadSize);
  size_t width = 0;
  gige->GetWidth((LONG*)&width);
  size_t height = 0;
  gige->GetHeight((LONG*)&height);

  std::cout << "PayloadSize: " << payloadSize << "; Width: " << width << "; Height: " << height << std::endl;
  gige->StartCapturing();

  unsigned char* image = new unsigned char[payloadSize];

  size_t i = 0;
  size_t min = 0;
  size_t max = 0;
  size_t lastMax = 0;
  LONG timestamp = 0;
  auto chrono = std::chrono::steady_clock::now();
  auto lastCh = chrono;

  while (i < 200) {
    
    gige->GetBufferInfo((LONG*)&min, (LONG*)&max);

    if (i < min + 2) {
      std::cout << "SLOW " << i << "->" << i + 2 << std::endl;
      i = min + 2;
    }

    if (0) {
      lastCh = std::chrono::steady_clock::now();
      if (gige->GetImage((LONG*)&i, image, (LONG*)&payloadSize) == S_OK) {

        std::cout << min << "-" << max << std::endl;
        LONG lastTs = timestamp;

        gige->GetTimestamp((LONG*)&i, &timestamp);
        std::cout << "Image " << i
          //<< "; Timestamp: " << (uint64_t)timestamp 
          << "; DeltaTimestamp: " << (int)(timestamp - lastTs)
          << "; DeltaChrono: " << std::chrono::duration_cast<std::chrono::microseconds>(lastCh - chrono).count()
          << std::endl;

        chrono = std::chrono::steady_clock::now();

        i++;
      }
    }
    else if (1) {

      lastCh = std::chrono::steady_clock::now();
      if (lastMax != max) {
        std::cout << "DeltaChrono: " << std::chrono::duration_cast<std::chrono::microseconds>(lastCh - chrono).count() << std::endl;

        lastMax = max;
        i = max;
        chrono = std::chrono::steady_clock::now();
      }
    }
  }

  return 0;
}