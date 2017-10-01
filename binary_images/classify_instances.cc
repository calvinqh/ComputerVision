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

  void ClassifyInstances(Image *input_image, string database, Image *out_image) {
    cout << "Classifying Image..." << endl;
    //Make copy of input to out image
    out_image->AllocateSpaceAndSetSize(input_image->num_rows(), input_image->num_columns());
    out_image->SetNumberGrayLevels(input_image->num_gray_levels());
    for(size_t i = 0; i < input_image->num_rows(); i++) {
      for(size_t j = 0; j < input_image->num_columns(); j++) {
        out_image->SetPixel(i,j,input_image->GetPixel(i,j));
      }
    }
    
    //contains all instances from the database
    // {label, x center, y center, inertia, orientation, roundness}
    vector<vector<double>> database_matrix;
    //contains all objects and their featues from the input image.
    vector<vector<double>> instance_matrix;

    //open and read database
    ifstream file(database);
    string str;
    getline(file,str); //skip the first line

    //read database information
    int start = 0;
    int end = 0;
    while(getline(file,str)){
      vector<double> features;
      for(int i = 0; i < str.length(); i++) {
        if(str[i] == ' ') {
          string data = str.substr(start, i);
          start = i+1;
          features.push_back(stod(data));
        }
      }
      database_matrix.push_back(features);
      start = 0;
    }
    
    
    //Compute Attributes for the current given image
    Image out_t;
    instance_matrix = ComputeAttributes(input_image, "", nullptr);
    cout << "Making Comparisons ..." << endl;
    //recognized, marks which objects have been classified
    vector<bool> recognized;
    double error_threshold = .2;
    for(size_t i = 0; i < instance_matrix.size(); i++) {
      //compare to all database instances
      //min_percent_diff set to n*1.0. 
      //where n is the number of attributes being compared
      double min_percent_diff = database_matrix[0].size()-4;
      for(size_t j = 0; j < database_matrix.size(); j++) {
        //compare the attribute: inertia, orientation, roundness
        double total_percent_diff = 0;
        for(size_t k = 4; k < database_matrix[0].size(); k++) {
          double instance_attr = instance_matrix[i][k];
          double data_attr = database_matrix[j][k];
          double difference = instance_attr-data_attr;
          double percent_diff = abs(difference/data_attr);
          if(percent_diff < error_threshold) {
            total_percent_diff += percent_diff;
          }
          else {
            //difference between attribute too large
            k = database_matrix[0].size();
          }
        }
        //check for non-zero b/c test may fail early b/c one attribute has too large of a difference (difference default =0)
        if (total_percent_diff < min_percent_diff && total_percent_diff != 0) {
          min_percent_diff = total_percent_diff;
        }
      }
      double avg_min_diff = min_percent_diff/(database_matrix[0].size()-4);
      cout << avg_min_diff << endl;
      //check for non-zero b/c comparison test may fail early b/c one atttribute too large of difference(difference default =0)
      bool res = (avg_min_diff < error_threshold) && (avg_min_diff != 0);
      recognized.push_back(res);
    }
    cout << "Classifying ..." << endl;
    for(size_t i = 0; i < recognized.size(); i++) {
      if(recognized[i]) {
        //get new (x,y)
        double x_center = instance_matrix[i][1];
        double y_center = instance_matrix[i][2];
        double rho = instance_matrix[i][3];
        double theta = instance_matrix[i][5];
        if(theta < 0)
          theta = (-1*theta) - (3.14159/2);
        else
          theta = (3.14159/2) - theta;
        double x1 = x_center + 100;
        double y1 = ((x1*sin(theta))+rho)/cos(theta);
        DrawLine(size_t(y_center), size_t(x_center), size_t(y1), size_t(x1), 255, out_image);
      }
    }
    cout << "Classifcation Complete!" << endl;
  }
}
