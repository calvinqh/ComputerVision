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

  void printMatrix(vector<vector<int>> &matrix) {
      for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
          cout << matrix[i][j] << " ";
        }
        cout << endl;
      }
  }

  int get3x3Determinant(vector<vector<int>> &matrix) {
    int accumulator = 0;
    int a = matrix[0][0];
    int b = matrix[0][1];
    int c = matrix[0][2];
    int d = matrix[1][0];
    int e = matrix[1][1];
    int f = matrix[1][2];
    int g = matrix[2][0];
    int h = matrix[2][1];
    int i = matrix[2][2];
    accumulator = a * (e*i + (-1*f*h));
    accumulator = accumulator - (b * (d*i + (-1*f*g)));
    accumulator = accumulator - (c *(d*h + (-1*e*g)));
    
    return accumulator;
  }

  void inverseMatrix(vector<vector<int>> &matrix) {
    int determinant = get3x3Determinant(matrix);
    for(int i = 0; i < matrix.size(); i++) {
      for(int j = 0; j < matrix[0].size(); j++) {
        matrix[i][j] = 0;
      }
    }
    printMatrix(matrix);
  }

  void FindSurfaceNormals(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int step, int threshold, Image* out_image) {

    //Copy image1 into outImage
    out_image->AllocateSpaceAndSetSize(image1->num_rows(), image1->num_columns());
    out_image->SetNumberGrayLevels(image1->num_gray_levels());


    //For each step pixel, find the N vector
    for(size_t row = 0+step; row < out_image->num_rows(); row+=step) {
      for(size_t col = 0+step; col < out_image->num_columns(); col+=step) {
        vector<int> intensities;
        intensities.push_back(image1->GetPixel(row,col));
        intensities.push_back(image2->GetPixel(row,col));
        intensities.push_back(image3->GetPixel(row,col));
        int counter = 0;

        vector<double> N; //will contain the components of the normal vector for the pixel
        double size = 0;
        for(size_t source = 0; source < directions.size(); source++) {
          int total = 0;
          for(size_t component = 0; component < directions[0].size(); component++) {
            total += (directions[source][component]*intensities[counter++]);
          }
          //TODO: save total into N vector for that pixel
          N.push_back(total);
          size += pow(total,2);
          counter = 0;
        }
        size = sqrt(size);
        //compute the normal and draw
        for(size_t index = 0; index < N.size(); index++) {
          N[index] = N[index]/size;

        }
      }

    }
    /*
    * Check slide 19!!
    * Loop, for i = 0 + step to all rows and for j = 0 + step to all columns
    *   For each pixel (within the steps)
    *     Normal vector = Calculate S^-1 (the threee light source vectors) * the three intensities
    */
  }

}
