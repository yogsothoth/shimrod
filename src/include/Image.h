/*
 * Image.h
 */

#ifndef IMAGE_H__
#define IMAGE_H__

#include <tuple>
#include <vector>
#include <string>
#include <Magick++.h>
#include "Viewport.h"

using Magick::Color;
using Magick::Quantum;
using Magick::Geometry;
using Magick::Image;

using std::tuple;
using std::vector;
using std::string;

namespace shimrod {
using rgba_colour = std::tuple<int, int, int, int>;

 int rgba_red(const rgba_colour& c);
 int rgba_green(const rgba_colour& c);
 int rgba_blue(const rgba_colour& c);
 int rgba_alpha(const rgba_colour& c);
    
 rgba_colour convert_to_rgb_smooth(int n, int iter_max);

  void
  write_image(const vector<vector<rgba_colour>> pixels,
	      const Viewport<int>& screen,
	      string filename);
} // namespace shimrod


#endif
