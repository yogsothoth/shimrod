/*
 * Fractals.h
 */

#ifndef FRACTALS_H
#define FRACTALS_H

#include <vector>
#include <complex>

#include "Viewport.h"
#include "Image.h"

namespace shimrod {

  std::vector<std::vector<rgba_colour>>
  mandelbrot(const Viewport<int>& screen,
	     const Viewport<double>& space,
	     const int max_iterations,
	     std::vector<std::complex<double>(*)(const int, const int,
				       const Viewport<int>&,
				       const Viewport<double>&,
						 const std::complex<double>)>& projections);


  std::vector<vector<rgba_colour>>
  julia(const Viewport<int>& screen,
	const Viewport<double>& space,
	const int max_iterations,
	std::vector<complex<double>(*)(const int, const int,
				  const Viewport<int>&,
				  const Viewport<double>&,
				       const std::complex<double>)>& projections,
	std::complex<double> k);


} // namespace shimrod

#endif // FRACTALS_H
