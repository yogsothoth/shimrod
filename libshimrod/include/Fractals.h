/*
 * Fractals.h
 */

#ifndef FRACTALS_H
#define FRACTALS_H

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


  vector<vector<rgba_colour>>
  julia(const Viewport<int>& screen,
	const Viewport<double>& space,
	const int max_iterations,
	vector<complex<double>(*)(const int, const int,
				  const Viewport<int>&,
				  const Viewport<double>&,
				  const complex<double>)>& projections,
	complex<double> k);


} // namespace shimrod

#endif // FRACTALS_H
