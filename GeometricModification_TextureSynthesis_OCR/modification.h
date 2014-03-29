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
#include "assert.h"
#include "float.h"

using namespace std;

#define WHITE 1
#define BLACK 2

#define PIECESIZE 122

extern int *k_means(double **data, int n, int m, int k, double t, double **centroids);

class modifyImage
{
private:
	unsigned char *inputImageData;
	unsigned char *outputImage;
	unsigned char *modImage;
	unsigned char *modOut;
	unsigned char *redComp;
	unsigned char *greenComp;
	unsigned char *blueComp;

	char imagePath[_MAX_PATH];
	char imagePath1[_MAX_PATH];

	int iprowSize;
	int ipcolSize;
	int oprowSize;
	int opcolSize;
	int bytesInPixel;
	int bytesPerPixelInOutput;

	struct location
	{
		int r_pos;
		int c_pos;
	}loc[12];

	struct coeff
	{
		double Acoeff;
		double Bcoeff;
	}coeffVec[6], coeffVec1[6];

	struct filters
	{
		int bank[25];
	}filterBank[25];

	struct transformedIp
	{
		double* img;
	}tIP[27];

	int numOfFeaturesVec;
	int numOfControlPoints;
	int numOfTriangles;
	int rowMin;
	int colMin;
	int rowMax;
	int colMax;
	float boundedArea;
	float normalizedArea;
	float normalizedPerimeter;
	float cirularity;
	int eulerNumber;
	int zeroCountCol;
	int zeroCountRow;
	float xCOG;
	float yCOG;

private:
	FILE *inputFilePointer;
	FILE *Output_file_pointer;
	FILE *hist_out;

public:
	//constructor
	modifyImage();

	//destructor
	~modifyImage();

public:
	unsigned char * getInputImagePointer(){return inputImageData;};
	void setInputImagePointer(unsigned char * imageptr) {inputImageData = imageptr;};
	unsigned char * getOutputImagePointer(){return outputImage;};
	void copyImagedata(unsigned char * srcptr, unsigned char * destptr);
	unsigned char * getModImagePointer(){return modImage;};
	void setModImagePointer(unsigned char * imageptr) {modImage = imageptr;};
	void reloadInputImageData(unsigned char * imgPtr);

	//set and get functions for rowsize, colsize, color/blackNwhite
	char* getFilePath() {return imagePath;};
	void setFilepath(char path[]) {strcpy(imagePath,path);};
	int getIpRowSize() { return iprowSize;};
	void setIpRowSize(int r) {iprowSize = r;};
	int getIpColSize() { return ipcolSize;};
	void setIpColSize(int c) {ipcolSize = c;};
	int getBytesInPixel() { return bytesInPixel;};
	void setBytesInPixel(int b) {bytesInPixel = b;};

	int getOpRowSize() { return oprowSize;};
	void setOpRowSize(int r) {oprowSize = r;};
	int getOpColSize() { return opcolSize;};
	void setOpColSize(int c) {opcolSize = c;};
	int getBytesInPixelOut() { return bytesPerPixelInOutput;};
	void setBytesInPixelOut(int b) {bytesPerPixelInOutput = b;};

	void initializePtr();

	void setNumofControlPoints(int n){numOfControlPoints = n;};
	int getNumOfControlPoints(){return numOfControlPoints;};
	void setNumofTriangles(int n){numOfTriangles = n;};
	int getNumOfTriangles(){return numOfTriangles;};

public:

	unsigned char *imageReader();
	void imageWriter(unsigned char* outputFile,int size);
	void freeMemory(int mode);
	void defaultDisplayInput();

	///////////// geometric transforms////////////
	void getCoordinates(unsigned char* ipImg, int bkgrnd, int bytesperPixel);
	float getTheta();
	void segregateImage(unsigned char* ipImg);
	void rotateImage(unsigned char* ipImg, unsigned char* opImg, float theta);
	void scaleImage(unsigned char* ipImg, unsigned char* opImg, float sx, float sy);
	void translateImage(unsigned char* ipImg, unsigned char* opImg, float tx, float ty);
	int bilinearT(unsigned char* ipImg, float pPrime, float qPrime);
	void insertPiece(unsigned char* ipImg, unsigned char* opImg, char *argv[]);//unsigned char* piece,
	void setControlPoints(int triangleNum,int imgComb);
	void findSpatialCoefficients(int NCP);
	void inverseMatrix(double *ipmat, double *opmat);
	double determinantOfMat(double ipMat[6][6], float order);
	void mappcoefficients(unsigned char* ipImg, unsigned char* opImg, int imgNo);
	void spatialWarping(unsigned char* ipImg, unsigned char* opImg, char *argv[], int imgComb);
	void imageMorphing(unsigned char* ipImgStart, unsigned char* ipImgEnd, unsigned char* opImg, double alpha);
	//////////////////////////////////////////////

	//////////////texture analysis///////////////
	void filterbankFormation();
	void transformDomainConversion(unsigned char* ipImg);
	void energyComputation(int order);
	void normalizeTransformedImg();
	void avgFeatureVec();
	void kmeanAlgorithm();
	void kmeanAlgorithmReducedFeatures();
	void deleteFilterbanks();
	//////////////////////////////////////////////

	//////////////texture synthesis///////////////
	void blockBasedSynthesis(int blkRSize, int blkCSize);
	void efrosFreemanAlgo(int blkRSize, int blkCSize, int overlapWidth, float maxError, int minCutReq);
	void findSSD(unsigned char* blk, int blkSize, int r, int c, int olapWidth, float err, bool hz, bool vr, int minCutReq);
	void insertBlock(unsigned char* blk, int blkRSize, int blkCSize, int rowStart, int colStart);
	void grayScaleConversion(unsigned char* ipImg, unsigned char* opImg, int r, int c);
	/////////////////////////////////////////////

	//////////////////////////OCR////////////////
	void binaryConvertion(unsigned char* ipImg, unsigned char* opImg);
	void grayAlgo(unsigned char* ipImg);
	void trainingSet(char *lastPath, int maxItr, int extraCredit);
	void preprocessing(unsigned char* img);
	void spatialmoment(unsigned char* ipImg);
	int zeroCrossing(unsigned char* ipImg, int index, int rowORcol);
	void determineCharacter();
	/////////////////////////////////////////////
};

class patternDB
{
private:
	struct tblDB
	{
		char *pattern[4];
		int numOfPattern;
	};

	tblDB bitquad[6];
public:
	patternDB();
	~patternDB();
	
	void genPattern();
	void convert2String(char *matstr,int mat[]);
	int checkPattern(char *str);
};