////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "iostream"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "cstdlib"
#include "malloc.h"
using namespace std;

#define SHRINK	1
#define THIN	2
#define SKEL	3

#define WHITE	1
#define BLACK	2

#define PI		3.14159265

class specialFilter
{
private:
	unsigned char *inputImageData;
	unsigned char *outputImage;
	unsigned char* redMapping;
	unsigned char* blueMapping;
	unsigned char* greenMapping;
	char imagePath[_MAX_PATH];
//	char outputImagePath[_MAX_PATH];

	int rowSize;
	int colSize;
	int bytesInPixel;
	int bytesPerPixelInOutput;
	
	struct location
	{
		int x_pos;
		int y_pos;
	}loc[250];

	int radius;
	int centerRow;
	int centerCol;
private:
	FILE *inputFilePointer;
	FILE *Output_file_pointer;


public:
	//constructor
	specialFilter();

	//destructor
	~specialFilter();

public:
	unsigned char * getInputImagePointer(){return inputImageData;};
	void setInputImagePointer(unsigned char * imageptr) {inputImageData = imageptr;};
	unsigned char * getOutputImagePointer(){return outputImage;};
	void copyImagedata(unsigned char * srcptr,unsigned char * destptr); 
	char* getFilePath() {return imagePath;};
	void setFilepath(char path[]) {strcpy(imagePath,path);};
	int getRowSize() { return rowSize;};
	void setRowSize(int r) {rowSize = r;};
	int getColSize() { return colSize;};
	void setColSize(int c) {colSize = c;};
	int getBytesInPixel() { return bytesInPixel;};
	void setBytesInPixel(int b) {bytesInPixel = b;};
	void initializePtr();
	void reloadInputImageData(unsigned char* imgPtr);

	struct location* getLocations() {return loc;};
	int getRadius() {return radius;};
	int getCenterRow() {return centerRow;};
	int getCenterCol() {return centerCol;};
	void setRadius(int rad){radius = rad;};
	void setCenterRow(int r){centerRow = r;};
	void setCenterCol(int c){centerCol = c;};

public:

	unsigned char *imageReader();
	void imageWriter(unsigned char* outputFile,int size);
	void freeMemory(int mode);
	void defaultDisplayInput();

	//////////////color mapping//////////////////
	void colorExtract(char *image_path[]);
	void colorMapping(unsigned char* ipImgPtr, unsigned char* opImgPtr);
	void linearMapping(unsigned char* colorVector);
	void grainyImage(float A, int B,unsigned char* ipImgPtr, unsigned char* opImgPtr);
	void borderedImage(unsigned char* ipImgPtr, unsigned char* opImgPtr);
	void meanFiltering(const int filterOrder,unsigned char* ipImgPtr, unsigned char* opImgPtr);
	//morphological algorithms
	void ImageNegate(unsigned char* imgPtr);
	void shrinkingAlgorithm(unsigned char* ipImgPtr, unsigned char* opImgPtr);
	int holeCounter(unsigned char* imgPtr);
	void dilateImage(unsigned char* ipImgPtr, unsigned char* opImgPtr);
	void pathWays(int background);
	void gearTooth(int background, int numOfTeeth);
	void outline(unsigned char* ipImgPtr, unsigned char* opImgPtr);
	void breakLink(unsigned char* ipImgPtr, unsigned char* opImgPtr);
	void locationIndicator(int backgroundType,unsigned char* imgPtr);
	int findRadiusOFGear(unsigned char* imgPtr);
	void findToothpositions(unsigned char* imgPtr, unsigned char* opImgPtr, int NumOfTeeth,  bool displayMissingGear);
	//halftoning Algorithms
	void ditheringBayerPattern(int order);
	void ditheringBayerLikePattern(int order);
	void fourGrayLevelPattern(int order);
	void errorDiffusionfloyd();
	void errorDiffusionJarvis();
	void errorDiffusionStucki();
	void errorDiffSerpentine();
};


class patternDB
{
private:
	struct tblDB
	{
		char *pattern[32];
		int bond;
		int numOFPatterns;
		bool shrink;
		bool thin;
		bool skeletonize;
	};

	tblDB C1Table[13];
	tblDB C2TableST[12];
	tblDB C2TableK[12];

	char matrixString[10];
public:
	patternDB();
	~patternDB();
	void generateConditionalTables(); //table 14.3.1
	void generateUnconditionalTableShrinkNthin(); //table 14.3.2
	void generateUnconditionalTableSkeletonize(); //table 14.3.2
	bool checkConditionTable1(int bondNo, int mat[], int MorphType);
	bool checkConditionTable2(int bondNo, int mat[], int MorphType);
	void convert2String(char *matstr,int mat[]);
};