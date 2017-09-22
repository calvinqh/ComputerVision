
#include "image.h"
#include "programs.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

namespace Programs {
  void createBinaryImage(Image *an_image, Image *out_image, size_t threshold) {
    cout << "Creating Binary Image ..." << endl;
    out_image->AllocateSpaceAndSetSize(an_image->num_rows(), an_image->num_columns());
    out_image->SetNumberGrayLevels(an_image->num_gray_levels());
    for(size_t i = 0; i< an_image->num_rows(); i++) {
      for (size_t j = 0; j < an_image->num_columns(); j++) {
        int byte = 0;
        if(an_image->GetPixel(i,j) > threshold)
          byte=225;
        out_image->SetPixel(i,j,byte);
      }
    }
    cout << "Binary Image created." << endl;
  }


  void createLabeledImage(Image *binary_image, Image *out_image) {
    cout << "Labeling Image ..." << endl;
    

    cout << "Labeled Image created." << endl;
  }


}
