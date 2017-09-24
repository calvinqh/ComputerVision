#ifndef PROGRAMS_H_
#define PROGRAMS_H_

#include "image.h"
#include <cstdlib>
#include <string>

using namespace ComputerVisionProjects;

namespace Programs {
  void CreateBinaryImage(Image *an_image, Image *out_image, size_t threshold);
  
  void CreateLabeledImage(Image *binary_image, Image *out_image);

  void ComputerAttributes(Image *labelImage, string database, Image *outImage);

} //namespace Programs

#endif // PROGRAMS_H_
