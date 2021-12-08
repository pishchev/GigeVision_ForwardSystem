﻿// Previewer.cpp: реализация CPreviewer

#include "pch.h"
#include "Previewer.h"


// CPreviewer



STDMETHODIMP CPreviewer::GetImage(LONG iLen, BYTE* oImage)
{
  auto res = gige.getImage(oImage, payloadSize);
  gige.waitNext();
  return S_OK;
}


STDMETHODIMP CPreviewer::StartAquisition()
{
  gige.configuration(config);
  gige.acquirerPreparing();
  gige.startAcquisition();
  payloadSize = gige.imageSize();

  gige.waitNext();
  return S_OK;
}


STDMETHODIMP CPreviewer::GetPayloadSize(LONG* oPayloadSize)
{
  *oPayloadSize = payloadSize;
  return S_OK;
}
