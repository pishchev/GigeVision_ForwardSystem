#pragma once
#include <iostream>

class Configurator
{
public:
  Configurator()
  {
    ctiFile = "TLSimu.cti";
    interfaceIndex = 0;
    deviceIndex = 1;
    streamIndex = 0;

    width = 8;
    height = 8;
  }

  std::string ctiFile;
  size_t interfaceIndex;
  size_t deviceIndex;
  size_t streamIndex;

  size_t width;
  size_t height;
};