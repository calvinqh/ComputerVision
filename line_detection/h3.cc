/*
* Program takes an input edge image file name, output Hough image file name, output textfile to store the voting array
* The input edge image is a binary image
* It will perform hough transformation to the given edge image. The voting size is ....
* The output of the hough voting space is saved into an output image file.
* The voting array will be saved into a textfile
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
    printf("Usage: %s file1 file2 file3\n", argv[0]);
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[2]);
  const string voting_data(argv[3]);

  Image binary_edge_image;
  Image hough_space;

  if (!ReadImage(input_file, &binary_edge_image)) {
  	cout << "Can't open file " << input_file << endl;
  	return 0;
  }

  vector<vector<int>> voting_array = GenerateHoughSpace(binary_edge_image, hough_space);

  if (!WriteImage(output_file, hough_space)) {
    cout << "Can't write to " << output_file << endl;
  }
  //TODO: save voting array

}