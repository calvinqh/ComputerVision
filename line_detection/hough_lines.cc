#include "programs.h"
#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

namespace Programs {

  vector<vector<int>> GenerateHoughSpace(Image* edge_image, Image* out_image) {
    vector<vector<int>> voting_array;
    out_image->AllocateSpaceAndSetSize(edge_image->num_rows(), edge_image->num_columns());
    out_image->SetNumberGrayLevels(edge_image->GetNumberGrayLevels());

    return voting_array;
  }

  void LineDetection(Image* original_image, vector<vector<int>> voting_array, int threshold, Image* out_image) {
    out_image->AllocateSpaceAndSetSize(original_image->num_rows(), original_image->num_columns());
    out_image->SetNumberGrayLevels(original_image->GetNumberGrayLevels());

    vector<LineParameter> lines;
  	for(int i = 0; i < voting_array.size(); i++) {
      for(int j = 0; j < voting_array[0].size(); i++) {
        if(voting_array[i][j] >= threshold) {
          //We found the theata and rho for a line
          //draw line onto out_image  
          LineParameter line;
          line.theta = 0;
          line.rho = 0;
          lines.push_back(line);
          size_t theta;
          size_t rho;
          size_t x0,y0;
          size_t x1,y1;
        }
      }
  	}
  }

}