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
#include "matrix_functions.h"

using namespace std;
using namespace Matrix;

namespace Programs {

  double mapValue(double value, double start, double end) {
    return value;
  }

  void ComputeSurfaceAlbedo(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int threshold, Image* out_image ) {

    //Copy image1 into outImage
    out_image->AllocateSpaceAndSetSize(image1->num_rows(), image1->num_columns());
    out_image->SetNumberGrayLevels(image1->num_gray_levels());
    for(int i = 0; i < out_image->num_rows(); i++) {
      for(int j = 0; j < out_image->num_columns(); j++) {
        out_image->SetPixel(i,j,image1->GetPixel(i,j));
      }
    }

    vector<vector<double>> source_inverse = inverseMatrix(directions);
        
    //For each step pixel, find the N vector
    for(size_t row = 0; row < out_image->num_rows(); row++) {
      for(size_t col = 0; col < out_image->num_columns(); col++) {
        if(image1->GetPixel(row,col) < threshold || image2->GetPixel(row,col) < threshold || image3->GetPixel(row,col) < threshold) {
          out_image->SetPixel(row,col,0);
          continue;
        }
        vector<int> intensities;
        intensities.push_back(image1->GetPixel(row,col));
        intensities.push_back(image2->GetPixel(row,col));
        intensities.push_back(image3->GetPixel(row,col));
        int counter = 0;

        double size = 0;
        //S^-1 * I
        for(size_t source = 0; source < source_inverse.size(); source++) {
          double total = 0;
          for(size_t component = 0; component < source_inverse[0].size(); component++) {
            total += (source_inverse[source][component]*intensities[counter++]);
          }
          size += pow(total,2);
          counter = 0;
        }

        size = sqrt(size);
        out_image->SetPixel(row,col, 127.1 * size );
      }
    }
  }


}
