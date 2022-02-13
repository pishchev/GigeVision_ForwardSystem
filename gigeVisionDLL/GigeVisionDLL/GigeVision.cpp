// GigeVision.cpp: реализация CGigeVision

#include "pch.h"
#include "GigeVision.h"


// CGigeVision



STDMETHODIMP CGigeVision::TestMethod(CHAR* oBuff)
{
  oBuff[1] = 'e';

  return S_OK;
}
