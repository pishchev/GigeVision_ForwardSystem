// Previewer.cpp: реализация CPreviewer

#include "pch.h"
#include "Previewer.h"


// CPreviewer




STDMETHODIMP CPreviewer::StartAcquisition()
{
  // TODO: Добавьте сюда код реализации
  gige.configuration(config);
  gige.acquirerPreparing();
  gige.startAcquisition();
  payloadSize = gige.imageSize();

  gige.waitNext();
  return S_OK;
}


STDMETHODIMP CPreviewer::GetPayloadSize(BYTE* oPayloadSize)
{
  // TODO: Добавьте сюда код реализации
  *oPayloadSize = payloadSize;
  return S_OK;
}


STDMETHODIMP CPreviewer::GetImage(BYTE* oImage)
{
  // TODO: Добавьте сюда код реализации
  auto res = gige.getImage(oImage, payloadSize);
  gige.waitNext();
  return res ? S_OK : S_FALSE;
}
