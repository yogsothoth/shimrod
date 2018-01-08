/*
 * Fractals.cc
 */

#include "include/Fractals.h"

namespace shimrod {

  vector<vector<rgba_colour>>
  //  mandelbrot(const Viewport<int>& screen , const Viewport<double>& space, const int max_iterations) {
  mandelbrot(const Viewport<int>& screen , const Viewport<double>& space, const int max_iterations, vector<complex<double>(*)(const int, const int, const Viewport<int>&, const Viewport<double>&, const complex<double>)>& projections) {
    vector<vector<rgba_colour>> pixels {};
    pixels.resize(screen.height(), vector<rgba_colour>(screen.width()));
      
    for(int y=0; y<screen.height(); ++y) {
      for(int x=0; x<screen.width(); ++x) {
	//	cout << "Iterating [" << y << "][" << x << "]" << endl;
	complex<double> c;
	//	cout << "Size " << projections.size() << endl;
	for(auto p : projections) {
	  c = p(x, y, screen, space, c);
	}
	
	//complex<double> c = linear_projection(x, y, screen, space);
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


} // namespace shimrod
