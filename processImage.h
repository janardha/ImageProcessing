////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//28th September 2012
////////////////////////////////////////////////////////
#include "iostream"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "cstdlib"
#include "malloc.h"
using namespace std;

	

class processImage
{
private:
	unsigned char *inputImageData;
	unsigned char *outputImage;
	unsigned char *grayImage;
	unsigned char *grayImage1;
	char imagePath[_MAX_PATH];

	int rowSize;
	int colSize;
	int bytesInPixel;
	int bytesPerPixelInOutput;
	int histogram[256];

private:
	FILE *inputFilePointer;
	FILE *Output_file_pointer;
	FILE *hist_out;

public:
	//constructor
	processImage();

	//destructor
	~processImage();

public:
	unsigned char * getInputImagePointer(){return inputImageData;};
	void setInputImagePointer(unsigned char * imageptr) {inputImageData = imageptr;};
	unsigned char * getOutputImagePointer(){return outputImage;};
	void setOutputImagePointer(unsigned char * imageptr); 
	unsigned char * getModifiedImagePointer(){return grayImage;};
	char* getFilePath() {return imagePath;};
	void setFilepath(char path[]) {strcpy(imagePath,path);};
	int getRowSize() { return rowSize;};
	void setRowSize(int r) {rowSize = r;};
	int getColSize() { return colSize;};
	void setColSize(int c) {colSize = c;};
	int getBytesInPixel() { return bytesInPixel;};
	void setBytesInPixel(int b) {bytesInPixel = b;};
	void initializePtr();

public:

	unsigned char *imageReader();
	void imageWriter(unsigned char* outputFile);
	void freeMemory(int mode);
	/////////////enhancement techniques////////////
	void grayScaleConverter_luminosity();
	void grayScaleConverter_avg();
	void defaultDisplayInput();
	void histogramGeneration(unsigned char* imageHist);
	void linearFiltering();
	void squareRootFiltering();
	void cumulativeHistogramEqualization();
	void digitalHistogramEqulization();
	void localContrastEnhancement();
	/////////////denoising////////////////////
	void meanFiltering(const int filterOrder);
	void medianFiltering3();
	void medianFiltering5();
	void lowPassFilteringWt10();
	void lowPassFilteringWt16();
	void lowPassGaussianFiltering3(unsigned char* inputImage, unsigned char* outputImage);
	void lowPassGaussianFiltering5(unsigned char* inputImage, unsigned char* outputImage);
	void outlierFiltering(float threshold);
	void SSIM(char *image_path[]);
	////////////////edge detection//////////
	void sobelOperator(int subMode, float threshold);
	void varianceEdgeDetection(float threshold);
	void logOfGaussian();
	int edgeThresholding(float threshold);
	
	void sortcoefficients(int *vectorCoefficients, int vectorLength);

};

	
