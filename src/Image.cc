/*
 * Image.cc
*/

#include "include/Image.h"

namespace shimrod {
  int rgba_red(const rgba_colour& c) { return std::get<0>(c); }
  int rgba_green(const rgba_colour& c) { return std::get<1>(c); }
  int rgba_blue(const rgba_colour& c) { return std::get<2>(c); }
  int rgba_alpha(const rgba_colour& c) { return std::get<3>(c); }
    
  rgba_colour convert_to_rgb_smooth(int n, int iter_max) {
    // // map n on the 0..1 interval
    double t = (double)n/(double)iter_max;

    // Use smooth polynomials for r, g, b
    int r = (int)(9*(1-t)*t*t*t*QuantumRange);
    int g = (int)(15*(1-t)*(1-t)*t*t*QuantumRange);
    int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*QuantumRange);	

    return rgba_colour(r, g, b, 0);
  }

  void
  write_image(const vector<vector<rgba_colour>> pixels,
	      const Viewport<int>& screen,
	      string filename) {
    Image image = Image(Geometry(screen.width(), screen.height()),
			Color(QuantumRange, QuantumRange, QuantumRange, 0));

    int iy {0};
    for(auto& y : pixels) {
      int ix {0};

      for(auto& x : y) {
	image.pixelColor(ix, iy,
			 Color(rgba_red(x),
			       rgba_green(x),
			       rgba_blue(x),
			       rgba_alpha(x)));
	//	image.pixelColor(ix, iy, Color(std::get<0>(x), std::get<1>(x), std::get<2>(x), 0));
	++ix;
      }
      ++iy;
    }
    image.write(filename);
  }			
} // namespace shimrod
