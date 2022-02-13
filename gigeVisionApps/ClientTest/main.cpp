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

  char file[] = "config.txt";
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

  for (size_t i = 0; i < 10; ++i)
  {
    gige->GetImage(image, payloadSize);

    for (size_t k = 0; k < payloadSize; ++k)
    {
      std::cout << (int)image[k] << ' ';
    }
    std::cout << std::endl << std::endl;
  }


  return 0;
}