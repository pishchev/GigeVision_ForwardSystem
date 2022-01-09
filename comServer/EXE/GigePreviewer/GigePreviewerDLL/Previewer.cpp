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
