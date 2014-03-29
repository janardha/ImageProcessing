
The ImageAlgoMain.cpp file is the main file in which all the other subroutines are called.
modification.h is the header file common to all the .cpp files. In this file the class variables are defined and the headers are declared.
The reading and writing the files are done in the IOfunctionality.cpp.
Geometrical Transformations are defined in transforms.cpp
Texture synthesis and analysis is done in textureanalysis.cpp and texturesynthesis.cpp
OCR is done in OCR.cpp
Once the files are complied and built, to run the file from the command prompt the structure is


argv[0] --------ImageProcessing 
argv[1]---------Mode     //problem Number
argv[2]---------Submode  //different methods employed
argv[3] --------Input file path
argv[4] --------Output file Path
argv[5]---------Number of Rows
argv[6] --------Number of Cols 
argv[7]---------Number of bytes in a pixel (3 for color and 1 for gray image)
argv[8]---------in prob 1a - piece path
		in prob 1b - romney path
		in prob 1c - alpha value
		in prob 1d - obama path
		in prob 2a - window size
		in prob 2b - window size
		in prob 2c - window size
		in prob 3  - number of characters
		in prob 1b - romney warp save path
		in prob 1d - obama warp save path
		in prob 2a - 0/1 (feature reduction)
		in prob 2c - min cut requirement
		in prob 3  - Final path for n > 10
argv[10]--------in prob	1b - piece sieze

The following is the input structure:
MODE	SUBMODE		ALGORITHM
1	1		Piece mapping
1 	2		warping
1 	3		morphing

2	1		Kmean {1 - kmean with all features else reduced}	
2	2		Texture random process {window size is argv 8}
2 	3		Texture synthesis

3	1		OCR

Examples for executing the code:

1.	C:\> GeoMod	1	1	c:/imagepath/lion.raw	c:/imagepath/lionMtched.raw	500	400	3  c:/imagepath/piece.raw  300 300
This executes color mapping of the image

2.	C:\> GeoMod	1	2	c:/imagepath/lionmatched.raw	c:/imagepath/warp.raw	500	400	3  c:/imagepath/romney.raw  c:/imagepath/romneywarp.raw
This executes adition of grainy image

3.	C:\> GeoMod	1	3	c:/imagepath/sailgrainy.raw	c:/imagepath/sailborder.raw	256	256	3  c:/imagepath/border.raw 

4.	C:/> GeoMod	2	1	c:/imagepath/pcb.raw	c:/imagepath/pathway.raw 	400 550	1 white
This executes the PCB analysis

5.	c:/> GeoMod	2	2	c:/imagepath/gearTooth.raw	c:/imagepath/gearMIssing.raw	250	250	1 white 12
This executes the gear position

6.	c:/> GeoMod	3	1	c:/imagepath/man.raw	c:/imagepath/bayerDithering.raw	512	512	1 2 1
This executes the OCR method 
IN ocr to 

In problem 2, the various steps can be executed step by step.
