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

  Image an_image;
  Image binary_image;
  if (!ReadImage(input_file, &an_image)) {
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  CreateBinaryImage(&an_image, &binary_image, threshold);

  if (!WriteImage(output_file, binary_image)) {
    cout << "Can't write to file " << output_file << endl;
  }
  return 0;
}
