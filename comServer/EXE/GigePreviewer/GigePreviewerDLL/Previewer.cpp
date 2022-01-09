// Previewer.cpp: реализация CPreviewer

#include "pch.h"
#include "Previewer.h"


// CPreviewer


STDMETHODIMP CPreviewer::useLibrary(CHAR* libFile)
{
  //std::string lib = _bstr_t(libFile);
  gige.useLib(libFile);
  return S_OK;
}

STDMETHODIMP CPreviewer::getInterfacesSize(BYTE* oInterfacesSize)
{
  *oInterfacesSize = gige.getIntefacesSize();
  return S_OK;
}
STDMETHODIMP CPreviewer::getInterfaceName(CHAR* oName, BYTE iIndex)
{
  std::string name = gige.getInterfaceName((int)iIndex);
  memcpy(oName, name.data(), name.size() * sizeof(char));
  oName[name.size()] = '\0';
  return S_OK;
}
STDMETHODIMP CPreviewer::setInterface(CHAR* iInterface)
{
  gige.useInterface(iInterface);
  return S_OK;
}

STDMETHODIMP CPreviewer::getDevicesSize(BYTE* oDevicesSize)
{
  *oDevicesSize = gige.getDevicesSize();
  return S_OK;
}
STDMETHODIMP CPreviewer::getDeviceName(CHAR* oName, BYTE iIndex)
{
  std::string name = gige.getDeviceName((int)iIndex);
  memcpy(oName, name.data(), name.size() * sizeof(char));
  oName[name.size()] = '\0';
  return S_OK;
}
STDMETHODIMP CPreviewer::setDevice(CHAR* iDevice)
{
  gige.useDevice(iDevice);
  return S_OK;
}

STDMETHODIMP CPreviewer::getStreamsSize(BYTE* oStreamsSize)
{
  *oStreamsSize = gige.getStreamsSize();
  return S_OK;
}
STDMETHODIMP CPreviewer::getStreamName(CHAR* oName, BYTE iIndex)
{
  std::string name = gige.getStreamName((int)iIndex);
  memcpy(oName, name.data(), name.size() * sizeof(char));
  oName[name.size()] = '\0';
  return S_OK;
}
STDMETHODIMP CPreviewer::setStream(CHAR* iStream)
{
  gige.useStream(iStream);
  return S_OK;
}

STDMETHODIMP CPreviewer::cameraInit()
{
  gige.cameraInit();
  return S_OK;
}

STDMETHODIMP CPreviewer::useConfig(CHAR* node)
{
  gige.useConfigurator(node);
  return S_OK;
}

STDMETHODIMP CPreviewer::saveConfig(CHAR* node)
{
  gige.SaveConfig(node);
  return S_OK;
}

STDMETHODIMP CPreviewer::getNodesSize(BYTE* size)
{
  *size = (BYTE)gige.getNodesSize();
  return S_OK;
}
STDMETHODIMP CPreviewer::getNodeName(CHAR* oName, BYTE iIndex)
{
  std::string name = gige.getNodeName((uint32_t)iIndex);
  memcpy(oName, name.data(), name.size() * sizeof(char));
  oName[name.size()] = '\0';
  return S_OK;
}
STDMETHODIMP CPreviewer::getNodeVisibility(BYTE* oVis, BYTE iIndex)
{
  *oVis = (BYTE)gige.getNodeVisibility((uint32_t)iIndex);
  return S_OK;
}
STDMETHODIMP CPreviewer::getNodeAccessMode(BYTE* oAm, BYTE iIndex)
{
  *oAm = (BYTE)gige.getNodeAccess((uint32_t)iIndex);
  return S_OK;
}
STDMETHODIMP CPreviewer::getNodeType(BYTE* oType, BYTE iIndex)
{
  *oType = (BYTE)gige.getNodeType((uint32_t)iIndex);
  return S_OK;
}


STDMETHODIMP CPreviewer::getIntNode(CHAR* node, LONG* oVal)
{
  int64_t val;
  gige.GetIntNode(node, val);
  *oVal = (LONG)val;
  return S_OK;
}

STDMETHODIMP CPreviewer::setIntNode(CHAR* node, LONG iVal)
{
  gige.SetIntNode(node, (int64_t)iVal);
  return S_OK;
}

STDMETHODIMP CPreviewer::getEnumStrNode(CHAR* node, CHAR* oVal)
{
  std::string val;
  gige.GetEnumStrNode(node, val);
  memcpy(oVal, val.data(), val.size() * sizeof(char));
  oVal[val.size()] = '\0';
  return S_OK;
}
STDMETHODIMP CPreviewer::getStrNode(CHAR* node, CHAR* oVal)
{
  std::string val;
  gige.GetStrNode(node, val);
  memcpy(oVal, val.data(), val.size() * sizeof(char));
  oVal[val.size()] = '\0';
  return S_OK;
}


STDMETHODIMP CPreviewer::startAquisition()
{
  gige.acquirerPreparing();
  gige.startAcquisition();
  return S_OK;
}


STDMETHODIMP CPreviewer::getImage(BYTE* image, LONG len)
{
  gige.waitNext();
  return gige.getImage(image, len) ? S_OK : S_FALSE;
}
