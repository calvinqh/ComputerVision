/*
* Contains implementation of:
*	
*		 void FindSurfaceNormals(vector<vector<int>>, Image*, Image*, Image*, int, int, Image*)
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

  void FindSurfaceNormals(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int step, int threshold, Image* out_image) {
    /*
    * Check slide 19!!
    * Loop, for i = 0 + step to all rows and for j = 0 + step to all columns
    *   For each pixel (within the steps)
    *     Normal vector = Calculate S^-1 (the threee light source vectors) * the three intensities
    */
  }

}
