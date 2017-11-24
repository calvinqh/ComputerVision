/*
* Contains implementation of:
*	
*		vector<int> FindLightSourceVector(Image*,size_t,size_t)
*
*
*
*/
#include "programs.h"
#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

namespace Programs {

  vector<int> FindLightSourceVector(Image* an_image, size_t centerX, size_t centerY, size_t radius) {
    vector<int> light_source;

    //find the brightest pixel location
    size_t maxBrightness = 0;
    //maxR is the Y position
    size_t maxR = 0;
    //maxC is the X position
    size_t maxC = 0;
    for(size_t i = 0; i < an_image->num_rows(); i++) {
    	for(size_t j = 0; j < an_image->num_columns(); j++) {
    		int pixel = an_image->GetPixel(i,j);
    		if(pixel > maxBrightness) {
    			maxBrightness = pixel;
    			maxR = i;
    			maxC = j;
    		}
    	}
    }

    //Calculate the light source vector
    //which is the normal of the brightest pixel
    //FIX: the order of center and max!!!!!!!!!
    double deltaX = centerX-maxC;
    double deltaY = centerY-maxR;
    light_source.push_back(deltaX);
    light_source.push_back(deltaY);

    //calculate the Z component of normal vector
    size_t z_comp = 0;
    //R^2 - (X-Xc)^2 - (Y-Yc)^2
    z_comp = sqrt(pow(radius,2)-pow(deltaX,2)-pow(deltaY,2));
    light_source.push_back(z_comp);

    //Draw the vector onto the image?
    //first make a copy, then draw onto the copy!
    string output_file = "sample1.pgm";

    return light_source;  
  }


}
