#ifndef PROGRAMS_H_
#define PROGRAMS_H_

#include "image.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace ComputerVisionProjects;

namespace Programs {
  //Creates a binary image given the threshold at which a pixel is considered white.
  //@param an_image: the image that the binary image is based on
  //@param out_image: where the binary image is stored
  //@param threshold: between 0 and 255, level at which pixels are either white or black
  void CreateBinaryImage(Image *an_image, Image *out_image, size_t threshold);
  
  //Created a labeled image given a binary image. Labels are the gray values
  //@param binary_image: a binary image
  //@param out_image: where the labaled image will be stored
  void CreateLabeledImage(Image *binary_image, Image *out_image);

  //Returns the attributes of each object in the image given a labeled image. Will add the info to database only if it is given. 
  //Image will also be saved if it is not null
  //@param label_image: the image which the objects we are trying to compute the attributes for
  //@param database: when given empty string, no database file will be written. Else data is stored in the format:
  //                 { label, x center, y center, rho, inertia, orientation, roundness }
  //@param out_image: where the attribute image is saved. If it is null, then no image is saved
  std::vector<std::vector<double>> ComputeAttributes(Image *label_image, std::string database, Image *out_image);

  //Label objects in the given input image that have been identified
  //@param input_image: the image that the classifcation will act on.
  //@param database: the database of objects to be used for classification
  //@param out_image: the image where classified objects will be.
  void ClassifyInstances(Image *input_image, std::string database, Image *out_image); 

} //namespace Programs

#endif // PROGRAMS_H_
