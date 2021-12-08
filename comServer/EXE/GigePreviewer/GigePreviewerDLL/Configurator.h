#pragma once
#include <iostream>

struct CameraConfigInt
{
  CameraConfigInt()
  {
    _value = 0;
    _active = false;
  }
  CameraConfigInt(int value)
  {
    _value = value;
    _active = true;
  }
  CameraConfigInt& operator=(int value)
  {
    _value = value;
    _active = true;
    return *this;
  }
  int _value;
  bool _active;
};

class Configurator
{
public:
  Configurator()
  {
    ctiFile = "TLSimu.cti";
    interfaceIndex = 0;
    deviceIndex = 1;
    streamIndex = 0;

    width = 640;
    height = 640;
  }

  std::string ctiFile;
  uint32_t interfaceIndex;
  uint32_t deviceIndex; 
  uint32_t streamIndex;

  CameraConfigInt width;
  CameraConfigInt height;
};