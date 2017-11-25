/*
* Contains implementation of:
*	
*		void ComputeSurfaceAlbedo(vector<vector<int>>, Image*, Image*, Image*, int, Image*)
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

  void ComputeSurfaceAlbedo(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int threshold, Image* out_image ) {
    /*
    * Check slide 19!!
    * Loop, for i = 0 + step to all rows and for j = 0 + step to all columns
    *   For each pixel (within the steps)
    *     Normal vector = Calculate S^-1 (the threee light source vectors) * the three intensities
    */
  }


}
