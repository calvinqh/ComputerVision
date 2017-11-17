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

  vector<vector<int>> voting_array = GenerateHoughSpace(&binary_edge_image, &hough_space);

  if (!WriteImage(output_file, hough_space)) {
    cout << "Can't write to " << output_file << endl;
  }

  //saving the hough space into database file
  FILE* output = fopen(voting_data.c_str(), "w");
  if(output==0 && voting_data.compare("") != 0) {
    cout << "Can't open voting file" << endl;
  }
  for(int i = 0; i < voting_array.size(); i++) {
    string line = "";
    int j = 0;
    for(; j < voting_array[0].size()-1; j++) {
      line += to_string(voting_array[i][j]) + " ";
    }
    line += to_string(voting_array[i][j]) + "\n";
    fprintf(output,line.c_str());
  }
  if(output!=0) fclose(output);
}
