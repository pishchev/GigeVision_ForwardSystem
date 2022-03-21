// GigeVision.cpp: реализация CGigeVision

#include "pch.h"
#include "GigeVision.h"


// CGigeVision

STDMETHODIMP CGigeVision::SetConfig(BSTR bstrFileName)
{
  char str[MAX_PATH * 2];
  WideCharToMultiByte(CP_ACP, 0, bstrFileName, -1, str, _countof(str), NULL, NULL);
  std::string szFileName(str);
  _gigeManager.UseConfigurator(szFileName);
  return S_OK;
}


STDMETHODIMP CGigeVision::Stop()
{
  _gigeManager.StopAcquisition();
  return S_OK;
}


STDMETHODIMP CGigeVision::Start()
{
  _gigeManager.AcquirerPreparing();
  _gigeManager.StartAcquisition();
  return S_OK;
}


STDMETHODIMP CGigeVision::GetImage(LONG iImageIndex, eImagePixelFormat iFormat, BYTE* oImage, LONG iImageSize, LONG* oImageTimestamp)
{
  switch (iFormat) {
  case eImagePixelFormat::eIP_RAW:
    _gigeManager.SetConverter(ConverterType::Raw);
    break;
  case eImagePixelFormat::eIP_RGB24_FAST:
    _gigeManager.SetConverter(ConverterType::Bayer_RGB24_NoInt);
    break;
  case eImagePixelFormat::eIP_RGB24_FINE:
    _gigeManager.SetConverter(ConverterType::Bayer_RGB24_Int);
    break;
  }

  const auto res = _gigeManager.GetImage((size_t)iImageIndex, oImage) ? S_OK : S_FALSE;
  if (res == S_OK) {
    size_t tmp = 0;
    _gigeManager.GetTimestamp((size_t)iImageIndex, tmp);
    *oImageTimestamp = (LONG)tmp;
  }

  return res;
}


STDMETHODIMP CGigeVision::GetImageInfo(LONG* oWidth, LONG* oHeight)
{
  int64_t width = 0;
  int64_t height = 0;

  _gigeManager.GetIntNode("Width", width);
  _gigeManager.GetIntNode("Height", height);

  *oWidth = (LONG)width;
  *oHeight = (LONG)height;
  return S_OK;
}

STDMETHODIMP CGigeVision::GetFifoInfo(LONG* oMinIndex, LONG* oMaxIndex)
{
  size_t min, max;
  _gigeManager.GetBufferInfo(min, max);
  *oMinIndex = (LONG)min;
  *oMaxIndex = (LONG)max;
  return S_OK;
}
