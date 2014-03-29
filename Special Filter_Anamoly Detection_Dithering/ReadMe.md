
The ImageAlgoMain.cpp file is the main file in which all the other subroutines are called.
filter.h is the header file common to all the .cpp files. In this file the class variables are defined and the headers are declared.
The reading and writing the files are done in the IOfunctionality.cpp.
Artistic filters are defined in specialFilters.cpp
Morphological processing is done in MorphlogicalProcessing.cpp
Haltoning is done in HalftoningMethods.cpp
Once the files are complied and built, to run the file from the command prompt the structure is


argv[0] --------ImageProcessing 
argv[1]---------Mode     //problem Number
argv[2]---------Submode  //different methods employed
argv[3] --------Input file path
argv[4] --------Output file Path
argv[5]---------Number of Rows
argv[6] --------Number of Cols 
argv[7]---------Number of bytes in a pixel (3 for color and 1 for gray image)
argv[8]---------in prob 1a - probe path
		in prob 1b - grain path
		in prob 1c - border path
		in prob 2 - background type
		in prob 3 a - order
		in prob 3 b - diffusion method 1 = floyd steinberg 2 = Jarvis method 3 = stucki method
argv[9]---------in prob 1a - response path 
		in prob 1b - constant A
		in prob 2 b- number of gear tooth
		in prob 3 a - method //1 for bayer and 2 for other method	
argv[10]--------in prob	1b - constant B

The following is the input structure:
MODE	SUBMODE		ALGORITHM
1	1		Color mapping
1 	2		Grainy image
1 	3		Border addition

2	1		PCB prob with final result displaying the hole numbers and pathways
			{the intermediate results can be inverted in this prob as the implementation 
			of the table is done for black background}	
2	2		GearTooth with final result showing missing gears and also the radius and 
			center pixels are displayed on the screen
			{the intermediate results can be inverted in this prob as the implementation 
			of the table is done for black background}
2 	3		Dilation of Image MaxIteration is given by arg 9
2 	4		Hole count
2 	5		Shrinking algorithm Max iteration is given by arg 9
2 	6		Negation of Image
2	7		Location of the center pixel or holes
2	8		Radius of gear center row - arg 8; center col - arg 9
2	9		Gear tooth positions	radius - arg8; center row - arg 9; center col - arg 10
2 	10		Missing Gear tooth positions	radius - arg8; center row - arg 9; center col - arg 10
2	11		Outline the image given

3	1		Dithering Matrix
3	2		error Diffusion
3	3		4 gray level
3	4		error diffusion serpentine method


Examples for executing the code:

1.	C:\> specialFilters	1	1	c:/imagepath/sailboat.raw	c:/imagepath/sailMapped.raw	256	256	3  c:/imagepath/probe.raw  c:/imagepath/response.raw
This executes color mapping of the image

2.	C:\> specialFilters	1	2	c:/imagepath/sailmapped.raw	c:/imagepath/sailgrainy.raw	256	256	3  c:/imagepath/grain.raw  A	B
This executes adition of grainy image

3.	C:\> specialFilters	1	3	c:/imagepath/sailgrainy.raw	c:/imagepath/sailborder.raw	256	256	3  c:/imagepath/border.raw 

4.	C:/> specialFilters	2	1	c:/imagepath/pcb.raw	c:/imagepath/pathway.raw 	400 550	1 white
This executes the PCB analysis

5.	c:/> specialFilters	2	2	c:/imagepath/gearTooth.raw	c:/imagepath/gearMIssing.raw	250	250	1 white 12
This executes the gear position

6.	c:/> specialFilters	3	1	c:/imagepath/man.raw	c:/imagepath/bayerDithering.raw	512	512	1 2 1
This executes the bayer method 

7.	c:/> specialFilters	3	2	c:/imagepath/man.raw	c:/imagepath/errorDiffuse.raw	512	512	1 method
This executes the error diffusion method 

8.	c:/> specialFilters	3	3	c:/imagepath/man.raw	c:/imagepath/errorDiffuse.raw	512	512	1 order(2 or 4)
This executes the four gray level method 

9.	c:/> specialFilters	3	4	c:/imagepath/man.raw	c:/imagepath/errorDiffuse.raw	512	512	1 
This executes the serpentine method for floyd steinberg method 

In problem 2, the various steps can be executed step by step.
