#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>

typedef std::map<std::string, int64_t> IntNodes;

class Configurator
{
public:
  
  bool ReadConfig(std::string fileName)
  {
    std::ifstream fd(fileName);
    if (!fd.is_open())
      return false;

    std::string word;
    std::cout << std::endl;
    while (fd >> word)
    {
      if (word == "Lib")
        fd >> lib;
      else if (word == "Interface")
        fd >> intface;
      else if (word == "Device")
        fd >> device;
      else if (word == "Stream")
        fd >> stream;
      else {
        std::string param;
        fd >> param;
        parameters[word] = std::stoi(param);
      }
    }

    fd.close();
    return true;
  }

  //console debug
  void PrintConfig()
  {
    std::cout << "Configuration: " << std::endl;

    std::cout << "Lib: " << lib << std::endl;
    std::cout << "Interface: " << intface << std::endl;
    std::cout << "Device: " << device << std::endl;
    std::cout << "Stream: " << stream << std::endl;

    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
      std::cout << it->first << ": " << it->second << std::endl;
    }
  }

  void SaveConfig(std::string fileName)
  {
    std::ofstream fd;
    fd.open(fileName, 'w');

    fd << "Lib " << lib << std::endl;
    fd << "Interface " << intface << std::endl;
    fd << "Device " << device << std::endl;
    fd << "Stream " << stream << std::endl;

    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
      fd << it->first << " " << it->second << std::endl;
    }

    fd.close();
  }

  std::string lib;
  std::string intface;
  std::string device;
  std::string stream;

  IntNodes parameters;
};