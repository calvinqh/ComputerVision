
Sample code that reads/writes pgm images and that draws lines on the images is provided.

image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

s1.cc : Creates a file that will save the center x,y coordinates of the given sphere image and its radius.


s2.cc : Uses sphere features, the center and radius, to find the light source vector for three given sphere images. The light sources are saved in an outputfile


s3.cc : Draws the surface normals onto the first image. Program assumes that the three images given use the same lighting as the three sphere images that was 
		used to find the light source vectors


s4.cc : Draw the albedo of the three images given. The program assumes that the three images given use the same lighting as the three shere images that was 
		used fo find the light source vectors.


programs.h : Contains the contracts of all functons used in this assignment.
			GenerateBinaryImage(an_image, binary_image, threshold)
			FindCenterAndRadius(binary_sphere_image)
			FindLightSourceVector(sphere_image, centerX, centerY, radius)
			FindSurfaceNormals(2d_direction_vectors, image1, image2, image3, step, threhsold, scene_with_normals)
			ComputeSurfaceAlbedo(2d_direction_vectors, image1, image2, image3, threshold, albedo_image)



sphere_features.cc : Contains the implementation of 
			GenerateBinaryImage()
			FindCenterAndRadius()


surface_normal.cc : Contains the implementation of
			FindSurfaceNormals()


light_sources.cc : Contains the implementation of 
			FindLightSourceVector()

albedo.cc : Contains the implementatin of 
			ComputeSurfaceAlbedo()


matrix_functions.h : Contains the contract of all functions used for matrix operations.
			printMatrix(matrix)
			get3x3Determinant(matrix, minors_matrix)
			get2x2Determinant(matrix, rowStart, rowEnd, columnStart, columnEnd)
			adjugate(matrix)
			getMatrixOfMinors(matrix)
			getMatrixCoFactors(matrix)
			inverseMatrix(matrix)


matrix_functions.cc : Contains the implemenation of all matrix functions.

----------------------
To compile in Linux:
----------
 
   make all

   or 
   
   make s1
   make s2
   make s3
   make s4

To run:
---------

./s1 {input sphere_image} {input threshold} {output sphere_paramter_file}

Finds the sphere's center and radius and saves these parameters into an output file.


./s2 {input sphere_parameter} {input sphere_image1} {input sphere_image2} {input sphere_image3} {output light_source_directions_file}

Uses the sphere's parameters to find the light sources direction vector for each image. Saves the results into output file.
Assumes that sphere images are all of the same sphere in the same position.


./s3 {input light_source_directions_file} {input image1} {input image2} {input image3} {input step} {input threshold} {output surface_normal_image}

Uses the light source direction vectors that was calculated with program 2 to draw the surface normal of the scene.
Assumes the scene images are all the same scene and in the same position.
Step is used to select which pixels to draw the normal on
Threshold is used to eliminate surfaces that are too dark


./s4 {input light_source_directions_file} {input image1} {input image2} {input image3} {input threshold} {output albedo_image}

Uses the light source direction vectors that was calculated with program 2 to draw the albedo.
Assumes the scene images are all the same scene and in the same position
Threshold is used to eliminate surfaces that are too dark


-----------

Notes:
-------
For s1, I used 110 threshold for creating the binary image of the sphere

For s3, I used 10 for the step and 85 for the threshold.

For s4, I used 85 for the threshold.

------Calculating the Light Source Vector--------
The equation used to calculate the light source
p = -1 * the derivative of Z with respect to X
q = -1 * the derivative of Z with respect to Z

derivative of Z with respect to X =  (-X/Z)
derivative of Z with respect to Y =  (-Y/Z)

Z = square_root(R^2 - X^2 - Y^2)

X and Y are the difference of the center to the brightest pixel

the normal is calculated by:
(p,q,1) / length((p,q,1))

Then scaled by the brightness of the brightest pixel.

--------Calculating the Surface Normal---------------
inverse(S) * I = N

Surface Normal = N / ||N||

--------Albedo Calculation-----------
Albedo = ||N||
