#ifndef PROGRAMS_H_
#define PROGRAMS_H_

#include "image.h"
#include <cstdlib>
#include <string>

using namespace ComputerVisionProjects;

namespace Programs {
  void createBinaryImage(Image *an_image, Image *out_image, size_t threshold);
  void pz();
} //namespace Programs

#endif // PROGRAMS_H_
