#pragma once
#include <vector>
#include <memory>

class BayerConverter;
class BayerConverterRGBInterpolated;
class BayerConverterRGBNoInterpolated;

typedef std::shared_ptr<BayerConverter> ConverterPtr;
typedef std::shared_ptr<BayerConverterRGBInterpolated> RGBIntPtr;
typedef std::shared_ptr<BayerConverterRGBNoInterpolated> RGBNoIntPtr;

class BayerConverter {
public:
  unsigned char GetRawPixel(int h, int w) {
    if (h < 0 || h >= static_cast<int>(_height) || w < 0 || w >= static_cast<int>(_width))
      return 0;
    return _buffer[h * _width + w];
  }

  virtual void Convert(unsigned char* oBuffer) = 0;

  size_t _width;
  size_t _height;
  unsigned char* _buffer;
};

class BayerConverterRGB : public BayerConverter {
public:
  enum PixType {
    R, G, B
  };
};

class BayerConverterRGBInterpolated : public BayerConverterRGB {
public:
  unsigned char Interpolate(int h, int w, PixType t) {

    const auto lt = h % 2 == 1 ? B : R;
    const auto pt = w % 2 == 0 ? G : lt;

    auto b = [&](int h, int w) {return GetRawPixel(h, w); };

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

  void Convert(unsigned char* oBuffer) override {
    
    for (size_t h = 0; h < _height; ++h)
      for (size_t w = 0; w < _width; ++w) {
      oBuffer[h * _width*3 + w*3] = Interpolate((int)h, (int)w, R);
      oBuffer[h * _width*3 + w*3 + 1] = Interpolate((int)h, (int)w, G);
      oBuffer[h * _width*3 + w*3 + 2] = Interpolate((int)h, (int)w, B);
      }
  }
};

class BayerConverterRGBNoInterpolated : public BayerConverterRGB {
public:
  unsigned char GetPixel(int h, int w, PixType t) {

    const auto lt = h % 2 == 0 ? R : B;
    const auto pt = w % 2 == 0 ? G : lt;

    auto b = [&](int h, int w) {return GetRawPixel(h, w); };

    if (t == G) {
      if (pt == G)
        return b(h, w);
      else if (lt == R)
        return b(h, w - 1);
      else 
        return b(h, w + 1);
    }
    else if (t == R) {
      if (pt == t)
        return b(h, w);
      else if (pt == B)
        return b(h + 1, w + 1);
      else if (lt == R)
        return b(h, w + 1);
      else 
        return b(h + 1, w);
    }
    else {
      if (pt == B)
        return b(h, w);
      else if (pt == R)
        return b(h - 1, w - 1);
      else if (lt == R)
        return b(h - 1, w);
      else
        return b(h, w - 1);
    }

    return 0;
  }

  void Convert(unsigned char* oBuffer) override {

    for (size_t h = 0; h < _height; ++h)
      for (size_t w = 0; w < _width; ++w) {
        oBuffer[h * _width * 3 + w * 3] = GetPixel((int)h, (int)w, R);
        oBuffer[h * _width * 3 + w * 3 + 1] = GetPixel((int)h, (int)w, G);
        oBuffer[h * _width * 3 + w * 3 + 2] = GetPixel((int)h, (int)w, B);
      }
  }
};