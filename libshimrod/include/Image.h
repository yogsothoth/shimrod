/*
 * Image.h
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <tuple>
#include <vector>
#include <string>

#include "Magick++-no-warn.h"
#include "Viewport.h"

namespace shimrod {
using rgba_colour = std::tuple<int, int, int, int>;

 int rgba_red(const rgba_colour& c);
 int rgba_green(const rgba_colour& c);
 int rgba_blue(const rgba_colour& c);
 int rgba_alpha(const rgba_colour& c);
    
 rgba_colour convert_to_rgb_smooth(int n, int iter_max);

  void
  write_image(const std::vector<std::vector<rgba_colour>> pixels,
	      const shimrod::Viewport<int>& screen,
	      std::string filename);
} // namespace shimrod


#endif // IMAGE_H
