////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "filter.h"

void specialFilter::colorExtract(char *image_path[])
{
	int imageIndex = 0;

	unsigned char *probeImage;
	unsigned char *mappedImage;
	int value;

	setFilepath(image_path[8]);
	probeImage = imageReader();

	setFilepath(image_path[9]);
	mappedImage = imageReader();


	for(value = 0; value < 256; value++)
	{
		redMapping[value] =0;
		blueMapping[value] =0;
		greenMapping[value] = 0;
	}

	for(imageIndex = 0; imageIndex < rowSize*colSize*3;)
	{
		
		redMapping[probeImage[imageIndex]] = mappedImage[imageIndex++];
		greenMapping[probeImage[imageIndex]] = mappedImage[imageIndex++];
		blueMapping[probeImage[imageIndex]] = mappedImage[imageIndex++];
	}

	setFilepath("../redCoarseMap.dat");
	imageWriter(redMapping,256);

	setFilepath("../blueCoarseMap.dat");
	imageWriter(blueMapping,256);
	
	setFilepath("../greenCoarseMap.dat");
	imageWriter(greenMapping,256);

	linearMapping(redMapping);
	linearMapping(blueMapping);
	linearMapping(greenMapping);

	setFilepath("../redFineMap.dat");
	imageWriter(redMapping,256);

	setFilepath("../blueFineMap.dat");
	imageWriter(blueMapping,256);
	
	setFilepath("../greenFineMap.dat");
	imageWriter(greenMapping,256);
	
	delete probeImage;
	delete mappedImage;
}

void specialFilter::linearMapping(unsigned char* colorVector)
{
	int index;
	int lowerLimit=0, higherLimit=0;
	int lowerIndex = 0, higherIndex = 0;
	int temp_index;



	for(index = 1; index < 256; index++)
	{
		if(colorVector[index]>0)
		{
			lowerIndex = higherIndex+1;
			higherIndex = index;

			lowerLimit = higherLimit;
			higherLimit = colorVector[index];

			temp_index = lowerIndex;
			while((lowerIndex != higherIndex))
			{
				if(lowerLimit == 255 || higherLimit == 255)
				{
					colorVector[lowerIndex] = 255;
				}
				else
				{
					colorVector[lowerIndex] = lowerLimit + (lowerIndex - temp_index)* 
						abs(higherLimit - lowerLimit)/(higherIndex - temp_index);
					temp_index = lowerIndex;
				}
				lowerIndex++;
			}
		}
		
	}
	if(higherIndex < 255)
	{
		while(higherIndex < 256)
		{
			colorVector[higherIndex+1] = colorVector[higherIndex];
			higherIndex++;
		}
	}
}

void specialFilter::colorMapping(unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	int imageIndex;

	for(imageIndex = 0;imageIndex < rowSize*colSize*3;)
	{
		opImgPtr[imageIndex] = redMapping[ipImgPtr[imageIndex++]];
		opImgPtr[imageIndex] = greenMapping[ipImgPtr[imageIndex++]];
		opImgPtr[imageIndex] = blueMapping[ipImgPtr[imageIndex++]];
	}

	//setFilepath("../output.raw");
	//imageWriter(outputImage,rowSize*colSize*3);

}
void specialFilter::grainyImage(float A, int B,unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	int imageIndex;

	unsigned char* grain;
	int* grainOverlimit = new int[rowSize*colSize*3]; 
	int maxRVal =0, maxBVal =0, maxGVal = 0;
	int minRVal =0, minBVal =0, minGVal = 0;
	
	grain = imageReader();

	for(imageIndex = 0; imageIndex < rowSize*colSize*3; imageIndex++)
	{
		if(inputImageData[imageIndex] > 2*B)
			grainOverlimit[imageIndex] = ipImgPtr[imageIndex]+ A * grain[imageIndex]+B;
			/*if(maxVal < grainOverlimit[imageIndex])
				maxVal = grainOverlimit[imageIndex];
			if(minVal > grainOverlimit[imageIndex])
				minVal = grainOverlimit[imageIndex];*/
		else
			grainOverlimit[imageIndex] = inputImageData[imageIndex];
	}
	for(imageIndex = 0; imageIndex < rowSize*colSize; imageIndex++)
	{
		if(maxRVal < grainOverlimit[3*imageIndex])
			maxRVal = grainOverlimit[3*imageIndex];
		if(minRVal > grainOverlimit[3*imageIndex])
			minRVal = grainOverlimit[3*imageIndex];
	
		if(maxGVal < grainOverlimit[3*imageIndex + 1])
			maxGVal = grainOverlimit[3*imageIndex + 1];
		if(minGVal > grainOverlimit[3*imageIndex + 1])
			minGVal = grainOverlimit[3*imageIndex + 1];

		if(maxBVal < grainOverlimit[3*imageIndex + 2])
			maxBVal = grainOverlimit[3*imageIndex + 2];
		if(minBVal > grainOverlimit[3*imageIndex + 2])
			minBVal = grainOverlimit[3*imageIndex + 2];
	}

	cout<<maxRVal<<endl;
	cout<<minRVal<<endl;
	cout<<maxGVal<<endl;
	cout<<minGVal<<endl;
	cout<<maxBVal<<endl;
	cout<<minBVal<<endl;
	for(imageIndex = 0; imageIndex < rowSize*colSize; imageIndex++)
	{
		opImgPtr[3*imageIndex] = (unsigned char)(grainOverlimit[3*imageIndex]*(255-0)/(maxRVal - minRVal));
		opImgPtr[3*imageIndex+1] = (unsigned char)grainOverlimit[3*imageIndex+1]*(255-0)/(maxGVal - minGVal);
		opImgPtr[3*imageIndex+2] = (unsigned char)grainOverlimit[3*imageIndex+2]*(255-0)/(maxBVal - minBVal);
	}

	delete grain;
	delete grainOverlimit;
}
void specialFilter::borderedImage(unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	int imageIndex;

	unsigned char* border;
	
	border = imageReader();

	for(imageIndex = 0; imageIndex < rowSize*colSize*3; imageIndex++)
	{
		if(border[imageIndex] >200)
			opImgPtr[imageIndex] = 255;
		else
			opImgPtr[imageIndex] = ipImgPtr[imageIndex];
	}
	delete border;
}

void specialFilter::meanFiltering(const int filterOrder,unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	/*The window is made to move along the row. To incorporate window at the boundary, reflection method is used.
	The weighted values are added in a loop and output imag is updted for every row and column*/

	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int* mask  = new int[filterOrder*filterOrder];
	int weightedValue[3] = {0,0,0};

	for(mask_index_x = 0; mask_index_x<filterOrder; mask_index_x++)
		for(mask_index_y = 0; mask_index_y<filterOrder; mask_index_y++)
			mask[mask_index_x*filterOrder+mask_index_y] = 1;


	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -filterOrder/2; mask_index_x < filterOrder/2; mask_index_x++)
				for(mask_index_y = -filterOrder/2; mask_index_y < filterOrder/2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					
					weightedValue[0] = weightedValue[0] + ipImgPtr[3*(abs(imageRowMask)*colSize + abs(imageColMask))];
					weightedValue[1] = weightedValue[1] + ipImgPtr[3*(abs(imageRowMask)*colSize + abs(imageColMask))+1];
					weightedValue[2] = weightedValue[2] + ipImgPtr[3*(abs(imageRowMask)*colSize + abs(imageColMask))+2];
				}
			//	cout<<"in here"<<endl;
				if(!(colIndex > 50 && colIndex < 128 && rowIndex > 50 && rowIndex < 188))
				{
					opImgPtr[3*(rowIndex*colSize+colIndex)] = (weightedValue[0]/(filterOrder*filterOrder));
					opImgPtr[3*(rowIndex*colSize+colIndex)+1] = (weightedValue[1]/(filterOrder*filterOrder));
					opImgPtr[3*(rowIndex*colSize+colIndex)+2] = (weightedValue[2]/(filterOrder*filterOrder));
				}
				else
				{
					opImgPtr[3*(rowIndex*colSize+colIndex)] = inputImageData[3*(rowIndex*colSize+colIndex)];
					opImgPtr[3*(rowIndex*colSize+colIndex)+1] = inputImageData[3*(rowIndex*colSize+colIndex)+1];
					opImgPtr[3*(rowIndex*colSize+colIndex)+2] = inputImageData[3*(rowIndex*colSize+colIndex)+2];
				}
			weightedValue[0] = 0;
			weightedValue[1] = 0;
			weightedValue[2] = 0;
		}
	cout<<"mean filtering done"<<endl;
}