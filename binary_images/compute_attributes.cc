#include "programs.h"
#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <math.h>

using namespace std;

namespace Programs {
  
  void ComputeAttributes(Image *label_image, string database, Image *out_image) {
    out_image->SetNumberGrayLevels(label_image->num_gray_levels());
    
    //maps labels to a list [area, sum of x, sum of y]
    unordered_map<int, vector<double>> center_map;
    vector<int> label_list;

    //find the area and the sum of x's and y's 
    for( size_t row = 0; row < label_image->num_rows(); row++ ) {
      for( size_t col = 0; col < label_image->num_columns(); col++) {
        int label = label_image->GetPixel(row,col);
        if(label != 0) {
          //if key does not exist
          if(center_map.find(label) == center_map.end()){
            vector<double> props = {1,double(col),double(row)};
            center_map[label] = props;
            //label_list.push_back(label);
          }
          else {
            center_map[label][0]++;
            center_map[label][1] += col;
            center_map[label][2] += row;
          }
        }
      }
    }
    /* show areas, sum of x's and sum of y's MAKE SURE U ADD LABEL_LIST PUSHBACK IN CODE BEFORE
    for(int i = 0; i < label_list.size(); i++) { 
      cout << "Label: " << label_list[i] << endl;
      for(int j = 0; j < 3; j++) {
        cout << center_map[label_list[i]][j] << " ";
      }
      cout << endl << "-------" <<  endl;
    }
    */

    //calculate the center
    for(auto it = center_map.begin(); it != center_map.end(); ++it) {
      center_map[it->first][1] /= center_map[it->first][0];
      center_map[it->first][2] /= center_map[it->first][0];
      cout << "Label: " << it->first << endl;
      cout << "Area: " << center_map[it->first][0] << endl;
      cout << "X: " << center_map[it->first][1] << endl;  
      cout << "Y: " << center_map[it->first][2] << endl;  
      cout << "----------------" << endl;
    }
    //maps labels to their a,b,c paramets
    //[a,b,c,theta,rho]
    unordered_map<int,vector<double>> parameters_map;
    for(size_t row = 0; row < label_image->num_rows(); row++){
      for(size_t col = 0; col < label_image->num_columns(); col++){
        int label = label_image->GetPixel(row,col);
        if(label != 0){
          double x_center = center_map[label][1];
          double y_center = center_map[label][2];
          double a = col - x_center;
          double c = row - y_center;
          double b = 2 * a * c;
          a *= a;
          c *= c;
          if(parameters_map.find(label) == parameters_map.end()) {
            //the 4th and 5th hold theta and rho for the instance
            vector<double> params = {a, b, c, 0, 0}; 
            parameters_map[label] = params;             
          }
          parameters_map[label][0] += a;
          parameters_map[label][1] += b;
          parameters_map[label][2] += c;
        }
      }
    }
    
    //calculate theta and rho and draw line
    for(auto it = parameters_map.begin(); it != parameters_map.end(); ++it) {
      int label = it->first;
      long double a = parameters_map[label][0];
      long double  b = parameters_map[label][1];
      long double c = parameters_map[label][2];
      cout << "Params: " << a << ", " << b << ", " << c << endl;
      long double tan_theta = atan2(b,a-c) * .5;
      cout << "Theta using tan: " << tan_theta << endl;
      
      size_t x_center = center_map[label][1];
      size_t y_center = center_map[label][2];
      long double rho = x_center*sin(tan_theta) - y_center*cos(tan_theta);
      cout << "Rho: " << rho << endl; 

      parameters_map[label][3] = tan_theta;
      parameters_map[label][4] = rho;

      cout << sin(tan_theta) << endl;
      double x1 = x_center+1000000;
      double y1 = ((x1*sin(tan_theta))+rho)/cos(tan_theta);
      cout << "Center    : {" << x_center << ", " << y_center << ")" << endl; 
      cout << "New coords: (" << x1 << ", " << y1 << ")" <<  endl;
      DrawLine(size_t(y_center),size_t(x_center),size_t(y1),size_t(x1),255,out_image);
      cout << endl;
    }
    
  }
}
