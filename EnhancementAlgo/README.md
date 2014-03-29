ImageProcessing
===============

Image processing algorithms implementation

The ImageAlgoMain.cpp file is the main file in which all the other subroutines are called.
processImage.h is the header file common to all the .cpp files. In this file the class variables are defined and the headers are declared.
The reading and writing the files are done in the IOfunctionality.cpp.
Enhancement algorithms are defined in ImageEnhancement.cpp
Noise reduction is done in DenoisingAlgorithms.cpp
Edge detection and thinning are done in EdgeDetectionAlgorithms.cpp
Once the files are complied and built, to run the file from the command prompt the structure is

argv[0] --------ImageProcessing 
argv[1]---------Mode     //problem number
argv[2]---------Submode  //different methods in the problem eg. Median filter in Question 2.
argv[3] --------Input file path
argv[4] --------Output file Path
argv[5]---------Number of Rows
argv[6] --------Number of Cols 
argv[7]---------Number of bytes in a pixel (3 for color and 1 for gray image)
argv[8]---------The filter order in case of filters
 		Distorted image path in case of ssim and mse
		Threshold in case of edge detection algorithms

The following is the input structure:
MODE	SUBMODE	ALGORITHM EXECUTED
1	1	Gray scale converter using averaging
1	2	Gray scale converter using luminosity
1	3	Linear scaling function
1	4	Square root scaling function
1	5	Cumulative histogram equalization
1	6	Digital histogram equalization
1	7	Local contrast enhancement

2	1	Mean filtering order given by argument 8
2	2	Median filtering order given by argument 8
2	3	Low pass filtering order given by argument 8
2	4	Gaussian filtering order given by argument 8
2	5	Outlier filtering threshold given by argument 8
2	6	SSIM calculator noisy image path is given by argument 8

3	1	Sobel filter, threshold given by arg 8
3	2	Variance filter, threshold given by arg 8
3	3	Laplacian of Gaussian filter 
3	4	Edge thinning, threshold by arg 8

Examples for executing the code:

1.	C:\> ImageProcessing 	1	1	c:/imagepath/desk.raw	c:/imagepath/grayimage.raw	400 	300 	3
This executes the gray scale conversion using averaging method

2.	C:/> ImageProcessing 	2	1	c:/imagepath/peppers_mixed.raw	c:/imagepath/meanfilter.raw 	512	 512	1	5
This executes the mean filtering of the order 5x5. 3x3 and 7x7 can also be chosen.

3. c:/> ImageProcessing 	2	6	c:/imagepath/peppers.raw	c:/imagepath/mse.raw	512	512	1	c:/imagepath/noisyImage.raw
This executes the SSIM subroutine

4. C:/> ImageProcessing 	3	1	c:/imagepath/girl.raw	c:/imagepath/sobel.raw 	256	256	1	90
This executes the sobel filtering with the 90% of the image is background and the rest 10% are the edges.

For executing a cascaded filter first the filter number 1 is executed. 
then the output file of filter1 is used as the input for filter2 and the 
filter 2 is executed to get the cascaded result.

5. c:/> ImageProcessing		2	1	c:/imagepath/peppers_mixed.raw	c:/imagepath/meanFilt.raw 512	512	1	5

c:/> ImageProcessing		2	2	c:/imagepath/meanFilt.raw	c:/imagepath/meanMedianCascade.raw 512	512	1	5
