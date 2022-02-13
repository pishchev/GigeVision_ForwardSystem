// GigeVision.cpp: реализация CGigeVision

#include "pch.h"
#include "GigeVision.h"


// CGigeVision



STDMETHODIMP CGigeVision::TestMethod(CHAR* oBuff)
{
  oBuff[1] = 'e';

  return S_OK;
}


STDMETHODIMP CGigeVision::SetConfig(CHAR* iFile)
{
  _gigeManager.UseConfigurator(iFile);
  return S_OK;
}


STDMETHODIMP CGigeVision::PayloadSize(LONG* oPayloadSize)
{
  int64_t payloadSize = 0;
  _gigeManager.GetIntNode("PayloadSize", payloadSize);
  *oPayloadSize = (LONG)payloadSize;
  return S_OK;
}


STDMETHODIMP CGigeVision::StartCapturing()
{
  _gigeManager.AcquirerPreparing();
  _gigeManager.StartAcquisition();
  return S_OK;
}


STDMETHODIMP CGigeVision::GetImage(BYTE* oImage, LONG iBufferSize)
{
  _gigeManager.GetImage(oImage, iBufferSize);
  return S_OK;
}


STDMETHODIMP CGigeVision::GetWidth(LONG* oWidth)
{
  int64_t width = 0;
  _gigeManager.GetIntNode("Width", width);
  *oWidth = (LONG)width;
  return S_OK;
}


STDMETHODIMP CGigeVision::GetHeight(LONG* oHeight)
{
  int64_t height = 0;
  _gigeManager.GetIntNode("Height", height);
  *oHeight = (LONG)height;
  return S_OK;
}
