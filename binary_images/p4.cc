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
  Image classified_image;

  if (!ReadImage(input_file, &labeled_image)) {
    cout << "Can't open file " << input_file << endl;
  }
  ClassifyInstances(&labeled_image, database, &classified_image);

  if (!WriteImage(output_file, classified_image)) {
    cout << "Can't write to " << output_file << endl;
  }
  return 0;
}
