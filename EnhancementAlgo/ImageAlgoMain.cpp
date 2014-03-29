////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//28th September 2012
////////////////////////////////////////////////////////
#include "processImage.h"

void main(int arc, char *argv[])
{
	
	processImage instance_1;
	int modeSelect;
	int subMode;
	unsigned char *modifedImage;
	
	modeSelect = atoi(argv[1]);
	subMode = atoi(argv[2]);
	instance_1.setFilepath(argv[3]);
	instance_1.setRowSize(atoi(argv[5]));
	instance_1.setColSize(atoi(argv[6]));
	instance_1.setBytesInPixel(atoi(argv[7]));
	
	instance_1.setInputImagePointer(instance_1.imageReader());
	instance_1.initializePtr();
	modifedImage = instance_1.getModifiedImagePointer();

	switch(modeSelect)
	{
	case 1:
		if(subMode == 1)
			instance_1.grayScaleConverter_avg();
		else if(subMode == 2)
			instance_1.grayScaleConverter_luminosity();
		else 
		{
			instance_1.grayScaleConverter_luminosity();
			if(subMode ==3)
				instance_1.linearFiltering();
			else if(subMode == 4)
				instance_1.squareRootFiltering();
			else if(subMode == 5)
				instance_1.cumulativeHistogramEqualization();
			else if(subMode == 6)
				instance_1.digitalHistogramEqulization();
			else if(subMode == 7)
				instance_1.localContrastEnhancement();
		}

		break;
	case 2:
		if(subMode == 1)
		{
			instance_1.meanFiltering(atoi(argv[8]));
		}
		else if(subMode == 2)
			if(atoi(argv[8]) == 3)
				instance_1.medianFiltering3();
			else
				instance_1.medianFiltering5();
		else if(subMode == 3)
		{
			if(atoi(argv[8]) == 10)
				instance_1.lowPassFilteringWt10();
			else
				instance_1.lowPassFilteringWt16();
		}
		else if(subMode == 4)
		{
			if(atoi(argv[8]) == 3)
				instance_1.lowPassGaussianFiltering3(instance_1.getInputImagePointer(), modifedImage);
			else
				instance_1.lowPassGaussianFiltering5(instance_1.getInputImagePointer(), modifedImage);

			instance_1.setOutputImagePointer(modifedImage);
		}
		else if(subMode == 5)
			instance_1.outlierFiltering(atof(argv[8]));
		else if(subMode == 6)
			instance_1.SSIM(argv);
		break;
	case 3:
		if(subMode == 1)
			instance_1.sobelOperator(subMode, atof(argv[8]));
		else if(subMode == 2)
			instance_1.varianceEdgeDetection(atof(argv[8]));
		else if(subMode == 3)
			instance_1.logOfGaussian();
		else if(subMode == 4)
			instance_1.sobelOperator(subMode,atof(argv[8]));
		break;
	default:
		instance_1.defaultDisplayInput();
		break;
	}

	instance_1.setFilepath(argv[4]);
	cout<<"at the output"<<endl;
	instance_1.imageWriter(instance_1.getOutputImagePointer());
	instance_1.freeMemory(modeSelect);

	printf("%d\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t\n", arc, argv[0],argv[1],argv[2], argv[3], 
		argv[4], argv[5], argv[6]);
	printf("INside main function\n");

	getchar();
}
