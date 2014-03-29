////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "modification.h"


modifyImage::modifyImage()
{
	inputImageData = NULL;
	outputImage = NULL;

	iprowSize = 0;
	ipcolSize = 0;
	oprowSize = 0;
	opcolSize = 0;
	bytesInPixel = 0;
	bytesPerPixelInOutput = 0;
	numOfFeaturesVec = 27;
	numOfControlPoints = 6;
	numOfTriangles = 4;

	rowMin = 0;
	colMin = 0;
	rowMax = 0;
	colMax = 0;
	boundedArea = 0;

}
modifyImage::~modifyImage()
{
	//do nothing for now
}

void modifyImage::copyImagedata(unsigned char * srcptr, unsigned char * destptr)
{
	
	int rowIndex;
	int colIndex;

	//the output image variable is loaded with the image ptr value
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			destptr[rowIndex*ipcolSize+colIndex] = srcptr[rowIndex*ipcolSize+colIndex];
		}
}
void modifyImage::reloadInputImageData(unsigned char * imgPtr)
{
	
	int rowIndex;
	int colIndex;

	//the output image variable is loaded with the image ptr value
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			inputImageData[rowIndex*ipcolSize+colIndex] = imgPtr[rowIndex*ipcolSize+colIndex];
		}
}
unsigned char * modifyImage::imageReader()
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
	
	oprowSize = iprowSize;
	opcolSize = ipcolSize;
	bytesPerPixelInOutput = bytesInPixel;

	imagePtr = new unsigned char[iprowSize*ipcolSize*bytesInPixel];

	fread(imagePtr,sizeof(unsigned char), iprowSize*ipcolSize*bytesInPixel,inputFilePointer);
	
	cout<<imagePtr[10]<<endl;
	fclose(inputFilePointer);
	cout<<"File read successful"<<endl;
	return imagePtr;
	
}
void modifyImage::imageWriter(unsigned char* outputFile,int size)
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

void modifyImage::initializePtr()
{
	outputImage = new unsigned char[oprowSize*opcolSize*bytesPerPixelInOutput];
	redComp = new unsigned char[iprowSize*ipcolSize];
	greenComp = new unsigned char[iprowSize*ipcolSize];
	blueComp = new unsigned char[iprowSize*ipcolSize];

}
void modifyImage::defaultDisplayInput()
{
	outputImage = inputImageData;
	bytesPerPixelInOutput = 3;
}

void modifyImage::freeMemory(int mode)
{
	//clearing all the pointer at the end of the execution

	if(outputImage)
		delete outputImage;
	if(redComp)
		delete redComp;
	if(greenComp)
		delete greenComp;
	if(blueComp)
		delete blueComp;
}