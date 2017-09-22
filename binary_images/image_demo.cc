// Sample test file for the image class.
// Reads a given pgm image, draws a line, and saves it to
// another pgm image.
#include "image.h"
#include "programs.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;
using namespace Programs;

int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 file2 threshold\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[2]);
  const size_t threshold = atoi(argv[3]);

  Image an_image;
  Image out_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
 
  //Create the binary image, image is saved into out_image 
  createBinaryImage(&an_image, &out_image, threshold);

  if (!WriteImage(output_file, out_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }

}
