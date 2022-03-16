// GigeVision.cpp: реализация CGigeVision

#include "pch.h"
#include "GigeVision.h"


// CGigeVision

STDMETHODIMP CGigeVision::SetConfig(CHAR* iFile)
{
  _gigeManager.UseConfigurator(iFile);
  return S_OK;
}


STDMETHODIMP CGigeVision::PayloadSize(LONG* oPayloadSize)
{
  *oPayloadSize = (LONG)_gigeManager.PayloadSize();
  return S_OK;
}


STDMETHODIMP CGigeVision::StartCapturing()
{
  _gigeManager.AcquirerPreparing();
  _gigeManager.StartAcquisition();
  return S_OK;
}


STDMETHODIMP CGigeVision::GetImage(LONG* iImageIndex, BYTE* oImage, LONG* iBufferSize)
{
  return _gigeManager.GetImage((size_t)*iImageIndex, oImage) ? S_OK : S_FALSE;
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


STDMETHODIMP CGigeVision::GetBufferInfo(LONG* oMinIndex, LONG* oMaxIndex)
{
  size_t min, max;
  _gigeManager.GetBufferInfo(min, max);
  *oMinIndex = (LONG)min;
  *oMaxIndex = (LONG)max;
  return S_OK;
}


STDMETHODIMP CGigeVision::GetTimestamp(LONG* iIndexTimestamp, LONG* oTimestamp)
{
  size_t time;
  _gigeManager.GetTimestamp((size_t)*iIndexTimestamp, time);
  *oTimestamp = (LONG)time;

  return S_OK;
}
