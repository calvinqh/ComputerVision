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

  void GenerateBinarayImage(Image* an_image, Image* out_image, int threshold) {
    cout << "Creating Binary Image ..." << endl;
    out_image->AllocateSpaceAndSetSize(an_image->num_rows(), an_image->num_columns());
    out_image->SetNumberGrayLevels(an_image->num_gray_levels());
    for(size_t i = 0; i< an_image->num_rows(); i++) {
      for (size_t j = 0; j < an_image->num_columns(); j++) {
        int byte = 0;
        if(an_image->GetPixel(i,j) > threshold)
          byte=255;
        out_image->SetPixel(i,j,byte);
      }
    }
    cout << "Binary Image created." << endl;
  }

  vector<int> FindCenterAndRadius(Image* binary_image) {
    //contains the center location and the radius
    //i.e. row coord of center, column coord of center, radius
    vector<int> features;
    int rowTotal = 0, colTotal = 0, total = 0;
    double topR = binary_image->num_rows(), bottomR = 0, leftC = 0, rightC = 0;

    //finds the center of the image
    //TODO: fix column and row for i and j
    for(size_t i = 0; i < binary_image->num_rows(); i++) {
      for(size_t j = 0; j < binary_image->num_columns(); j++) {
        if(binary_image->GetPixel(i,j) <= 0)
          continue;
        if(i < topR)
          topR = i;
        if(i > bottomR)
          bottomR = i;
        if(j < leftC)
          leftC = j;
        if(j > rightC)
          rightC = j;

        rowTotal += i;
        colTotal += j;
        total++;
      }
    }
    //calculate the average
    double average_radius = ((bottomR-topR)/2 + (rightC-leftC)/2)/2;
    cout << average_radius << endl;
    features.push_back(rowTotal/total);
    features.push_back(colTotal/total);
    features.push_back(average_radius);

    return features;
  }

}
