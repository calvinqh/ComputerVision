#ifndef _PROGRAMS_H_
#define _PROGRAMS_H_

#include "image.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;


namespace Programs {


	//Create a binary image based off the threshold given
	//@param an_image, the image that will be converted to a binary image
	//@param threshold, the threshold in which a pixel will be considered apart of the object
	//@param out_image, where the output binary image will be saved
	void GenerateBinaryImage(Image* an_image, Image* out_image, int threshold);

	//Finds the center and radius of the sphere from the given binary image
	//@param binary_image, binary image of a sphere
	//@return, vector of cetner and radius for given sphere binary image
	//i.e, center X, center Y, radius
	vector<int> FindCenterAndRadius(Image* binary_image);


  //Finds the x,y,z compnent of the light source vector for the given image
  //@param an_image, an image with one light source
  //@return, vector of x,y,z component of light source.
	vector<int> FindLightSourceVector(Image* an_image, int centerX, int centerY, int radius);

  //Finds the surface normals and applies it to image1
  //@param directions, a vector containing light source directions for each of the three images. contains X,Y,Z component
  //@param image1, an image with light source parameters at directions[0]
  //@param image2, an image with light source parameters at directions[1]
  //@param image3, an image with light source parameters at directions[2]
  //@param step, the distance between grid points  on which vectors will be drawn on
  //@param threshold, what would be considered as a surface
  //@param out_image, surface normals are drawn onto image1
  void FindSurfaceNormals(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int step, int threshold, Image* out_image);




}	//namespace programs


#endif  
