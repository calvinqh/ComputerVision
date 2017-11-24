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
    for(size_t i = 0; i < an_image->num_rowS(); i++) {
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
    light_source.push_back(centerX-maxC);
    light_source.push_back(centerY-maxR);

    //calculate the Z component of normal vector
    size_t z_comp = 0;
    z_comp = sqrt(1);
    light_source.push_back(0;)

    return light_source;  
  }


}
