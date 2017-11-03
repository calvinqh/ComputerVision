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

  void smooth(Image* an_image, Image* out_image) {
    cout << "Applying Gaussian Smoothing" << endl;
    out_image->AllocateSpaceAndSetSize(an_image->num_rows(), an_image->num_columns());
    out_image->SetNumberGrayLevels(an_image->num_gray_levels());
    vector<vector<int>> kernel;
    vector<int> kernel_vals = {
      1,2,1,
      2,12,2,
      1,2,1
    };
    int count = 0;
    for(int i = 0; i < 3; i++) {
      vector<int> t;
      for(int j = 0; j < 3; j++) {
        t.push_back(kernel_vals[count]);
      }
      kernel.push_back(t);
    }

    //convolve the kernel to the image
    for(int i = 0; i < an_image->num_rows(); i++) {
      for(int j = 0; j < an_image->num_columns(); j++) {
        int accumulator = 0;
        //the neighbors
        for(int r = -1; r <= 1; r++) {
          for(int c = -1; c <= 1; c++) {
            accumulator+=(an_image->GetPixelSafe(i+c,j+r)*kernel[1+r][c+1]);
          }
        }
        accumulator /= 24;
        out_image->SetPixel(i,j,accumulator);
      }
    }
  }
  void convolve(Image* mask1, Image* mask2, Image* an_image, Image* out_image){
    cout << "Performing convolution" << endl;
    out_image->AllocateSpaceAndSetSize(an_image->num_rows(),an_image->num_columns());
    out_image->SetNumberGrayLevels(an_image->num_gray_levels());
    for(int i = 0; i < an_image->num_rows(); i++) {
      for(int j = 0; j < an_image->num_columns(); j++) {
        int accumulator1 = 0, accumulator2 = 0;
        //the neighbors
        for(int r = -1; r <= 1; r++) {
          for(int c = -1; c <= 1; c++) {
            accumulator1+=(an_image->GetPixelSafe(i+c,j+r)*mask1->GetPixel(1+r,c+1));
            accumulator2+=(an_image->GetPixelSafe(i+c,j+r)*mask2->GetPixel(1+r,c+1));
          }
        }
        double strength = sqrt(pow(accumulator1,2) + pow(accumulator2,2));
        out_image->SetPixel(i,j,int(strength));
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
    {-1,0,1,
      -2,0,2,
      -1,0,1 };
    vector<int> mask_array_Y = 
    {1,2,1,
      0,0,0,
      -1,-2,-1};
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
    //smooth picture
    Image smooth_picture;
    smooth(an_image, &smooth_picture);

    //perform convolution on the input image and store it into the output image
    convolve(&maskX, &maskY, &smooth_picture, strength_image);
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
