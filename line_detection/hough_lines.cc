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
    //M is the dimension of X
    //N is the dimension of Y
    size_t M = edge_image->num_columns();
    size_t N = edge_image->num_rows();
    double rho_size = sqrt(double(M*M + N*N));
    double theta_size = 1;
    double rho_step = 2;
    double theta_step = .004;
    size_t theta_dimension = size_t(theta_size/theta_step);
    size_t rho_dimension = size_t(rho_size/rho_step);
    out_image->AllocateSpaceAndSetSize(theta_dimension, rho_dimension);
    vector<vector<int>> voting_array;
    for(int i = 0; i < theta_dimension; i++) {
      vector<int> temp;
      for(int j = 0; j < rho_dimension; j++) {
        temp.push_back(0);
      }
      voting_array.push_back(temp);
    }
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
          double temp_rho = (c * sin(temp_theta)) + (r * cos(temp_theta));
          //index j: where j*rho_step is closest to rho calculated
          int j = int(temp_rho/rho_step);
          int curr_val = out_image->GetPixel(i,j);
          if(j < theta_dimension) {
            out_image->SetPixel(i,j,curr_val+1);
            voting_array[i][j]++;
          }
        }
      }
    }
    return voting_array;
  }

  void LineDetection(Image* original_image, vector<vector<int>> voting_array, int threshold, Image* out_image) {
    out_image->AllocateSpaceAndSetSize(original_image->num_rows(), original_image->num_columns());
    out_image->SetNumberGrayLevels(original_image->num_gray_levels());
    cout << "Detecting Lines.." << endl;
    vector<LineParameter> lines;
    double theta_step = .004;
    double rho_step = 2;
    cout << voting_array.size() << " " << voting_array[0].size() << endl;
  	for(int i = 0; i < voting_array.size(); i++) {
      for(int j = 0; j < voting_array[0].size(); j++) {
        if(voting_array[i][j] >= threshold) {
          //We found the theata and rho for a line
          //draw line onto out_image  
          LineParameter line;
          line.theta = (i*theta_step);
          line.rho = (j*rho_step);
          lines.push_back(line);
          double x0,y0;
          x0 = 0;
          y0 = (x0*sin(line.theta)+line.rho)/cos(line.theta);
          double x1,y1;
          x1 = x0 + 100;
          y1 = (x1*sin(line.theta)+line.rho)/cos(line.theta);
          //cout << "(" << x0 << ", " << y0 << ")" << endl;
          //cout << "(" << x1 << ", " << y1 << ")" << endl; 
          cout << line.theta << " " << line.rho << endl;
          size_t x2 = size_t(x0);
          size_t y2 = size_t(y0);
          size_t x3 = size_t(x1);
          size_t y3 = size_t(y1);
          if(y3 > 640 || y2 > 640)
            cout << "----" << endl;
          //DrawLine(y2,x2,y3,x3,100,out_image);
        }
      }
  	}
    cout << "Lines Detected." << endl;
  }

}
