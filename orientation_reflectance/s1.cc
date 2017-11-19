/*
* Computes the radius and center of the sphere in the image
* This prorgram assumes orthographic projection, this means sphere are projected as circles
* The results of the spheres radius and center will be stored in the parameter file
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
  if (argc != 4) {
    printf("Usage: %s input_image threshold parameter_file\n", argv[0]);
    return 0;
  }

  const string input_file(argv[1]);
  const size_t threshold = atoi(argv[2]);
  const string output_file(argv[3]);

  Image an_image;
  Image edge_image;

  if (!ReadImage(input_file, &an_image)) {
  	cout << "Can't open file " << input_file << endl;
  	return 0;
  }


  Image binary_image;
  GenerateBinaryImage(&an_image,&binary_image,threshold);
  vector<int> sphere_attributes = FindCenterAndRadius(&binary_image);

  //write sphere attributes onto parameter file.
  //saving the hough space into database file
  FILE* output = fopen(output_file.c_str(), "w");
  if(output==0 && output_file.compare("") != 0) {
    cout << "Can't open voting file" << endl;
  }
  for(int i = 0; i < sphere_attributes.size(); i++) {
    string line = "";
    line += to_string(sphere_attributes[i]) + "\n";
    fprintf(output,line.c_str());
  }
  if(output!=0) fclose(output);
  
}