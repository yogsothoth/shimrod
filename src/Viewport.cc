/*
 * Viewport.cc
 */

#include "include/Viewport.h"


namespace shimrod {
  complex<double>
  linear_projection(const int x, const int y,
		    const Viewport<int>& screen,
		    const Viewport<double>& space,
		    const complex<double> accumulator_complex) {
    complex<double> c((double)x / screen.width() * space.width() + space.get_x_min(),
                      (double)y / screen.height() * space.height() + space.get_y_min());
    return c;
  }
} // namespace shimrod
