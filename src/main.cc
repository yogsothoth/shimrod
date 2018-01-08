/*
  shimrod
  The imaginary part of Murgen
  Mandelbrot set explorer
*/

#include <iostream>
#include <complex>
#include <vector>
#include <tuple>
#include <string>

#include "include/Viewport.h"
#include "include/Image.h"
#include "include/Fractals.h"

using std::cout;
using std::endl;
using std::complex;
using std::vector;
using std::tuple;
using std::string;

using shimrod::Viewport;
using shimrod::write_image;
using shimrod::mandelbrot;
using shimrod::rgba_colour;
using shimrod::linear_projection;

int
main(int argc, char **argv) {
  Viewport<int> screen(0,800 , 0, 600);
  Viewport<double> space(-2.0, 2.0, -2.0, 2.0);

  vector<complex<double>(*)(const int, const int,
			    const Viewport<int>&,
			    const Viewport<double>&,
			    const complex<double>)> projections;

  projections.push_back(&linear_projection);
  
  int i = 0;
  while(i < 50) {
    double step = space.size()/100;
    double move = step;

    std::string filename = std::string("shimrod_mandelbrot");

    if(i < 10) {
      filename = filename + "0";
    }
    
    filename = filename + std::to_string(i) + std::string(".png");
    space = Viewport<double>(space.get_x_min() + step + move,
			     space.get_x_max() - step,
			     space.get_y_min() + step,
			     space.get_y_max() - step - move);
    vector<vector<rgba_colour>> pixels = mandelbrot(screen, space, 50, projections);
    write_image(pixels, screen, filename);
    ++i;
  }
  
  return 0;
}
