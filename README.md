# Shimrod
Shimrod is a simple Mandelbrot and Julia fractals explorer.

## Building
Shimrod relies on:
* ImageMagick to create image files
* cmake (>= 3.2.10) to build
* clang (>= 4.0) to compile.

To build Shimrod, clone the repository:
```
$ git clone https://github.com/yogsothoth/shimrod.git
$ mkdir shimrod-build
$ cd shimrod-build
$ cmake ../shimrod
$ make
```

## Usage
To generate a simple Mandelbrot representation, just from where you built shimrod (shimrod-build in the example above):
```
$ ./shimrod-cli/shimrod
$ feh -F ./shimrod_pictures/shimrod_mandelbrot_001.png
```	

Below are all the options supported for Mandelbrot fractal generation:

* -a|--algorithm
  Algorithm used to generate the fractals. Either mandelbrot or julia. Default: mandelbrot
* -i|--iterations
  Maximum number of iterations per complex in the escape time algorithm. Default: 50
* --screen-height
  Screen height in pixels. Default: 1200
* --screen-width
  Screen width in pixels. Default: 1920
* --x0|--space_x0
  Complex space x (real part) minimum. Default: -2.0
* --x1|--space_x1
  Complex space x (real part) maximum. Default: 2.0
* --y0|--space_y0
  Complex space y (imaginary part) minimum. Default: -2.0
* --y1|--space_y1
  Complex space y (imaginary part) maximum. Default: 2.0
* -f|--filename
  Base name for the file(s) generated. Default: shimrod_<algorithm>
* --number--pics
  Total number of pictures to generate. Default: 1
* --step
  Zoom in step as a proportion of the size of the space. Default: 100
* -d|--directory
  Output directory. The path is created if it doesn't exist. Default: shimrod_pictures
When generating Julia fractals, the following two extra options can be used to specify the constant:
* --kr
  Julia k constant complex, real part. Default: 0.274
* --ki
  Julia k constant complex, imaginary part. Default: -0.008

## Limitations
Shimrod is just a toy, and has only been tested on FreeBSD 11.
Online help (the usual usage() thing) seems broken in https://github.com/catchorg/Clara (or, rather, I couldn't figure out how to make it work).

