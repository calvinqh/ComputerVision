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

  void convolve(Image* mask, Image* an_image, Image* out_image){
    cout << "Performing convolution" << endl;
    out_image->AllocateSpaceAndSetSize(an_image->num_rows,an_image->num_columns);
    out_image->SetNumberGrayLevels(an_image->num_gray_levels());
    for(int i = 0; i < an_image->num_rows(); i++) {
      for(int j = 0; j < an_image->num_columns(); j++) {
        int accumulator = 0;
        //the neighbors
        for(int r = -1; r <= 1; r++) {
          for(int c = -1; c <= 1; c++) {
            accumulator+=(an_image->GetPixelSafe(i+c,j+r)*mask->GetPixel(1+r,c+1));
          }
        }
        out_image->SetPixel(i,j,accumulator);
        cout << accumulator << " ";
      }
    }
  }


}