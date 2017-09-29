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
          if(parameters_map.find(label) == parameters_map.end()) {
            vector<double> params = {0,0,0,0,0};
            parameters_map[label] = params;
          }
          double x_center = center_map[label][1];
          double y_center = center_map[label][2];
          double x_prime = col - x_center;
          double y_prime = row - y_center;
          double a = pow(x_prime,2); //x'^2
          double c = pow(y_prime,2); //y`^2
          double b = 2 * x_prime * y_prime; //2 * x` * y`
          parameters_map[label][0] += a;
          parameters_map[label][1] += b;
          parameters_map[label][2] += c;
        }
      }
    }
    
    //calculate theta and rho and draw line
    for(auto it = parameters_map.begin(); it != parameters_map.end(); ++it) {
      int label = it->first;
      double x_center = center_map[label][1];
      double y_center = center_map[label][2];
      double a = parameters_map[label][0];
      double b = parameters_map[label][1];
      double c = parameters_map[label][2];
      cout << "Label: " << label << endl;
      cout << "Params: " << a << ", " << b << ", " << c << endl;
      double tan_theta = atan2(b,a-c)/2;
      cout << "Theta: " << tan_theta << endl;
      double rho = -1*((x_center*sin(tan_theta))-(y_center*cos(tan_theta)));
      cout << "Rho: " << rho << endl;

      //double cos_theta = acos(b,a-c)/2;
      //double sin_theta = asin(b,a-c)/2;
      
      double inter = (a*pow(sin(tan_theta),2)) - (b*sin(tan_theta)*cos(tan_theta)) + (c*pow(cos(tan_theta),2));
      cout << "Inertia " << inter << endl;

      parameters_map[label][3] = tan_theta;

      double x1 = x_center+100;
      double y1 = ((x1*sin(tan_theta))+rho)/cos(tan_theta);
      //double x1 = x_center + (200*sin(tan_theta));
      //double y1 = y_center + (200*cos(tan_theta));
      cout << "Center    : {" << x_center << ", " << y_center << ")" << endl; 
      cout << "New coords: (" << x1 << ", " << y1 << ")" <<  endl;
      DrawLine(size_t(y_center),size_t(x_center),size_t(y1),size_t(x1),255,out_image);
      cout << endl;
    }
    
  }
}
