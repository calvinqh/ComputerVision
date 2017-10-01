#ifndef PROGRAMS_H_
#define PROGRAMS_H_

#include "image.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace ComputerVisionProjects;

namespace Programs {
  void CreateBinaryImage(Image *an_image, Image *out_image, size_t threshold);
  
  void CreateLabeledImage(Image *binary_image, Image *out_image);

  std::vector<std::vector<double>> ComputeAttributes(Image *label_image, std::string database, Image *out_image);

  void ClassifyInstances(Image *input_image, std::string database, Image *out_image); 
} //namespace Programs

#endif // PROGRAMS_H_
