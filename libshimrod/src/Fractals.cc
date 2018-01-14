/*
 * Fractals.cc
 */

#include <vector>
#include <complex>

#include "Viewport.h"
#include "Image.h"
#include "include/Fractals.h"

namespace shimrod {

  vector<vector<rgba_colour>>
  mandelbrot(const Viewport<int>& screen,
	     const Viewport<double>& space,
	     const int max_iterations,
	     vector<complex<double>(*)(const int,
				       const int,
				       const Viewport<int>&,
				       const Viewport<double>&,
				       const complex<double>)>& projections) {
    vector<vector<rgba_colour>> pixels {};
    pixels.resize(screen.height(), vector<rgba_colour>(screen.width()));
      
    for(int y=0; y<screen.height(); ++y) {
      for(int x=0; x<screen.width(); ++x) {
	complex<double> c;
	for(auto p : projections) {
	  c = p(x, y, screen, space, c);
	}
	
	complex<double> z(0);
	int iterations {0};
	while(abs(z)<2 && iterations < max_iterations) {
	  z = z * z + c;
	  ++iterations;
	}

	pixels[y][x] = convert_to_rgb_smooth(iterations, max_iterations);
      }
    }

    return pixels;
  }

   vector<vector<rgba_colour>>
   julia(const Viewport<int>& screen,
	 const Viewport<double>& space,
	 const int max_iterations,
	 vector<complex<double>(*)(const int,
				   const int,
				   const Viewport<int>&,
				   const Viewport<double>&,
				   const complex<double>)>& projections,
	 complex<double> k) {
    vector<vector<rgba_colour>> pixels {};
    pixels.resize(screen.height(), vector<rgba_colour>(screen.width()));
      
    for(int y=0; y<screen.height(); ++y) {
      for(int x=0; x<screen.width(); ++x) {
	complex<double> c;
	for(auto p : projections) {
	  c = p(x, y, screen, space, c);
	}
	
	complex<double> z(c);
	int iterations {0};
	while(abs(z)<2 && iterations < max_iterations) {
	  z = z * z + k;
	  ++iterations;
	}

	pixels[y][x] = convert_to_rgb_smooth(iterations, max_iterations);
      }
    }
    return pixels;
  }
} // namespace shimrod
