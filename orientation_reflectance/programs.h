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


	


}	//namespace programs


#endif  
