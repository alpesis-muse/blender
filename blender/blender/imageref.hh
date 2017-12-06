
#pragma once
#include <string>
#include <memory>
#include "../utils/mat.h"
#include "../utils/imgproc.hh"
#include "match_info.hh"

// A transparent reference to a image in file
struct ImageRef {
  std::string fname;
  Mat32f* img = nullptr;
  int _width, _height;

  ImageRef(const std::string& fname): fname(fname) {}
  //ImageRef(const ImageRef& ) = delete;  // TODO make it work
  ~ImageRef() { if (img) delete img; }

  // Reading image from a url
  void load() {
    if (img) return;
    img = new Mat32f{read_img(fname.c_str())};
    _width = img->width();
    _height = img->height();
  }

  void release() { if (img) delete img; img = nullptr; }

  int width() const { return _width; }
  int height() const { return _height; }
  Shape2D shape() const { return {_width, _height}; }

};
