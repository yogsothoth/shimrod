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
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <algorithm>
#include <functional>
#include <chrono>

#include "include/Viewport.h"
#include "include/Image.h"
#include "include/Fractals.h"

// turn off warnings for clara
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextra-semi"
#include "clara.hpp"
#pragma clang diagnostic pop

#include "easylogging++.h"

using std::cout;
using std::endl;
using std::complex;
using std::vector;
using std::tuple;
using std::string;

using shimrod::Viewport;
using shimrod::write_image;
using shimrod::mandelbrot;
using shimrod::julia;
using shimrod::rgba_colour;
using shimrod::linear_projection;

using namespace clara;

void
calculate_and_write(string& algorithm,
		    string& filename,
		    Viewport<int>& screen,
		    Viewport<double>& space,
		    int iterations,
		    vector<complex<double>(*)(const int,
					      const int,
					      const Viewport<int>&,
					      const Viewport<double>&,
					      const complex<double>)> projections,
		    complex<double>& k) {
  LOG(INFO) << "Working on " << filename << "...";
  LOG(INFO) << " Calculating pixels...";

  vector<vector<rgba_colour>> pixels;
  if(algorithm == "mandelbrot") {
    pixels = mandelbrot(screen, space, iterations, projections);
  }
  else if(algorithm == "julia") {
    //    complex<double> k(julia_kr, julia_ki);
    pixels = julia(screen, space, iterations, projections, k);
  }

  LOG(INFO) << " Writing the picture...";
  write_image(pixels, screen, filename);
      
  LOG(INFO) << " Done." << endl;
}

INITIALIZE_EASYLOGGINGPP

int
main(int argc, char **argv) {
  // variables to hold command-line arguments
  double julia_kr {0.274};
  double julia_ki {-0.008};
  string algorithm {"mandelbrot"};
  int screen_height {1200};
  int screen_width {1920};
  int iterations {50};
  double space_x0 {-2.0};
  double space_x1 {2.0};
  double space_y0 {-2.0};
  double space_y1 {2.0};
  string filename_base {"shimrod"};
  int number_pics {1};
  int zoom_step {100};
  bool help { true };
  string directory {"shimrod_pictures"};
  
  Viewport<int> screen(0,800 , 0, 600);
  Viewport<double> space(-2.0, 2.0, -2.0, 2.0);

  auto cli =
    Help(help)
    |
    Opt(julia_kr, "julia_kr")
    ["--kr"]
    ("Julia k constant complex, real part. Default: 0.274")
    |
    Opt(julia_ki, "julia_ki")
    ["--ki"]
    ("Julia k constant complex, imaginary part. Default: -0.008")
    |
    Opt(algorithm, "algorithm")
    ["-a"] ["--algorithm"]
    ("Algorithm used to generate the fractals. Either mandelbrot or julia. Default: mandelbrot")
    |
    Opt(iterations, "iterations")
    ["-i"] ["--iterations"]
    ("Maximum number of iterations per complex in the escape time algorithm. Default: 50")
    |
    Opt(screen_height, "screen_height")
    ["--screen-height"]
    ("Screen height in pixels. Default: 1200")
    |
    Opt(screen_width, "screen_width")
    ["--screen-width"]
    ("Screen width in pixels. Default: 1920")
    |
    Opt(space_x0, "space_x0")
    ["--x0"] ["--space_x0"]
    ("Complex space x (real part) minimum. Default: -2.0")
    |
    Opt(space_x1, "space_x1")
    ["--x1"] ["--space_x1"]
    ("Complex space x (real part) maximum. Default: 2.0")
    |
    Opt(space_y0, "space_y0")
    ["--y0"] ["--space_y0"]
    ("Complex space y (imaginary part) minimum. Default: -2.0")
    |
    Opt(space_y1, "space_y1")
    ["--x0"] ["--space_y1"]
    ("Complex space y (imaginary part) maximum. Default: 2.0")
    |
    Opt(filename_base, "filename_base")
    ["-f"] ["--filename"]
    ("Base name for the file(s) generated. Default: shimrod_<algorithm>")
    |
    Opt(number_pics, "number_pics")
    ["--number-pics"]
    ("Total number of pictures to generate. Default: 1")
    |
    Opt(zoom_step, "zoom_step")
    ["--step"]
    ("Zoom in step as a proportion of the size of the space. Default: 100")
    |
    Opt(directory, "directory")
    ["-d"] ["--directory"]
    ("Output directory. The path is created if it doesn't exist. Default: shimrod_pictures");

    auto result = cli.parse(Args(argc, argv));
    if(!result) {
      LOG(FATAL) << "Error in command line: "
		 << result.errorMessage() << endl;
      exit(1);
    }
    
    if( (algorithm != "mandelbrot") && (algorithm != "julia") ) {
      LOG(FATAL) << "Error in command line: algorithm must be one of "
		 << "'mandelbrot' or 'julia'"
		 << " (provided: " << algorithm << ")" << endl;
	exit(1);
    }

    if(filename_base == "shimrod") {
      filename_base = filename_base + "_" + algorithm;
    }

    /* when std::experimental::fs is available
    fs::path p(directory);
    
    if(! fs::exists(p)) {
      std::error_code ec;
      if(! fs::create_directories(p, ec)) {
	  LOG(FATAL) << "Error creating the output directory: the path " << p.string() << " could not be created. Reason: " << ec.message() << "." << endl;
	  exit(1);
	}
    }
    */

    // Simple POSIX method
    struct stat sb;
    if(! (stat(directory.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
      LOG(INFO) << "Creating output directory "
		<< directory << "." << endl;
      // create the directory
      if(mkdir(directory.c_str(), 0744) == -1) {
	LOG(FATAL) << "Error creating the output directory: the path "
		   << directory
		   << " could not be created. Reason: "
		   << errno << "." << endl;
	exit(1);
      }
    }
    
  vector<complex<double>(*)(const int, const int,
			    const Viewport<int>&,
			    const Viewport<double>&,
			    const complex<double>)> projections;

  projections.push_back(&linear_projection);

  unsigned long const hardware_threads = std::thread::hardware_concurrency();

  unsigned long const num_threads = std::max(hardware_threads, (unsigned long)2);
  if(hardware_threads>0) {
    LOG(INFO) << "Detected " << hardware_threads
	      << " hardware threads. Using a maximum of "
	      << num_threads << " threads." << endl;
  }
  else {
    LOG(INFO) << "Could not detect the number of available hardware threads."
	      << " Using a maximum of "
	      << num_threads << " threads." << endl;
  }
  
  int i {0};

  auto start_time = std::chrono::high_resolution_clock::now();
  
  while(i < number_pics) {
    unsigned long num_useful_threads = std::min((unsigned long)number_pics - i, num_threads);

    
    vector<std::thread> threads;
    unsigned long j;
    for(j = 0; j < num_useful_threads; ++j) {
      double step = space.size()/zoom_step;
      double move = step;

      if(i == 0) {
	step = move = 0;
      }

      std::string filename {directory + "/" + filename_base};

      if(i < 10) {
	filename = filename + "00";
      } else if (i < 100) {
	filename = filename + "0";
      }
    
      filename = filename + std::to_string(i) + std::string(".png");
    
      space = Viewport<double>(space.get_x_min() + step + move,
			       space.get_x_max() - step,
			       space.get_y_min() + step,
			       space.get_y_max() - step - move);

      complex<double> k(julia_kr, julia_ki);

      threads.push_back(std::thread(calculate_and_write,
				    std::ref(algorithm),
				    std::ref(filename),
				    std::ref(screen),
				    std::ref(space),
				    std::ref(iterations),
				    std::ref(projections),
				    std::ref(k)));
      ++i;
    } // for j

    std::for_each(threads.begin(), threads.end(),
		  std::mem_fn(&std::thread::join));

  } //for i

  auto finish_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish_time - start_time;

  LOG(INFO) << "Time elapsed: " << elapsed.count()
       << " seconds (" << number_pics << " pictures total, "
       << elapsed.count() / number_pics << " seconds/picture)."
       << endl;
    
  return 0;
}
