/*
* Program takes original gray image, text file containing the voting array of hough space, threshold for lines, output image file name
* This program will draw lines the original image file using the voting array and threshold to find the lines
* The result of this program will be saved into the output image file name
*/
#include "image.h"
#include "programs.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace ComputerVisionProjects;
using namespace Programs;

int
main(int argc, char **argv) {
  if (argc != 5) {
    printf("Usage: %s file1 file2 threshold file3\n", argv[0]);
    return 0;
  }

  const string original_file(argv[1]);
  const string voting_data(argv[2]);
  const size_t threshold = atoi(argv[3]);
  const string output_file(argv[4]);

  Image original_image;
  vector<vector<int>> voting_array; //TODO
  ifstream file(voting_data);
  string str;
  //getline(file,str); //str contains the rho step, theta step, rho dimension and theta dimension

  //parse the hough voting space into a 2d vector
  int start = 0;
  while(getline(file,str)){
    vector<int> data_line;
    for(int i = 0; i < str.length(); i++) {
      if(str[i] == ' ') {
        string data = str.substr(start,i);
        start = i+1;
        data_line.push_back(stoi(data));
      }
    }
    voting_array.push_back(data_line);
    start = 0;
  }
  cout << "Voting Array has been read." << endl;
  Image output_image;

  if (!ReadImage(original_file, &original_image)) {
  	cout << "Can't open file " << original_file << endl;
  	return 0;
  }

  LineDetection(&original_image, voting_array, threshold, &output_image);

  if (!WriteImage(output_file, output_image)) {
    cout << "Can't write to " << output_file << endl;
  }
}
