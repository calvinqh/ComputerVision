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

  template<typename T>
  void printMatrix(vector<vector<T>> &matrix) {
      for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
          cout << matrix[i][j] << " ";
        }
        cout << endl;
      }
  }

  double get3x3Determinant(vector<vector<int>> &matrix, vector<vector<int>> &minors_matrix) {
    int sign = 1;
    double accumulator = 0;
    for(int i = 0; i < minors_matrix.size(); i++) {
      accumulator += (sign* matrix[0][i] * minors_matrix[0][i]);
      cout << matrix[0][i] << " ";
      cout << minors_matrix[0][i] << endl;
      sign *= -1;
    }
    
    return accumulator;
  }

  int get2x2Determinant(vector<vector<int>> &matrix, int rStart, int rEnd, int cStart, int cEnd) {
    int a = matrix[rStart][cStart];
    int b = matrix[rStart][cEnd];
    int c = matrix[rEnd][cStart];
    int d = matrix[rEnd][cEnd];
    return (a*d - b*c);
  }

  void flippyflip(vector<vector<int>>& matrix) {
    for(int i = 0; i < matrix.size(); i++) {
      for(int j = 0; j < matrix[0].size(); j++) {
        if(i >= j)
          continue;
        int temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp;
      }
    }
  }

  void adjugate(vector<vector<int>> &matrix) {
    flippyflip(matrix);
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
    cout << "-------Minors--------" << endl;
    printMatrix(matrix_of_minors);
    cout << "--------------------" << endl;

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

  vector<vector<double>> inverseMatrix(vector<vector<int>> &matrix) {
    
    vector<vector<int>> matrix_of_minors = getMatrixOfMinors(matrix);
    double determinant = get3x3Determinant(matrix,matrix_of_minors);
    cout << determinant << endl;
    vector<vector<int>> cofactors = getMatrixCoFactors(matrix_of_minors);
    adjugate(cofactors);
    vector<vector<double>> inverse;
    for(int i = 0; i < cofactors.size(); i++) {
      vector<double> row;
      for(int j = 0; j < cofactors[0].size(); j++) {
        double value = cofactors[i][j] * (1/determinant);
        row.push_back(value);
      }
      inverse.push_back(row);
    }

    cout << "------Adjugated Cofactor------" << endl;
    printMatrix(cofactors);
    cout << "------Inverse--------" << endl;
    printMatrix(inverse);
    cout << "-------------" << endl;
    return inverse;

  }

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

    cout << "-------------" << endl;
    cout << "Directions" << endl;
    printMatrix(directions);
    cout << "-------------" << endl;

    //Copy image1 into outImage
    out_image->AllocateSpaceAndSetSize(image1->num_rows(), image1->num_columns());
    out_image->SetNumberGrayLevels(image1->num_gray_levels());
    for(int i = 0; i < out_image->num_rows(); i++) {
      for(int j = 0; j < out_image->num_columns(); j++) {
        out_image->SetPixel(i,j,image1->GetPixel(i,j));
      }
    }

    vector<vector<double>> source_inverse = inverseMatrix(directions);
    
    cout << "Line 124" << endl;
    
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
        //S^-1 * I
        for(size_t source = 0; source < source_inverse.size(); source++) {
          double total = 0;
          for(size_t component = 0; component < source_inverse[0].size(); component++) {
            total += (source_inverse[source][component]*intensities[counter++]);
          }
          cout << source << " Total :" << total << endl;
          N.push_back(total);
          size += pow(total,2);
          counter = 0;
        }

        size = sqrt(size);
        cout << "Size: " <<  size << endl;
        //compute the normal  and draw
        vector<int> coords = {0,0}; //x and y coords for the normal vector (col,row)
        for(size_t index = 0; index < N.size(); index++) {
          N[index] = N[index]/size;
          cout << N[index] << endl;
        }

        coords[0] = col + N[0] * 10;
        coords[1] = row + N[1] * 10;

        DrawLine(row,col, coords[1], coords[0], 255, out_image);
        cout << row << ", " << col << endl;
        cout << coords[0] << ", " << coords[1] << endl;
        cout << N[0] << ", " << N[1] << endl;
        createBlackPoint(out_image,row,col);
      }

    }
    
  }

}
