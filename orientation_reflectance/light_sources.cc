/*
* Contains implementation of:
*	
*		vector<int> FindLightSourceVector(Image*,int,int,int)
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

  double getPartialOfX(int x, int y, int radius) {
    //-x/sqrt(R^2 - X^2 - Y^2)
    double numer = -1 * x;
    double denom = sqrt(pow(radius,2) - pow(x,2) - pow(y,2));
    return numer/denom;
  }
  double getPartialOfY(int x, int y, int radius) {
    //-y/sqrt(R^2 - X^2 - Y^2)
    double numer = -1 * y;
    double denom = sqrt(pow(radius,2) - pow(x,2) - pow(y,2));
    return numer/denom;
  }

  vector<double> FindLightSourceVector(Image* an_image, int centerX, int centerY, int radius) {
    vector<double> light_source;

    //find the brightest pixel location
    size_t maxBrightness = 0;
    //maxR is the Y position
    int maxR = 0;
    //maxC is the X position
    int maxC = 0;
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
    double deltaX = maxC-centerX;
    double deltaY = maxR-centerY;
    double p = -1* getPartialOfX(deltaX,deltaY,radius);
    double q = -1 * getPartialOfY(deltaX,deltaY,radius);
    
    double denominator = sqrt(pow(p,2) + pow(q,2) + 1);
    light_source.push_back(p/denominator*maxBrightness); //scale and divide by length
    light_source.push_back(q/denominator*maxBrightness); //scale and divide by length

    double z_comp = 1;
    light_source.push_back(z_comp*maxBrightness/denominator); //scale and divide by length

    return light_source;  
  }


}
