#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>

typedef std::map<std::string, int64_t> IntNodes;

class Configurator
{
public:
  
  bool ReadConfig(std::string iFileName)
  {
    std::ifstream fd(iFileName);
    if (!fd.is_open())
      return false;

    std::string word;
    std::cout << std::endl;
    while (fd >> word)
    {
      if (word == "Lib")
        fd >> _lib;
      else if (word == "Interface")
        fd >> _interface;
      else if (word == "Device")
        fd >> _device;
      else if (word == "Stream")
        fd >> _stream;
      else {
        std::string param;
        fd >> param;
        _parameters[word] = std::stoi(param);
      }
    }

    fd.close();
    return true;
  }

  //console debug
  void PrintConfig()
  {
    std::cout << "Configuration: " << std::endl;

    std::cout << "Lib: " << _lib << std::endl;
    std::cout << "Interface: " << _interface << std::endl;
    std::cout << "Device: " << _device << std::endl;
    std::cout << "Stream: " << _stream << std::endl;

    for (auto it = _parameters.begin(); it != _parameters.end(); ++it)
      std::cout << it->first << ": " << it->second << std::endl;
  }

  void SaveConfig(std::string iFileName)
  {
    std::ofstream fd;
    fd.open(iFileName, 'w');

    fd << "Lib " << _lib << std::endl;
    fd << "Interface " << _interface << std::endl;
    fd << "Device " << _device << std::endl;
    fd << "Stream " << _stream << std::endl;

    for (auto it = _parameters.begin(); it != _parameters.end(); ++it)
      fd << it->first << " " << it->second << std::endl;

    fd.close();
  }

  std::string _lib;
  std::string _interface;
  std::string _device;
  std::string _stream;

  IntNodes _parameters;
};