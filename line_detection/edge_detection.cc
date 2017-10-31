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
    out_image->AllocateSpaceAndSetSize(an_image->num_rows(),an_image->num_columns());
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
        cout << accumulator << " ";
        //out_image->SetPixel(i,j,accumulator);
      }
    }
  }

  void GenerateEdgeStrengthImage(Image* an_image, Image* strength_image) {
    cout << "Generating Edge Strength Image." << endl;
    //Setting up the mask
    Image maskX;
    Image maskY;
    //The dimensions of the mask
    int mask_r = 3;
    int mask_c = 3;
    //The mask values put into a 1D array (the length must match with mask_r * mask_c)
    //TODO: make sure the mask is flipped!
    vector<int> mask_array_X = 
    {0,0,0,
      1,1,1,
      2,2,2 };
    vector<int> mask_array_Y = 
    {0,0,0,
      1,1,1,
      2,2,2};
    maskX.AllocateSpaceAndSetSize(mask_r,mask_c);
    maskX.SetNumberGrayLevels(an_image->num_gray_levels());
    maskY.AllocateSpaceAndSetSize(mask_r,mask_c);
    maskY.SetNumberGrayLevels(an_image->num_gray_levels());
    int counter = 0;
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        maskX.SetPixel(i,j,mask_array_X[counter]);
        maskY.SetPixel(i,j,mask_array_Y[counter]);
        counter++;
        cout << maskX.GetPixelSafe(i,j) << " ";
      }
      cout << endl;
    }

    //perform convolution on the input image and store it into the output image
    convolve(&maskX, an_image, strength_image);
    cout << "Edge Strength Image Created." << endl;
  }


  void CleanEdgeImage(Image* edge_image, int threshold, Image* out_image) {
    cout << "Thresholding Edge Strength Image." << endl;
    out_image->AllocateSpaceAndSetSize(edge_image->num_rows(), edge_image->num_columns());
    out_image->SetNumberGrayLevels(edge_image->num_gray_levels());
    for(int i = 0; i < edge_image->num_rows(); i++) {
      for(int j = 0; j < edge_image->num_columns(); j++) {
        int value = edge_image->GetPixel(i,j);
        if(value >= threshold)
          out_image->SetPixel(i,j,225);
        else
          out_image->SetPixel(i,j,0);
      }
    }
    cout << "Thresholding Complete." << endl;
  }

}