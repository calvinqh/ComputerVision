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
    printf("Usage: %s file1 database file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[3]);
  const string database(argv[2]);

  Image labeled_image;
  Image attribute_image;
  if (!ReadImage(input_file, &labeled_image)) {
    cout << "Can't open file " << input_file << endl;
  }
  
  ComputeAttributes(&labeled_image, database, &attribute_image);

  if (!WriteImage(output_file, attribute_image)) {
    cout << "Can't write to " << output_file << endl;
  }

  //add data to databse file


  return 0;
}
