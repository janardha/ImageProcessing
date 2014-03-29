////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "filter.h"


specialFilter::specialFilter()
{
	inputImageData = NULL;
	outputImage = NULL;

	rowSize = 0;
	colSize = 0;
	bytesInPixel = 0;
	bytesPerPixelInOutput = 0;


}
specialFilter::~specialFilter()
{
	//do nothing for now
}

void specialFilter::copyImagedata(unsigned char * srcptr, unsigned char * destptr)
{
	
	int rowIndex;
	int colIndex;

	//the output image variable is loaded with the image ptr value
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			destptr[rowIndex*colSize+colIndex] = srcptr[rowIndex*colSize+colIndex];
		}
}
void specialFilter::reloadInputImageData(unsigned char * imgPtr)
{
	
	int rowIndex;
	int colIndex;

	//the output image variable is loaded with the image ptr value
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			inputImageData[rowIndex*colSize+colIndex] = imgPtr[rowIndex*colSize+colIndex];
		}
}
unsigned char * specialFilter::imageReader()
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
void specialFilter::imageWriter(unsigned char* outputFile,int size)
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

	
	fwrite(outputFile, sizeof(unsigned char), size, Output_file_pointer);
	fclose(Output_file_pointer);

}

void specialFilter::initializePtr()
{
	outputImage = new unsigned char[rowSize*colSize*bytesInPixel];
	redMapping = new unsigned char[256];
	blueMapping = new unsigned char[256];
	greenMapping = new unsigned char[256];
}
void specialFilter::defaultDisplayInput()
{
	outputImage = inputImageData;
	bytesPerPixelInOutput = 3;
}

void specialFilter::freeMemory(int mode)
{
	//clearing all the pointer at the end of the execution
	if(redMapping)
		delete redMapping;
	if(blueMapping)
		delete blueMapping;
	if(greenMapping)
		delete greenMapping;
	
	if(outputImage)
		delete outputImage;
}