/*
* Outputs an albedo map. Computes the albedo visible from all 3 light sources
* ALbedos are scaled down to 0-255
*/
#include "image.h"
#include "programs.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;
using namespace Programs;

int
main(int argc, char **argv) {
  if (argc != 7) {
    printf("Usage: %s input image1 image2 image3 threshold output\n", argv[0]);
    return 0;
  }

  const string directions_file(argv[1]);
  const string image1(argv[2]);
  const string image2(argv[3]);
  const string image3(argv[4]);
  const size_t threshold = atoi(argv[5]);
  const string output_file(argv[6]);

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

  //will contain image with surface albedo
  Image out_image;
  ComputeSurfaceAlbedo(directions, &an_image1, &an_image2, &an_image3, threshold, &out_image);

  if (!WriteImage(output_file, &out_image)) {
    cout << "Can't write to " << output_file << endl;
  }
  
}