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