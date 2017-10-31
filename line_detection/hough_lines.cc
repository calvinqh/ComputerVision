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

  vector<vector<int>> GenerateHoughSpace(Image* edge_image, Image* out_image) {
    vector<vector<int>> voting_array;
    //M is the dimension of X
    //N is the dimension of Y
    size_t M = edge_image->num_columns();
    size_t N = edge_image->num_rows();
    double rho_size = sqrt(double(M*M + N*N));
    double theta_size = 1;
    double rho_step = .5;
    double theta_step = .001;
    size_t theta_dimension = size_t(theta_size/theta_step);
    size_t rho_dimension = size_t(rho_size/rho_step);
    out_image->AllocateSpaceAndSetSize(theta_dimension, rho_dimension);
    cout << "Theta: " << theta_dimension << endl;
    cout << "Rho: " << rho_dimension << endl;
    out_image->SetNumberGrayLevels(edge_image->num_gray_levels());
   
    for(int r = 0; r < edge_image->num_rows(); r++) {
      for(int c = 0; c < edge_image->num_columns(); c++) {
        size_t value = edge_image->GetPixel(r,c);
        if(value == 0) 
          continue;
        for(int i = 0; i < theta_dimension; i++) {
          double temp_theta = theta_step * i;
          double temp_rho = (r * sin(temp_theta)) + (c * cos(temp_theta));
          //index j: where j*rho_step is closest to rho calculated
          int j = int(temp_rho/rho_step);
          out_image->SetPixel(i,j,out_image->GetPixel(i,j)+1);
        }
      }
    }
    return voting_array;
  }

  void LineDetection(Image* original_image, vector<vector<int>> voting_array, int threshold, Image* out_image) {
    out_image->AllocateSpaceAndSetSize(original_image->num_rows(), original_image->num_columns());
    out_image->SetNumberGrayLevels(original_image->num_gray_levels());

    vector<LineParameter> lines;
  	for(int i = 0; i < voting_array.size(); i++) {
      for(int j = 0; j < voting_array[0].size(); i++) {
        if(voting_array[i][j] >= threshold) {
          //We found the theata and rho for a line
          //draw line onto out_image  
          LineParameter line;
          line.theta = i;
          line.rho = j;
          lines.push_back(line);
          size_t x0,y0;
          x0 = 0;
          y0 = (x0*sin(line.theta)+line.rho)/cos(line.theta);
          size_t x1,y1;
          x1 = x0 + 100;
          y1 = (x1*sin(line.theta)+line.rho)/cos(line.theta);
          DrawLine(y0,x0,y1,x1,100,out_image);
        }
      }
  	}
  }

}
