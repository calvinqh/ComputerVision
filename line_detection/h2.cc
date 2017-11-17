/*
* Program takes the input edge image file name, threshold for edges, and output edge image file name.
* Creates a output edge image that thresholds the input edge image. It's intention is to remove "weak" edges caused by noise.
* The resulting image is a binary edge image
* Code is from previous assignment (for creating binary images)
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
    printf("Usage: %s file1 threshold file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[3]);
  const size_t threshold = atoi(argv[2]);

  Image edge_image;
  Image clean_edge_image;
  if (!ReadImage(input_file, &edge_image)) {
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  CleanEdgeImage(&edge_image, threshold, &clean_edge_image);

  if (!WriteImage(output_file, clean_edge_image)) {
    cout << "Can't write to file " << output_file << endl;
  }
  return 0;
}
