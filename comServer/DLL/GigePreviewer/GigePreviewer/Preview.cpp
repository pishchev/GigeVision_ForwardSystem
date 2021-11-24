// Preview.cpp: реализация CPreview

#include "pch.h"
#include "Preview.h"


// CPreview



STDMETHODIMP CPreview::get_Radius(DOUBLE* pVal)
{
  *pVal = m_dRadius;
  return S_OK;
}


STDMETHODIMP CPreview::put_Radius(DOUBLE newVal)
{
  m_dRadius = newVal;
  return S_OK;
}


STDMETHODIMP CPreview::GetArea(DOUBLE* Area)
{
  *Area = 3.14 * m_dRadius * m_dRadius;

  return S_OK;
}
