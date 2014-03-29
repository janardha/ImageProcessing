////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "filter.h"

void main(int arc, char *argv[])
{
	
	specialFilter filterIns;
	int modeSelect, subMode;
	int width, height;
	int itr, maxItr;
	unsigned char *modifedImage;
	
	modeSelect = atoi(argv[1]);
	subMode = atoi(argv[2]);
	filterIns.setFilepath(argv[3]);
	filterIns.setRowSize(atoi(argv[5]));
	filterIns.setColSize(atoi(argv[6]));
	filterIns.setBytesInPixel(atoi(argv[7]));
	
	filterIns.setInputImagePointer(filterIns.imageReader());
	filterIns.initializePtr();

	switch(modeSelect)
	{
	case 1:
		if(subMode == 1)
		{
			filterIns.colorExtract(argv);
			filterIns.colorMapping(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 2)
		{
			filterIns.setFilepath(argv[8]);
			filterIns.grainyImage(atof(argv[9]),atoi(argv[10]),filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 3)
		{
			filterIns.setFilepath(argv[8]);
			filterIns.borderedImage(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 4)
		{
			filterIns.meanFiltering(7,filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		break;
	case 2:
		if(subMode == 1)
		{
			//Calculate holes and pathways
			//argument 8 indicates whether the background is white of black
			if(strcmp(argv[8],"white") == 0)
				filterIns.pathWays(WHITE);
			else
				filterIns.pathWays(BLACK);
			
		}
		else if(subMode == 2)
		{
			//Calculate and display of missing gear position
			//argument 8 indicates whether the background is white of black
			if(strcmp(argv[8],"white") == 0)
				filterIns.gearTooth(WHITE, atoi(argv[9]));
			else
				filterIns.gearTooth(BLACK, atoi(argv[9]));
			
		}
		else if(subMode == 3)
		{
			//argument 8 indicates whether the background is white of black
			//argument 9 gives the number of iterations to be done to obtain the result
			maxItr = atoi(argv[9]);
			if(strcmp(argv[8],"white") == 0)
			{
				for(itr =0; itr < maxItr;itr++)
				{
					filterIns.dilateImage(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
					filterIns.reloadInputImageData(filterIns.getOutputImagePointer());
				}
			}
			else
			{
				filterIns.ImageNegate(filterIns.getInputImagePointer());
				for(itr =0; itr < maxItr;itr++)
				{
					filterIns.dilateImage(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
					filterIns.reloadInputImageData(filterIns.getOutputImagePointer());
				}
				filterIns.ImageNegate(filterIns.getOutputImagePointer());
			}
		}
		else if(subMode == 4)
		{
			int count = filterIns.holeCounter(filterIns.getInputImagePointer());
			filterIns.copyImagedata(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 5)
		{
			maxItr = atoi(argv[9]);
			if(strcmp(argv[8],"white") == 0)
			{
				filterIns.ImageNegate(filterIns.getInputImagePointer());
				for(itr =0; itr < maxItr;itr++)
				{
					filterIns.shrinkingAlgorithm(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
					filterIns.reloadInputImageData(filterIns.getOutputImagePointer());
				}
				filterIns.ImageNegate(filterIns.getOutputImagePointer());
			}
			else
			{
				for(itr =0; itr < maxItr;itr++)
				{
					filterIns.shrinkingAlgorithm(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
					filterIns.reloadInputImageData(filterIns.getOutputImagePointer());
				}
			}
		}
		else if(subMode == 6)
		{
			filterIns.ImageNegate(filterIns.getInputImagePointer());
			filterIns.copyImagedata(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 7)
		{
			if(strcmp(argv[8],"white") == 0)
				filterIns.locationIndicator(WHITE,filterIns.getInputImagePointer());
			else
				filterIns.locationIndicator(BLACK,filterIns.getInputImagePointer());
			filterIns.copyImagedata(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 8)
		{
			//argument 8 and 9 give the location of the center pixel
			filterIns.setCenterRow(atoi(argv[8]));
			filterIns.setCenterCol(atoi(argv[9]));
			filterIns.findRadiusOFGear(filterIns.getInputImagePointer());
			filterIns.copyImagedata(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
		}
		else if(subMode == 9)
		{
			//arguemnt 8 gives the radius
			//argument 9 and 10 give the center position
			//the argument 11 gives number of teeth present
			//display only the gear present
			filterIns.setRadius(atoi(argv[8]));
			filterIns.setCenterRow(atoi(argv[9]));
			filterIns.setCenterCol(atoi(argv[10]));
			
			filterIns.findToothpositions(filterIns.getInputImagePointer(),filterIns.getInputImagePointer(),atoi(argv[11]), false);
			
		}
		else if(subMode == 10)
		{
			//display the missing gear
			filterIns.setRadius(atoi(argv[8]));
			filterIns.setCenterRow(atoi(argv[9]));
			filterIns.setCenterCol(atoi(argv[10]));

			filterIns.findToothpositions(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer(),atoi(argv[11]), true);
			
		}
		else if(subMode == 11)
		{
			filterIns.ImageNegate(filterIns.getInputImagePointer());
			filterIns.outline(filterIns.getInputImagePointer(),filterIns.getOutputImagePointer());
			filterIns.ImageNegate(filterIns.getOutputImagePointer());
		}
		
		break;
	case 3:
		if(subMode == 1)
		{
			//the bayer pattern is given by arg 9 set to 1
			//the other method is selected if the any other value.
			if(atoi(argv[9]) == 1)
				filterIns.ditheringBayerPattern(atoi(argv[8]));//bayer matrix
			else
				filterIns.ditheringBayerLikePattern(atoi(argv[8]));//bayer like matrix
		}
		else if(subMode == 2)
		{
			if(atoi(argv[8]) == 1)
				filterIns.errorDiffusionfloyd();
			else if(atoi(argv[8]) == 2)
				filterIns.errorDiffusionJarvis();
			else
				filterIns.errorDiffusionStucki();
		}
		else if(subMode == 3)
		{
			filterIns.fourGrayLevelPattern(atoi(argv[8]));
		}
		else if(subMode == 4)
		{
			filterIns.errorDiffSerpentine();
		}
		break;
	
	
	default:
		filterIns.defaultDisplayInput();
		break;
	}

	filterIns.setFilepath(argv[4]);
	cout<<"at the output"<<endl;
	width = filterIns.getColSize();
	height = filterIns.getRowSize();
	filterIns.imageWriter(filterIns.getOutputImagePointer(), width*height*filterIns.getBytesInPixel());
	filterIns.freeMemory(modeSelect);

	//printf("%d\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t\n", arc, argv[0],argv[1],argv[2], argv[3], 
	//	argv[4], argv[5], argv[6]);
	printf("INside main function\n");

	getchar();
}
