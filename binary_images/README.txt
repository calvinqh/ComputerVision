
Calvin Quach
Assignment 2

image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

p1.cc : Converts a gray-level image to a binary one given a threshold value

p2.cc : Segments a binary image into several connected regions

p3.cc : Given a labeled image, compute the object attributes and generates the database of the object(s).
        Attributes {label, x center, y center, rho, inertia, orientation, roundness}

p4.cc : Given a labeled image and database, compute the attributes of objects that are similar to database objects

programs.h : Contains the contracts of all functions used in this assignment.
             CreateBinaryImage(an_image, output_image, threshold)
             CreateLabeledImage(binary_image, output_image)
             ComputeAttributes(labeled_image, database, output_image)
             ClassifyInstances(input_image, database, output_image)

create_binary_image.cc : Contains the implementation of CreateBinaryImage()

create_labeled_image.cc : Contains the implementation of CreateLabeledImage()

compute_attributes.cc : Contains the implementation of ComputeAttributes()

classify_instance.cc : Contains the implementation of ClassifyInstances()

DisjSets.h : Contains the implementation of disjoint set. The code was pulled from old 335 assignment.

----------------------
To compile in Linux:
----------
 
   make all

To run:
---------

./image_demo objects.pgm output.pgm

This will open image objects.pgm, will draw a line on the image, and will save resulting image to file output.pgm


./p_1 {input gray-level image} {input gray-level threshold} {output binary_image}

Will read the gray level image and use the given gray level threshold to create binary image


./p_2 {input binary image} {output labeled image}

Will run through the binary image with raster scan and return a labeled image. Labels are the gray scale value shared by the objects neighbors


./p_3 {input labeled image} {output database} {output image}

Will calculate: center coordinates of each object, the minimum moment of inertia, orientation, rho and roundness. These results will be outputed into the database file. In the output image, the center and orientation are drawn.

./p_4 {input labeled image} {input database} {output image}

Classifies objects in the given image by making comparisons to the database. Comparisons are done by checking the percent difference between attributes. Output image shows the center and orientation of all objects identified.

-----------

General Notes:
----------

The chosen threshold is 134. Because it most closely matches the sample output file given.
The threshold 110 works just as well because when creating the binary image, it ignores the noise near the bottom right of the image.
Any thing less would've picked up some noise.


The classification correctly identifies the two objects, but gives a false positive for one object.

