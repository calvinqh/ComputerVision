#ifndef _MATRIX_FUNCTION_H_
#define _MATRIX_FUNCTION_H_

#include "image.h"
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;
using namespace ComputerVisionProjects;


namespace Matrix {

	template<typename T>
  void printMatrix(vector<vector<T>> &matrix);

  double get3x3Determinant(vector<vector<int>> &matrix, vector<vector<int>> &minors_matrix);

  int get2x2Determinant(vector<vector<int>> &matrix, int rStart, int rEnd, int cStart, int cEnd);

  void flippyflip(vector<vector<int>>& matrix);

  void adjugate(vector<vector<int>> &matrix);

  vector<vector<int>> getMatrixOfMinors(vector<vector<int>> &matrix);

  vector<vector<int>> getMatrixCoFactors(vector<vector<int>> &matrix);

  vector<vector<double>> inverseMatrix(vector<vector<int>> &matrix);

}

#endif