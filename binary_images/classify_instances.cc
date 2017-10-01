#include "programs.h"
#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

namespace Programs {

  void ClassifyInstances(Image *input_image, string database, Image *out_image) {
    cout << "Classifying Image..." << endl;
  
    //Map labels to instances features from the databse
    // {label, x center, y center, inertia, orientation, roundness}
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
      instance_matrix.push_back(features);
      start = 0;
    }
    /*
    //print out instance matrix
    for(int i = 0; i < instance_matrix.size(); i++) {
      for(int j = 0; j < instance_matrix[0].size(); j++) {
        cout << instance_matrix[i][j] << endl;
      }
    }
    */
    
    //Compute Attributes for the current given image
    Image out_t;
    vector<vector<double>> t = ComputeAttributes(input_image, "sss", &out_t);
    }
  }
}
