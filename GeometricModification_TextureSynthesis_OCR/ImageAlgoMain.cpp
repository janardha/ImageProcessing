////////////////////////////////////////////////////////
//Rajani Janardhana
//5710-8838-33
//janardha@usc.edu
//EE 569 Homework #2
//19th October 2012
////////////////////////////////////////////////////////
#include "modification.h"

void main(int arc, char *argv[])
{
	
	modifyImage modifier;
	int modeSelect, subMode;
	int width, height, numBytes;
	unsigned char *modifedImage;
	
	int zcr =0;
	float theta = 0;

	modeSelect = atoi(argv[1]);
	subMode = atoi(argv[2]);
	modifier.setFilepath(argv[3]);
	modifier.setIpRowSize(atoi(argv[5]));
	modifier.setIpColSize(atoi(argv[6]));
	modifier.setBytesInPixel(atoi(argv[7]));
	
	modifier.setInputImagePointer(modifier.imageReader());
	modifier.initializePtr();

	switch(modeSelect)
	{
	case 1:
		if(subMode == 1)
		{
			modifier.insertPiece(modifier.getInputImagePointer(), modifier.getOutputImagePointer(),argv);
		}
		else if(subMode == 2)
		{
			if(strstr(argv[8],"romney") != NULL)
				modifier.spatialWarping(modifier.getInputImagePointer(), modifier.getOutputImagePointer(),argv, 0);
			else if(strstr(argv[8],"obama") != NULL)
				modifier.spatialWarping(modifier.getInputImagePointer(), modifier.getOutputImagePointer(),argv, 1);
			else
				modifier.spatialWarping(modifier.getInputImagePointer(), modifier.getOutputImagePointer(),argv, 2);
		}
		else if(subMode == 3)
		{
			modifier.setFilepath(argv[8]);
			modifier.setModImagePointer(modifier.imageReader());
			modifier.imageMorphing(modifier.getInputImagePointer(),modifier.getModImagePointer(),
					modifier.getOutputImagePointer(),atof(argv[9]));
		}
		else if(subMode == 4)
		{
			
		}
		else if(subMode == 5)
		{
		}
		
		break;
	case 2:
		if(subMode == 1)
		{
			modifier.filterbankFormation();
			modifier.transformDomainConversion(modifier.getInputImagePointer());
			modifier.energyComputation(atoi(argv[8]));
			modifier.normalizeTransformedImg();
			if(atoi(argv[9]))
				modifier.kmeanAlgorithm();
			else
				modifier.kmeanAlgorithmReducedFeatures();
			modifier.deleteFilterbanks();
		}
		else if(subMode == 2)
		{
			modifier.setOpRowSize(2*modifier.getIpRowSize());
			modifier.setOpColSize(2*modifier.getIpColSize());
			modifier.blockBasedSynthesis(atoi(argv[8]), atoi(argv[8]));
		}
		else if(subMode == 3)
		{
			modifier.setOpRowSize(2*modifier.getIpRowSize());
			modifier.setOpColSize(2*modifier.getIpColSize());
			modifier.efrosFreemanAlgo(atoi(argv[8]),atoi(argv[8]),atoi(argv[8])/6,0.1, atoi(argv[9]));
		}
		break;
	case 3:
		if(subMode == 1)
		{
			modifier.trainingSet(argv[9], atoi(argv[8]), atoi(argv[10]));
		}
		break;
	default:
		modifier.defaultDisplayInput();
		break;
	}

	modifier.setFilepath(argv[4]);
	cout<<"at the output"<<endl;
	width = modifier.getOpColSize();
	height = modifier.getOpRowSize();
	numBytes = modifier.getBytesInPixelOut();
	modifier.imageWriter(modifier.getOutputImagePointer(), width*height*numBytes);
	modifier.freeMemory(modeSelect);

	//printf("%d\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t\n", arc, argv[0],argv[1],argv[2], argv[3], 
	//	argv[4], argv[5], argv[6]);
	printf("INside main function\n");

	getchar();
}
