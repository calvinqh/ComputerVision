
Calvin Quach
Assignment 3

image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

h1.cc : Creates an edge strength image with the given input image. Program applies Gaussian Smoothing and then uses Sobel to detect edges


h2.cc : Thresholds the given edge strength image with the given threshold. Edges in the resulting image are non-zero values.

h3.cc : Creates a hough transform database and image for the given binary image


h4.cc : Results in an image with drawn lines overlayed onto the original image. Lines are chosen from the hough space database based off given threshold

programs.h : Contains the contracts of all functions used in this assignment. Also contains the struct, LineParameter
			GenerateEdgeStrengthImage(an_image, strength_image)
			CleanEdgeImage(edge_image, threshold, out_image)
			GenerateHoughSpace(edge_image, out_image)
			LineDetection(original_image, voting_array, threshold, out_image)

			convolve(mask1, mask2, an_image, out_image)
			smooth(image, smoothed_image)
			copy(image, copied_image)

edge_detection.cc : Contains the implementation of
					GenerateEdgeStrenth()
					CleanEdgeImage()
					convolve()

hough_lines.cc : Contains the implementation of
				GenerateHoughSpace()
				LneDetection()


----------------------
To compile in Linux:
----------
 
   make all

   or

   make h1
   make h2
   make h3
   make h4

To run:
---------

./h1 {input original_image} {output edge_strength_image}

Will read the gray level image and output an edge strength image.


./h2 {input edge_strength_image} {input edge_threshold} {output binary_edge_image}

Will output an edge image that filters out the edge strength image with the given threshold


./h3 {input binary_edge_image} {output hough_space_image} {output hough_space_database(txt)}

With the given binary edge image, it will output an image and database that using hough transform to vote for lines


./h4 {input original_image} {input hough_space_database} {input line_threshold} {output original_image_with_lines}

With the given hough space database, it will produce a new image of the original image with lines drawn. The lines are chosen from the parameters of the hough space based off the threshold given.

-----------
General Notes:
-----------

The threshold chosen for h2 is 20. 
The threhsold chosen for h4 is 160.

The lines produced for this assignment are very thick. 
The program has trouble looking for vertical lines.
I believe that my problem is that my rho space does not represent negative rho.

The program correctly draw lines for hough_simple_2 but not for hough_simple_1 and complex.
