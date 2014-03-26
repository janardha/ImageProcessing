////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//28th September 2012
////////////////////////////////////////////////////////

#include "processImage.h"

void processImage::meanFiltering(const int filterOrder)
{
	/*The window is made to move along the row. To incorporate window at the boundary, reflection method is used.
	The weighted values are added in a loop and output imag is updted for every row and column*/

	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int* mask  = new int[filterOrder*filterOrder];
	int weightedValue = 0;

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
					
					weightedValue = weightedValue + mask[(mask_index_x+filterOrder/2)*filterOrder+(mask_index_y+filterOrder/2)] * 
						inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
			//	cout<<"in here"<<endl;
				outputImage[rowIndex*colSize+colIndex] = (weightedValue/(filterOrder*filterOrder));
			weightedValue = 0;
		}
	cout<<"mean filtering done"<<endl;
}
void processImage::medianFiltering3()
{
	/*The window is made to move along the row. To incorporate window at the boundary, reflection method is used.
	The weighted values are added in a loop and output imag is updted for every row and column*/

	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int mask[3][3] = {0,1,0,1,1,1,0,1,0};
//	int mask[3][3] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int weightedValue[9], wtIndex = 0;

	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					if(mask[mask_index_x + 1][mask_index_y + 1] !=0)
					{
						weightedValue[wtIndex] = inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
						wtIndex++;
					}
				}
			
			sortcoefficients(weightedValue,wtIndex);
			outputImage[rowIndex*colSize+colIndex] = weightedValue[3];
			wtIndex = 0;
			
		}
	}

}

void processImage::medianFiltering5()
{
	/*The window is made to move along the row. To incorporate window at the boundary, reflection method is used.
	The weighted values are added in a loop and output imag is updted for every row and column*/

	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int mask[5][5] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0};
//	int mask[5][5] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int weightedValue[9], wtIndex = 0;

	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					if(mask[mask_index_x + 2][mask_index_y + 2] !=0)
					{
						weightedValue[wtIndex] = inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
						wtIndex++;
					}
				}
			
			sortcoefficients(weightedValue,wtIndex);
			outputImage[rowIndex*colSize+colIndex] = weightedValue[4];
			wtIndex = 0;
			
		}
		//cout<<"row index "<<rowIndex<<endl;
	}

}

void processImage::lowPassFilteringWt10()
{
	
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int Weight = 10;
	int weightedValue = 0;
	int	mask[3][3] = {1, 1, 1, 1, 2, 1, 1, 1, 1};
	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					weightedValue = weightedValue + mask[mask_index_x + 1][mask_index_y + 1] * 
						inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
			
				outputImage[rowIndex*colSize+colIndex] = (weightedValue/Weight);
			weightedValue = 0;
		}
}
void processImage::lowPassFilteringWt16()
{
	
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;
	int Weight = 16;
	int weightedValue = 0;
	int	mask[3][3] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					weightedValue = weightedValue + mask[mask_index_x + 1][mask_index_y + 1] * 
						inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
			
				outputImage[rowIndex*colSize+colIndex] = (weightedValue/Weight);
			weightedValue = 0;
		}
}

void processImage::lowPassGaussianFiltering3(unsigned char* inputImagePtr, unsigned char* outputImagePtr)
{
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	float mask[3][3];
	float delta= 0.3536;//5/(6*sqrt(2.0));
	int weightedValue = 0;
	float normalizingVal = 0;

	for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
		for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
		{
			mask[mask_index_x + 1][mask_index_y + 1] = 
				exp(-1*(mask_index_x*mask_index_x + mask_index_y*mask_index_y)/(2*delta* delta));
			normalizingVal = normalizingVal + mask[mask_index_x + 1][mask_index_y + 1];
			//cout<<mask[mask_index_x + 2][mask_index_y + 2]<<endl;
		}

	for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
		for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
		{
			mask[mask_index_x + 1][mask_index_y + 1] = mask[mask_index_x + 1][mask_index_y + 1]/normalizingVal;
			cout<<mask[mask_index_x + 1][mask_index_y + 1]<<endl;  
		}
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					weightedValue = weightedValue + mask[mask_index_x + 1][mask_index_y + 1] * 
						inputImagePtr[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
			
				outputImagePtr[rowIndex*colSize+colIndex] = (weightedValue);
			weightedValue = 0;
		}

}
void processImage::lowPassGaussianFiltering5(unsigned char* inputImagePtr, unsigned char* outputImagePtr)
{
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	float mask[5][5];
	float delta= 0.58;//5/(6*sqrt(2.0));
	int weightedValue = 0;
	float normalizingVal = 0;

	for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
		for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
		{
			mask[mask_index_x + 2][mask_index_y + 2] = 
				exp(-1*(mask_index_x*mask_index_x + mask_index_y*mask_index_y)/(2*delta* delta));
			normalizingVal = normalizingVal + mask[mask_index_x + 2][mask_index_y + 2];
			//cout<<mask[mask_index_x + 2][mask_index_y + 2]<<endl;
		}

	for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
		for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
		{
			mask[mask_index_x + 2][mask_index_y + 2] = mask[mask_index_x + 2][mask_index_y + 2]/normalizingVal;
			cout<<mask[mask_index_x + 2][mask_index_y + 2]<<endl;  
		}
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{ 
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					weightedValue = weightedValue + mask[mask_index_x + 2][mask_index_y + 2] * 
						inputImagePtr[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
				//the center of the pixel is loaded with the weighted sum of the image points 
				//around the pixel
				outputImagePtr[rowIndex*colSize+colIndex] = (weightedValue);
			weightedValue = 0;
		}

}

void processImage::outlierFiltering(float threshold)
{
	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;

	int mask[3][3] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
	int weightedValue = 0;

	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			for(mask_index_x = -1; mask_index_x < 2; mask_index_x++)
				for(mask_index_y = -1; mask_index_y < 2; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					
					weightedValue = weightedValue + mask[mask_index_x + 1][mask_index_y + 1] * 
						inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
				if((inputImageData[rowIndex*colSize+colIndex] - (weightedValue/8)) > threshold)
					outputImage[rowIndex*colSize+colIndex] = (weightedValue/8);
				else
					outputImage[rowIndex*colSize+colIndex] = inputImageData[rowIndex*colSize+colIndex];
			weightedValue = 0;
		}
}

void processImage::SSIM(char *image_path[])
{
	int image_index;
	float inputMean = 0, outputMean = 0;
	float inputVariance = 0, outputVariance = 0, tempVar = 0;
	float covariance = 0;

	int maxIntensity = 255;
	float constant1 = pow((0.01 * maxIntensity), 2);
	float constant2 = pow((0.03 * maxIntensity), 2);

	int rowIndex, colIndex;
	int mask_index_x, mask_index_y;
	int imageRowMask, imageColMask;
	float max = 0, min = 0;
	
	float* ssimMap = new float[rowSize * colSize];

	int mask[5][5] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int totalWt = 25;
	
	float ssim_value;
	float mse_value = 0;
	float meanSquareError = 0;
	float PSNR = 0;
	unsigned char *distortedImage;

	cout<<constant1<<endl;
	cout<<constant2<<endl;

	setFilepath(image_path[8]);
	
	distortedImage = imageReader();
	
	//set path to write ssim map to file
	setFilepath("../ssimMap.raw");
	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			//mean value within the window is calculated by adding all the values 
			//in the window and divided by the square of window size
			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{
					
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					inputMean = inputMean + inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)];
					//cout<<"read successful"<<endl;
				}
			inputMean = inputMean/totalWt;

			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					tempVar = inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)] - inputMean;
					inputVariance = inputVariance + tempVar*tempVar;
				}
			inputVariance = inputVariance/totalWt;

			//cout<<inputMean<<endl;
			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					outputMean = outputMean + mask[mask_index_x + 2][mask_index_y + 2] * 
						distortedImage[abs(imageRowMask)*colSize + abs(imageColMask)];
				}
			outputMean = outputMean/totalWt;

			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					tempVar = distortedImage[abs(imageRowMask)*colSize + abs(imageColMask)] - outputMean;
					outputVariance = outputVariance + tempVar*tempVar;
				}
			outputVariance = outputVariance/totalWt;

			for(mask_index_x = -2; mask_index_x < 3; mask_index_x++)
				for(mask_index_y = -2; mask_index_y < 3; mask_index_y++)
				{
					imageRowMask = rowIndex + mask_index_x;
					imageColMask = colIndex + mask_index_y;
					covariance = covariance +  
						(inputImageData[abs(imageRowMask)*colSize + abs(imageColMask)] - inputMean) *
						(distortedImage[abs(imageRowMask)*colSize + abs(imageColMask)] - outputMean);
				}
			covariance = covariance / 25;
		
			ssim_value = (2*inputMean * outputMean + constant1)*(2*covariance + constant2) /
				((pow(inputMean,2)+pow(outputMean,2)+ constant1)*(inputVariance + outputVariance+ constant2));
	
			//mapping -1 to +1 ----> 0 to 255
			ssimMap[rowIndex*colSize + colIndex] = ssim_value;
			outputImage[rowIndex*colSize + colIndex] = (255/2) * (ssim_value+1);

			//all the looped variables are set to zero before next iteration
			inputMean = 0;
			inputVariance = 0;
			outputMean = 0;
			outputVariance = 0;
			covariance = 0;
		}
		ssim_value = 0;
		///////averaging method////////////////
		for(rowIndex = -rowSize/2; rowIndex < rowSize/2; rowIndex++)
			for(colIndex = -colSize/2; colIndex < colSize/2; colIndex++)
			{
				if(((-rowSize/8) < rowIndex) && (rowIndex < (rowSize/8)) &&
					((-colSize/8) < colIndex) && (colIndex < (colSize/8)))
					ssim_value = ssim_value + 4 * ssimMap[(rowIndex+rowSize/2)*colSize + (colIndex+colSize/2)];
				else
					ssim_value = ssim_value + ssimMap[(rowIndex+rowSize/2)*colSize + (colIndex+colSize/2)];
			}
		ssim_value = ssim_value/(rowSize * colSize);

		cout<<ssim_value<<endl;
		imageWriter(outputImage);

		//set path for writing mse map into file
		setFilepath("../mseMap.raw");
		meanSquareError = 0;
		for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		{
			for(colIndex = 0; colIndex < colSize; colIndex++)
			{
				
				mse_value = (inputImageData[rowIndex*colSize + colIndex] * inputImageData[rowIndex*colSize + colIndex]) -
					(distortedImage[rowIndex*colSize + colIndex] * distortedImage[rowIndex*colSize + colIndex]);
				meanSquareError = meanSquareError + mse_value;
				
				//mapping -1 to +1   ------------> 0 to 255
				outputImage[rowIndex*colSize + colIndex] = (255/2) * (mse_value+1);
			}
		}
		imageWriter(outputImage);
		meanSquareError = abs(meanSquareError)/(rowSize * colSize);
	
		PSNR = 10 * log10(255*255/meanSquareError);

		cout<<"PSNR is "<<PSNR<<endl;
}

void processImage::sortcoefficients(int *vectorCoefficients, int vectorLength)
{
	int sortLen, sortItr;
	int tempStorage;

	for(sortLen = 0; sortLen < vectorLength; sortLen++)
		for(sortItr = sortLen; sortItr < vectorLength; sortItr++)
		{
			if(vectorCoefficients[sortLen] > vectorCoefficients[sortItr])
			{
				tempStorage = vectorCoefficients[sortLen];
				vectorCoefficients[sortItr] = vectorCoefficients[sortLen];
				vectorCoefficients[sortLen] = tempStorage;
			}
		}

}


