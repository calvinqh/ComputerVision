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
  Image binary_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
 
  //Create the binary image, image is saved into binary_image 
  CreateBinaryImage(&an_image, &binary_image, threshold);
  
  Image label_image;
  CreateLabeledImage(&binary_image, &label_image);
  Image attribute_image;
  CreateLabeledImage(&binary_image, &attribute_image);
  ComputeAttributes(&label_image, "file.txt", &attribute_image);
  if (!WriteImage("binary_image.pgm", binary_image)) {
    cout << "Can't write to binary image file"  <<  endl;
  }
  if (!WriteImage("label_image.pgm", label_image)) { 
    cout << "Can't write to label image file"  <<  endl;
  } 
  if (!WriteImage(output_file, attribute_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
  
}
