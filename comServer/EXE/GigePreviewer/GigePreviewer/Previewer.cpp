// Previewer.cpp: реализация CPreviewer

#include "pch.h"
#include "Previewer.h"


// CPreviewer



STDMETHODIMP CPreviewer::get_Radius(DOUBLE* pVal)
{
  // TODO: Добавьте сюда код реализации
  *pVal = _rad;
  return S_OK;
}


STDMETHODIMP CPreviewer::put_Radius(DOUBLE newVal)
{
  // TODO: Добавьте сюда код реализации
  _rad = newVal;
  return S_OK;
}


STDMETHODIMP CPreviewer::GetArea(DOUBLE* pArea)
{
  // TODO: Добавьте сюда код реализации
  *pArea = 3.14 * _rad * _rad;
  return S_OK;
}
