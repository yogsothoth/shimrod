/* 
 * Viewport.h
 */
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <complex>

namespace shimrod {

  template<typename T>
  class Viewport {
    T _x_min, _x_max, _y_min, _y_max;

  public:
    Viewport(T x_min, T x_max, T y_min, T y_max)
      : _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max)
    {}

    T get_x_min() const { return _x_min;}
    T get_x_max() const { return _x_max;}
    T get_y_min() const { return _y_min;}
    T get_y_max() const { return _y_max;}

    T height() const { return _y_max - _y_min; }
    T width() const { return _x_max - _x_min; }
    T size() const { return height() * width(); }
    
  };

  /* projections screen -> space */
  std::complex<double>
  linear_projection(const int x, const int y,
		    const Viewport<int>& screen,
		    const Viewport<double>& space,
		    const std::complex<double> accumulator_complex);
} //namespace shimrod

#endif // VIEWPORT_H
