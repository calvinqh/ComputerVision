/*
* Computes the direction and intensities of the light sources from each image.
* Finds the normal vector from the brightest surface spot on the sphere for the three images
* For the intensity of the light source, use the magnitude (brightness) of the brightest
* pixel found in the corresponding image. Scale the direction vector so that its length equals
* this value.
*
* This program results in a directions file that contains the x,y,z components of the vector for the three light sourcs
* 
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
  if (argc != 6) {
    printf("Usage: %s parameter_file image1 image2 image3 directions_file\n", argv[0]);
    return 0;
  }

  const string parameter_file(argv[1]);
  const string image1(argv[2]);
  const string image2(argv[3]);
  const string image3(argv[4]);
  const string directions_file(argv[5]);
  
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
  vector<int> parameters;
  ifstream file(parameter_file);
  string str;

  while(getline(file,str)){
    parameters.push_back(stoi(str));
    cout << parameters.back() << endl;
  }
  
}