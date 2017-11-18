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

using namespace std;
using namespace ComputerVisionProjects;
using namespace Programs;

int
main(int argc, char **argv) {
  if (argc != 8) {
    printf("Usage: %s direction_file image1 image2 image3 step threshold output\n", argv[0]);
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[2]);

  Image an_image;
  Image edge_image;

  if (!ReadImage(input_file, &an_image)) {
  	cout << "Can't open file " << input_file << endl;
  	return 0;
  }

  if (!WriteImage(output_file, edge_image)) {
    cout << "Can't write to " << output_file << endl;
  }
  
}