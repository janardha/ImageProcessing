////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//28th September 2012
////////////////////////////////////////////////////////
#include "processImage.h"

////////////////////edge detection/////////////
void processImage::sobelOperator(int subMode, float threshold)
{
	int imageIndex;
	int rowIndex, colIndex;

	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int mask[3][3] = {1, 2, 1, 2, 0, 2, 1, 2, 1};

	int rightHandAvg_X = 0;
	int	leftHandAvg_X = 0;
	int	topLvlAvg_Y = 0;
	int	bottomLvlAvg_Y = 0;
	int thresholdValue = 0, newThresh = 0;

	unsigned char *xgradient = new unsigned char[rowSize * colSize];
	unsigned char *ygradient = new unsigned char[rowSize * colSize];

	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
			{
				mask_index_y = -1;
				imageRowMask = rowIndex + mask_index_x;
				imageColMask = colIndex + mask_index_y;
				leftHandAvg_X = leftHandAvg_X + mask[mask_index_x + 1][mask_index_y + 1] * 
					inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
			}
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
			{
				mask_index_y = 1;
				imageRowMask = rowIndex + mask_index_x;
				imageColMask = colIndex + mask_index_y;
				rightHandAvg_X = rightHandAvg_X + mask[mask_index_x + 1][mask_index_y + 1] * 
					grayImage[abs(imageRowMask)*colSize + abs(imageColMask)];
			}
			for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
			{
				mask_index_x = -1;
				imageRowMask = rowIndex + mask_index_x;
				imageColMask = colIndex + mask_index_y;
				topLvlAvg_Y = topLvlAvg_Y + mask[mask_index_x + 1][mask_index_y + 1] * 
					inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
			}
			for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
			{
				mask_index_x = 1;
				imageRowMask = rowIndex + mask_index_x;
				imageColMask = colIndex + mask_index_y;
				bottomLvlAvg_Y = bottomLvlAvg_Y + mask[mask_index_x + 1][mask_index_y + 1] * 
					grayImage[abs(imageRowMask)*colSize + abs(imageColMask)];
			}
			xgradient[rowIndex*colSize+colIndex] = (rightHandAvg_X - leftHandAvg_X)/4;
			ygradient[rowIndex*colSize+colIndex] = (topLvlAvg_Y - bottomLvlAvg_Y)/4;

			rightHandAvg_X = 0;
			leftHandAvg_X = 0;
			topLvlAvg_Y = 0;
			bottomLvlAvg_Y = 0;

			//outputImage[rowIndex*colSize+colIndex] = xgradient[rowIndex*colSize+colIndex];
			//outputImage[rowIndex*colSize+colIndex] = ygradient[rowIndex*colSize+colIndex];
			grayImage[rowIndex*colSize+colIndex] = sqrt((double)(xgradient[rowIndex*colSize+colIndex] * xgradient[rowIndex*colSize+colIndex])
				+ (ygradient[rowIndex*colSize+colIndex] * ygradient[rowIndex*colSize+colIndex]));
		}
	
	thresholdValue = edgeThresholding(threshold);

	if(subMode == 4)
	{
		for(rowIndex = 1; rowIndex < rowSize-1; rowIndex++)
			for(colIndex = 1; colIndex < colSize-1; colIndex++)
			{
				if(xgradient[rowIndex*colSize+colIndex] > ygradient[rowIndex*colSize+colIndex])
				{
					if(grayImage[rowIndex*colSize+colIndex] > grayImage[(rowIndex+1)*colSize+colIndex] &&
						grayImage[rowIndex*colSize+colIndex] > grayImage[(rowIndex-1)*colSize+colIndex] && 
						grayImage[rowIndex*colSize+colIndex] > thresholdValue)
						outputImage[rowIndex*colSize+colIndex] = 0;
					else
						outputImage[rowIndex*colSize+colIndex] = 255;
				}
				else
				{
					if(grayImage[rowIndex*colSize+colIndex] > grayImage[rowIndex*colSize+colIndex+1] &&
						grayImage[rowIndex*colSize+colIndex] > grayImage[rowIndex*colSize+colIndex-1] &&
						grayImage[rowIndex*colSize+colIndex] > thresholdValue)
						outputImage[rowIndex*colSize+colIndex] = 0;
					else
						outputImage[rowIndex*colSize+colIndex] = 255;
				}
			}

	}
	else
	{
		for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
			for(colIndex = 0; colIndex < colSize; colIndex++)
			{
				if(grayImage[rowIndex*colSize+colIndex] < thresholdValue)
					outputImage[rowIndex*colSize+colIndex] = 255;
				else
					outputImage[rowIndex*colSize+colIndex] = 0;
			}
	}

		setFilepath("../xGradMap.raw");
		imageWriter(xgradient);
		
		setFilepath("../yGradMap.raw");
		imageWriter(ygradient);

	delete (xgradient);
	delete (ygradient);
}

void processImage::logOfGaussian()
{
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int* thresholdMap = new int[rowSize*colSize];
	int* secondDerivative = new int[rowSize*colSize];
	int thresholdValue = 3;
	int mask[3][3] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
	int weightVal = 0;

	lowPassGaussianFiltering5(inputImageData, grayImage);

	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					weightVal = weightVal + mask[mask_index_x + 1][mask_index_y + 1] * 
						grayImage[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
			
				secondDerivative[rowIndex*colSize+colIndex] = weightVal/4;
			weightVal = 0;
		//	cout<<secondDerivative[rowIndex*colSize+colIndex]<<endl;

		}
//
////	thresholdValue = edgeThresholding();
//
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			if((-thresholdValue < secondDerivative[rowIndex*colSize+colIndex]) &&
				(secondDerivative[rowIndex*colSize+colIndex]< thresholdValue))
				thresholdMap[rowIndex*colSize+colIndex] = 0;
			else if((secondDerivative[rowIndex*colSize+colIndex]< -thresholdValue))
				thresholdMap[rowIndex*colSize+colIndex] = -1;
			else
				thresholdMap[rowIndex*colSize+colIndex] = 1;
		}

	for(rowIndex = 1; rowIndex < rowSize-1; rowIndex++)
		for(colIndex = 1; colIndex < colSize-1; colIndex++)
		{
			if(thresholdMap[rowIndex*colSize+colIndex] == 0)
			{
				//if the center pixel is zero then the neighbors are seen if they form (-1 0 1) pattern
				if((thresholdMap[(rowIndex-1)*colSize+colIndex] == -1 && thresholdMap[(rowIndex+1)*colSize+colIndex]== 1)||
					(thresholdMap[(rowIndex-1)*colSize+colIndex] == 1 && thresholdMap[(rowIndex+1)*colSize+colIndex]== -1)||
					(thresholdMap[rowIndex*colSize+(colIndex-1)] == -1 && thresholdMap[rowIndex*colSize+(colIndex+1)]== 1)||
					(thresholdMap[rowIndex*colSize+(colIndex-1)] == 1 && thresholdMap[rowIndex*colSize+(colIndex+1)]== -1))

					outputImage[rowIndex*colSize+colIndex] = 0;
				else
					outputImage[rowIndex*colSize+colIndex] = 255;
			}
		}
	delete thresholdMap;
	delete secondDerivative;
}
void processImage::varianceEdgeDetection(float threshold)
{
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;
	int thresholdValue;
	int tempVar;

	int mask[3][3] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	float meanValue = 0;
	float variance =0;

	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					meanValue = meanValue + inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
				meanValue = (meanValue/9);
				for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					tempVar = inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)] - meanValue;
					variance = variance + tempVar*tempVar;
					
				}
			
				grayImage[rowIndex*colSize+colIndex] = inputImageData[rowIndex*colSize+colIndex] - variance/9;
			meanValue = 0;
			variance =0;
		}
		thresholdValue = edgeThresholding(threshold);

	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			if(grayImage[rowIndex*colSize+colIndex] < thresholdValue)
				outputImage[rowIndex*colSize+colIndex] = 255;
			else
				outputImage[rowIndex*colSize+colIndex] = 0;
		}
}
int processImage::edgeThresholding(float threshold)
{
	int rowIndex, colIndex;
	int histIndex;
	float cumulativeHist[256];
	//int thresholdPercent = 90;
	int thresholdValue = 0;

	histogramGeneration(grayImage);

	cumulativeHist[0] = histogram[0];
	for(histIndex = 1; histIndex < 256; histIndex++)
		cumulativeHist[histIndex] = cumulativeHist[histIndex - 1] + histogram[histIndex];
	
	for(histIndex = 1; histIndex < 256; histIndex++)
	{
		cumulativeHist[histIndex] = cumulativeHist[histIndex] / (rowSize * colSize);
		if(cumulativeHist[histIndex]*100 <= threshold)
		{
			thresholdValue = histIndex;
		//	cout<<thresholdValue<<endl;
		}
	//	cout<<cumulativeHist[histIndex]<<endl;
	//	cout<<thresholdValue<<endl;
	}

	return thresholdValue;

}
////////////////////////////////////////////////
