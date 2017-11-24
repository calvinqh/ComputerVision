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

  vector<int> FindLightSourceVector(Image* an_image) {
    vector<int> light_source;

    size_t maxBrightness = 0;
    size_t maxR = 0, maxC = 0;
    //find the brightest pixel
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


    return light_source;  
  }


}
