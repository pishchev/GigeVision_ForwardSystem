#pragma once
#include <vector>

class BayerConverter {
public:
  enum PixType {
    R, G, B
  };

  BayerConverter(unsigned char* iBuffer, size_t iWidth, size_t iHeight) : _width(iWidth), _height(iHeight), _buffer(iBuffer)
  {
  }

  int GetPixel(int h, int w) {
    if (h < 0 || h >= static_cast<int>(_height)|| w < 0 || w >= static_cast<int>(_width))
      return 0;
    return _buffer[h * _width + w];
  }

  int Interpolate(size_t h, size_t w, PixType t) {

    const auto lt = h % 2 == 0 ? B : R;
    const auto pt = w % 2 == 0 ? G : lt;

    auto b = [&](int h, int w) {return GetPixel(h, w); };

    if (t == G) {
      if (pt == G)
        return (b(h, w) + b(h + 1, w + 1) + b(h - 1, w + 1) + b(h + 1, w - 1) + b(h - 1, w - 1))/5;
      else
        return (b(h, w + 1) + b(h, w - 1) + b(h + 1, w) + b(h - 1, w))/4;
    }
    else if (lt == t) {
      if (pt == t) {
        return b(h, w);
      }
      else {
        return (b(h, w + 1) + b(h, w - 1))/2;
      }
    }
    else {
      if (pt == G) {
        return (b(h + 1, w) + b(h + 1, w))/2;
      }
      else {
        return (b(h + 1, w + 1) + b(h - 1, w + 1) + b(h + 1, w - 1) + b(h - 1, w - 1))/4;
      }
    }

    return 0;
  }

  void ConvertToRGB(unsigned char* oBuffer) {
    
    for (size_t h = 0; h < _height; ++h)
      for (size_t w = 0; w < _width; ++w) {
      oBuffer[h * _width*3 + w*3] = Interpolate(h, w, R);
      oBuffer[h * _width*3 + w*3 + 1] = Interpolate(h, w, G);
      oBuffer[h * _width*3 + w*3 + 2] = Interpolate(h, w, B);
      }
  }

private:
  size_t _width;
  size_t _height;

  unsigned char* _buffer;
};