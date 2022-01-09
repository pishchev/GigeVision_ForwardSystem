#include <iostream>
#include <iomanip>
#include <objbase.h>
#include <comdef.h>
#include <string>

#include "../GigePreviewerDLL/GigePreviewerDLL_i.h"
#include "../GigePreviewerDLL/GigePreviewerDLL_i.c"


void chooseInterface(IPreviewer* pPrev)
{
  BYTE interfacesSize;
  pPrev->getInterfacesSize(&interfacesSize);
  for (int i = 0; i < (int)interfacesSize; ++i)
  {
    CHAR buffer[50];
    pPrev->getInterfaceName(buffer, (BYTE)i);
    std::cout << i << ")" << buffer << std::endl;
  }

  uint32_t intIndex;
  std::cin >> intIndex;
  CHAR buffer[50];
  pPrev->getInterfaceName(buffer, (BYTE)intIndex);
  pPrev->setInterface(buffer);
}
void chooseDevice(IPreviewer* pPrev)
{
  BYTE devicesSize;
  pPrev->getDevicesSize(&devicesSize);
  for (int i = 0; i < (int)devicesSize; ++i)
  {
    CHAR buffer[50];
    pPrev->getDeviceName(buffer, (BYTE)i);
    std::cout << i << ")" << buffer << std::endl;
  }

  CHAR buffer[50];
  uint32_t devIndex;
  std::cin >> devIndex;
  pPrev->getDeviceName(buffer, (BYTE)devIndex);
  pPrev->setDevice(buffer);
}
void chooseStream(IPreviewer* pPrev)
{
  BYTE streamsSize;
  pPrev->getStreamsSize(&streamsSize);
  for (int i = 0; i < (int)streamsSize; ++i)
  {
    CHAR buffer[50];
    pPrev->getStreamName(buffer, (BYTE)i);
    std::cout << i << ")" << buffer << std::endl;
  }

  CHAR buffer[50];
  uint32_t devIndex;
  std::cin >> devIndex;
  pPrev->getStreamName(buffer, (BYTE)devIndex);
  pPrev->setStream(buffer);
}

void noConfig(IPreviewer* pPrev)
{
  CHAR lib[] = "TLSimu.cti";
  pPrev->useLibrary(lib);

  chooseInterface(pPrev);
  chooseDevice(pPrev);
  chooseStream(pPrev);

  pPrev->cameraInit();
}
void useConfig(IPreviewer* pPrev)
{
  std::string cfg = "config.txt";
  CHAR* conf = cfg.data();
  pPrev->useConfig(conf);
}

int64_t getIntNode(IPreviewer* pPrev, std::string node)
{
  CHAR* nodeName = node.data();
  LONG val;
  pPrev->getIntNode(nodeName, &val);
  return (int64_t)val;
}
std::string getEnumStrNode(IPreviewer* pPrev, std::string node)
{
  CHAR* nodeName = node.data();
  CHAR val[50];
  pPrev->getEnumStrNode(nodeName, val);
  return val;
}
std::string getStrNode(IPreviewer* pPrev, std::string node)
{
  CHAR* nodeName = node.data();
  CHAR val[50];
  pPrev->getStrNode(nodeName, val);
  return val;
}

void setIntNode(IPreviewer* pPrev, std::string node, int64_t iVal)
{
  CHAR* nodeName = node.data();
  pPrev->setIntNode(nodeName, (LONG)iVal);
}

void saveConfig(IPreviewer* pPrev, std::string fileConfig)
{
  CHAR* file = fileConfig.data();
  pPrev->saveConfig(file);
}

void gettingImage(IPreviewer* pPrev, int64_t payloadSize)
{
  unsigned char* image = new unsigned char[payloadSize];

  while (true)
  {
    if (pPrev->getImage(image, (LONG)payloadSize) == S_OK)
      for (int i = 0; i < payloadSize; i++)
      {
        std::cout << ' ' << (int)image[i];
      }
    std::cout << std::endl;
    system("pause");
  }
}

void showNodes(IPreviewer* pPrev)
{
  //узлы
  BYTE nodesSize;
  pPrev->getNodesSize(&nodesSize);

  std::cout << std::setw(8) << std::right << "Name"
    << std::setw(47) << std::right << "V"
    << std::setw(5) << std::right << "AM"
    << std::setw(5) << std::right << "T"
    << std::setw(6) << std::right << "Val" << std::endl;

  CHAR nameBuf[50];
  for (uint32_t i = 0; i < (uint32_t)nodesSize; i++)
  {
    BYTE vis, am, tp;
    pPrev->getNodeName(nameBuf, (BYTE)i);
    pPrev->getNodeVisibility(&vis, (BYTE)i);
    pPrev->getNodeAccessMode(&am, (BYTE)i);
    pPrev->getNodeType(&tp, (BYTE)i);

    std::cout << std::setw(3) << std::right << i << ")" << std::setw(50) << std::left << nameBuf
      << std::setw(5) << std::left << (int)vis
      << std::setw(5) << std::left << (int)am
      << std::setw(5) << std::left << (int)tp;

    if ((int)tp == 2)
      std::cout << getIntNode(pPrev, nameBuf);
    else if ((int)tp == 9)
      std::cout << getEnumStrNode(pPrev, nameBuf);
    else if ((int)tp == 6)
      std::cout << getStrNode(pPrev, nameBuf);

    std::cout << std::endl;
  }
}

int main() {

  CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);

  IPreviewer* pPrev;

  HRESULT hr = CoCreateInstance(CLSID_Previewer, nullptr, CLSCTX_INPROC_SERVER, IID_IPreviewer, (LPVOID*)&pPrev);
  if (SUCCEEDED(hr)) {
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
  }
  else {
    std::cout << "Instance: FAIL" << std::endl;
    return 1;
  }

  CoUninitialize();

  return 0;
}