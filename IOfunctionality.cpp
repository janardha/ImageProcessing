////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//28th September 2012
////////////////////////////////////////////////////////
#include "processImage.h"


processImage::processImage()
{
	inputImageData = NULL;
	outputImage = NULL;
	grayImage = NULL;
	grayImage1 = NULL;
	rowSize = 0;
	colSize = 0;
	bytesInPixel = 0;
	bytesPerPixelInOutput = 0;
	histogram[0] = 0;
}
processImage::~processImage()
{
	//do nothing for now
}

void processImage::setOutputImagePointer(unsigned char * imageptr)
{
	
	int rowIndex;
	int colIndex;

	//the output image variable is loaded with the image ptr value
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			outputImage[rowIndex*colSize+colIndex] = imageptr[rowIndex*colSize+colIndex];
		}
}
unsigned char * processImage::imageReader()
{
	//In this module the file the from the set set path is read 
	//and the image is loaded into pointer whihc is returned
	
	unsigned char *imagePtr;
	int errorNum = fopen_s(&inputFilePointer,imagePath,"rb");
	//int errorNum = fopen_s(&inputFilePointer,"c:/users/public/images/desk.raw","rb");

	if(errorNum)
	{
		cout<<"in input"<<endl;
		cout<<"Error: The file cannot be opened"<<endl;
	}

	bytesPerPixelInOutput = bytesInPixel;

	imagePtr = new unsigned char[rowSize*colSize*bytesInPixel];

	fread(imagePtr,sizeof(unsigned char), rowSize*colSize*bytesInPixel,inputFilePointer);
	
	cout<<imagePtr[10]<<endl;
	fclose(inputFilePointer);
	cout<<"File read successful"<<endl;
	return imagePtr;
	
}
void processImage::imageWriter(unsigned char* outputFile)
{
	//in this module the image pointer given by outputFile 
	//is written into the path set using setImagePath

	int errorNum = fopen_s(&Output_file_pointer,imagePath,"wb");
	if(errorNum)
	{
		cout<<imagePath<<endl;
		cout<<"in output"<<endl;
		cout<<"Error: The file cannot be opened"<<endl;
		return;
	}

	
	fwrite(outputFile, sizeof(unsigned char), rowSize*colSize*bytesPerPixelInOutput, Output_file_pointer);
	fclose(Output_file_pointer);

}

void processImage::initializePtr()
{
	grayImage =  new unsigned char[rowSize*colSize];
	grayImage1 = new unsigned char[rowSize*colSize];
	outputImage = new unsigned char[rowSize*colSize];
}
void processImage::defaultDisplayInput()
{
	outputImage = inputImageData;
	bytesPerPixelInOutput = 3;
}

void processImage::freeMemory(int mode)
{
	//clearing all the pointer at the end of the execution
	delete grayImage1;
	delete grayImage;
	delete inputImageData;
	delete outputImage;
}
