#include "DisjSets.h"
#include "image.h"
#include "programs.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

namespace Programs {
  void CreateBinaryImage(Image *an_image, Image *out_image, size_t threshold) {
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


  void CreateLabeledImage(Image *binary_image, Image *out_image) {
    cout << "Labeling Image ..." << endl;
    //table equiv
    int label_counter = 0;
    DisjSets label_equivalence(255);
    out_image->AllocateSpaceAndSetSize(binary_image->num_rows(), binary_image->num_columns());
    out_image->SetNumberGrayLevels(binary_image->num_gray_levels());
    for(size_t row = 0; row < binary_image->num_rows(); row++) {
      for(size_t col = 0; col < binary_image->num_columns(); col++) {
        int a = binary_image->GetPixel(row,col);
        if(a == 0) {
          //a is part of the background
          out_image->SetPixel(row,col,0);
        } 
        else {
          int b = out_image->GetPixelSafe(row-1,col);
          int c = out_image->GetPixelSafe(row,col-1);
          int d = out_image->GetPixelSafe(row-1,col-1);
          if(d > 0) {
            a = d;
          }
          else if(c > 0 && b <= 0 && d <= 0) {
            a = c;
          }
          else if(b > 0 && c <= 0 && d <= 0) {
            a = b;
          }
          else if(b > 0 && c > 0 && d <= 0) {
            a = b;
          }
          else {
            //new label
            //set a to new gray level
            a = label_counter;
            label_counter++;
            if(label_counter > label_equivalence.GetSize())
              label_equivalence.Extend(label_equivalence.GetSize());
          }
          if(b > 0 && c > 0 && b != c) {
            int root1 = label_equivalence.Find(b);
            int root2 = label_equivalence.Find(c);
            if(root1 != root2) //if they dont belong to the same set
              label_equivalence.UnionSets(root1,root2);
          }
          out_image->SetPixel(row,col,a);
        }
      }
    }
    //resolve equivalences on the output image
    for(size_t r = 0; r < out_image->num_rows(); r++) {
      for(size_t c = 0; c < out_image->num_columns(); c++) {
        int label = out_image->GetPixel(r,c);
        //check if actually is label
        if(label != 0) {
          //check if it has any equivalency (what set it belongs to)
          int set_owner = label_equivalence.Find(label);
          out_image->SetPixel(r,c,set_owner);
        }
      }
    }
    cout << "Labeled Image created." << endl;
  }
}
