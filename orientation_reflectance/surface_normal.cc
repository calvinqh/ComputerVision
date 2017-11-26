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

  int get2x2Determinant(vector<vector<int>> &matrix, int rStart, int rEnd, int cStart, int cEnd) {
    int a = matrix[rStart][cStart];
    int b = matrix[rStart][cEnd];
    int c = matrix[rEnd][cStart];
    int d = matrix[rEnd][cEnd];
    return (a*d - b*c);
  }

  vector<vector<int>> getMatrixOfMinors(vector<vector<int>> &matrix) {
    vector<vector<int>> matrix_of_minors;
    for(int i = 0; i < matrix.size(); i++) {
      vector<int> row;
      for(int j = 0; j < matrix[0].size(); j++) {
        int rowStart = 0, rowEnd = 1;
        int colStart = 0, colEnd = 1;
        if(i == 0) {
          rowStart = i+1;
          rowEnd = i+2;
        }
        else if(i == 1) {
          rowStart = i-1;
          rowEnd = i+1;
        }
        if(j == 0) {
          colStart = j+1;
          colEnd = j+2;
        }
        else if(j == 1) {
          colStart = j-1;
          colEnd = j+1;
        }
        row.push_back(get2x2Determinant(matrix,rowStart,rowEnd,colStart,colEnd));
      }
      matrix_of_minors.push_back(row);
    }
    return matrix_of_minors;
  }

  vector<vector<int>> getMatrixCoFactors(vector<vector<int>> &matrix) {
    vector<vector<int>> cofactors;
    int sign = 1;
    for(int i = 0; i < matrix.size(); i++) {
      vector<int> row;
      for(int j = 0; j < matrix[0].size(); j++) {
        row.push_back(sign*matrix[i][j]);
        sign *= -1;
      }
      cofactors.push_back(row);
    }
    return cofactors;
  }

  vector<vector<int>> inverseMatrix(vector<vector<int>> &matrix) {
    int determinant = get3x3Determinant(matrix);
    cout << determinant << " Line 103" << endl;
    
    vector<vector<int>> matrix_of_minors = getMatrixOfMinors(matrix);
    /*
    vector<vector<int>> cofactors = getMatrixCoFactors(matrix_of_minors);
    vector<vector<int>> inverse;
    for(int i = 0; i < cofactors.size(); i++) {
      vector<int> row;
      for(int j = 0; j < cofactors[0].size(); j++) {
        row.push_back(cofactors[i][j] * (1/double(determinant)));
      }
      inverse.push_back(row);
    }
    printMatrix(matrix);
    return inverse;
    */
    vector<vector<int>> result;
    return result;
  }

  void FindSurfaceNormals(vector<vector<int>> directions, Image* image1, Image* image2, Image* image3, int step, int threshold, Image* out_image) {

    //Copy image1 into outImage
    out_image->AllocateSpaceAndSetSize(image1->num_rows(), image1->num_columns());
    out_image->SetNumberGrayLevels(image1->num_gray_levels());

    vector<vector<int>> source_inverse = inverseMatrix(directions);
    cout << "Line 124" << endl;
    /*
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
        for(size_t source = 0; source < source_inverse.size(); source++) {
          int total = 0;
          for(size_t component = 0; component < source_inverse[0].size(); component++) {
            total += (source_inverse[source][component]*intensities[counter++]);
          }
          N.push_back(total);
          size += pow(total,2);
          counter = 0;
        }
        size = sqrt(size);
        //compute the normal  and draw
        vector<int> coords = {0,0}; //x and y coords for the normal vector (col,row)
        for(size_t index = 0; index < N.size(); index++) {
          N[index] = N[index]/size;
        }
        coords[0] = col + N[0] * 10;
        coords[1] = row + N[1] * 10;
        DrawLine(row,col, coords[1], coords[0], 255, out_image);
      }

    }
    */
  }

}
