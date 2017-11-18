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

using namespace std;
using namespace ComputerVisionProjects;
using namespace Programs;

int
main(int argc, char **argv) {
  if (argc != 6) {
    printf("Usage: %s parameter_file image1 image2 image3 directions_file\n", argv[0]);
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