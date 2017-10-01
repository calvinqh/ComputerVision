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

  Image binary_image;
  Image labeled_image;
  if (!ReadImage(input_file, &binary_image)) {
    cout << "Can't open file " << input_file << endl;
  }
  
  CreateLabeledImage(&binary_image, &labeled_image);

  if (!WriteImage(output_file, labeled_image)) {
    cout << "Can't write to " << output_file << endl;
  }
  return 0;
}
