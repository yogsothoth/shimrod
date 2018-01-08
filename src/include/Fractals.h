/*
 * Fractals.h
 */

#ifndef FRACTALS_H__
#define FRACTALS_H__

#include <vector>
#include <complex>

#include "Viewport.h"
#include "Image.h"

using std::vector;
using std::complex;

namespace shimrod {

  vector<vector<rgba_colour>>
  mandelbrot(const Viewport<int>& screen,
	     const Viewport<double>& space,
	     const int max_iterations,
	     vector<complex<double>(*)(const int, const int,
				       const Viewport<int>&,
				       const Viewport<double>&,
				       const complex<double>)>& projections);


} // namespace shimrod

#endif
