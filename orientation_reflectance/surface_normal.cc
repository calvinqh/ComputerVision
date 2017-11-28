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
#include "matrix_functions.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;
using namespace Matrix;

namespace Programs {
  
  //Draws a white square with black center
  void createBlackPoint(Image* an_image, int row, int col) {
    for(int i = -1; i < 2; i++) {
      for(int j = -1; j < 2; j++) {
        if(i == 0 && i == 0 && j == 0 && j == 0)
          an_image->SetPixel(row+i,col+j,0);
        else
          an_image->SetPixel(row+i,col+j,255);
      }
    }
  }

  void FindSurfaceNormals(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int step, int threshold, Image* out_image) {


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
    for(size_t row = 0+step; row < out_image->num_rows(); row+=step) {
      for(size_t col = 0+step; col < out_image->num_columns(); col+=step) {
        if(image1->GetPixel(row,col) < threshold || image2->GetPixel(row,col) < threshold || image3->GetPixel(row,col) < threshold)
          continue;
        vector<int> intensities;
        intensities.push_back(image1->GetPixel(row,col));
        intensities.push_back(image2->GetPixel(row,col));
        intensities.push_back(image3->GetPixel(row,col));
        int counter = 0;

        vector<double> N; //will contain the components of the normal vector for the pixel
        double size = 0;
        //S^-1 * I, computing normal
        for(size_t source = 0; source < source_inverse.size(); source++) {
          double total = 0;
          for(size_t component = 0; component < source_inverse[0].size(); component++) {
            total += (source_inverse[source][component]*intensities[counter++]);
          }
          N.push_back(total);
          size += pow(total,2);
          counter = 0;
        }

        size = sqrt(size);
        //divde normal vector by lengt
        for(size_t index = 0; index < N.size(); index++) {
          N[index] = N[index]/size;
        }
        //Get points for drawing vector
        vector<int> coords = {0,0}; //x and y coords for the normal vector (col,row)
        coords[0] = col + N[0] * 10;
        coords[1] = row + N[1] * 10;

        DrawLine(row,col, coords[1], coords[0], 255, out_image);
        createBlackPoint(out_image,row,col);
      }

    }
    
  }

}
