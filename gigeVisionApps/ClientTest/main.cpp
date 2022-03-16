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

  char file[] = "configH.txt";
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

  while (i < 200) {
    
    gige->GetBufferInfo((LONG*)&min, (LONG*)&max);

    std::cout << min << "-" << max << std::endl;

    if (i < min + 2) {
      std::cout << "SLOW " << i << "->" << i + 2 << std::endl;
      i = min + 2;
    }

    if (gige->GetImage((LONG*)&i, image, (LONG*)&payloadSize) == S_OK) {
      std::cout << "Image " << i << std::endl;
      i++;
    }
  }

  return 0;
}