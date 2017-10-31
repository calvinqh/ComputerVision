#ifndef _PROGRAMS_H_
#define _PROGRAMS_H_

#include "image.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;


namespace Programs {

  //Performs convolution with the given mask onto an_image. The result is saved into out_image
  //@param mask: a mxm mask that will be applied to an_image
  //@param an_image: the image the mask will be applied to
  //@param out_image: where the result of the convolution is saved.
  void convolve(Image* mask, Image* an_image, Image* out_image);


  //Creates a edge strength image using sobel operator
  //@param an_image: gray image where the sobel operator will be applied to
  //@param strength_image: the edge image (with gray level correlating to the strength)
  void GenerateEdgeStrengthImage(Image* an_image, Image* strength_image);

  //Thresholds the edge "strength" image, removes all weak edges. The result is a binary edge image
  //@param edge_image: the edge strength image that the result is based off
  //@param threshold: gray level value that determines if pixel is an edge or not
  //@param out_image: the applied threshold image for edge image, results in a binary edge image
  void CleanEdgeImage(Image* edge_image, int threshold Image* out_image);
  

  //Creates the line hough space for the edge "strength" image provided
  //@param edge_image: binary edge image
  //@param out_image: saves the hough voting image produces from the edge image
  //@return: the 2d array for the voting space. rows are for theta, cols are for rho
  vector<vector<int>> GenerateHoughSpace(Image* edge_image, Image* out_image);

  //Draws Lines on the original image
  //@param original_image: the original gray level image
  //@param voting array: array containing the line votes from hough. array is indexed by [theta, rho]
  //@param threshold: the threshold on which votes in the voting array are considered lines
  //@param out_image: contains lines drawn onto original image 
  void LineDetection(Image* original_image, vector<vector<int>> voting_array, int threshold, Image* out_image);

}	//namespace programs


#endif  