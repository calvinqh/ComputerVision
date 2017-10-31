/*
* Program takes an input image file name and output image file name.
* It will create a edge strength image from the input image.
* This program uses the sobel operator to generate the edge strength image
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
  if (argc != 3) {
    printf("Usage: %s file1 file2\n", argv[0]);
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

  GenerateEdgeStrengthImage(an_image, edge_image);

  if (!WriteImage(output_file, edge_image)) {
    cout << "Can't write to " << output_file << endl;
  }
  
}