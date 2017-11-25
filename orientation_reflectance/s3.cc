/*
* Computes the surface normals of the object
* directions file, contains the vector componenets for the three light sources for the three images
* output, contains the needle map of the surface normals
* This program will only draw the surface normals if their brightness is above the threshold
* The normal will not be drawn for all pixels, the pixels chosen are based on the pixel step size.
*/
#include "image.h"
#include "programs.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;
using namespace Programs;

int
main(int argc, char **argv) {
  if (argc != 8) {
    printf("Usage: %s direction_file image1 image2 image3 step threshold output\n", argv[0]);
    return 0;
  }

  const string directions_file(argv[1]);
  const string image1(argv[2]);
  const string image2(argv[3]);
  const string image3(argv[4]);
  const size_t step = atoi(argv[5]);
  const size_t threshold = atoi(argv[6]);
  const string output_file(argv[7]);

  Image an_image1;
  Image an_image2;
  Image an_image3;

  //Load the image files
  if (!ReadImage(image1, &an_image1)) {
    cout << "Can't open file " << image1 << endl;
    return 0;
  }
  if (!ReadImage(image2, &an_image2)) {
    cout << "Can't open file " << image2 << endl;
    return 0;
  }
  if (!ReadImage(image3, &an_image3)) {
    cout << "Can't open file " << image3 << endl;
    return 0;
  }

  //read parameter file
  vector<vector<int>> directions;
  ifstream file(directions_file);
  string str;
  int start = 0;
  while(getline(file,str)) {
    vector<int> source;
    for(int i = 0; i < str.length(); i++) {
      if(str[i] == ' ') {
        string data = str.substr(start, i);
        start = i + 1;
        source.push_back(stoi(data));
      }
    }
    directions.push_back(source);
    start = 0;
  }

  //will contain image with surface normals drawn on
  Image out_image;
  FindSurfaceNormals(directions, &an_image1, &an_image2, &an_image3, step, threshold, &out_image);

  if (!WriteImage(output_file, out_image)) {
    cout << "Can't write to " << output_file << endl;
  }
  
}