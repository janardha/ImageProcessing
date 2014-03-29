////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "filter.h"

void specialFilter::ditheringBayerPattern(int order)
{
	int ditherIndexX, ditherIndexY;
	int rowIndex, colIndex;
	int* dither = new int[order*order];
	float* threshold = new float[order*order];

	cout<<"In here"<<endl;
	if(order == 2)
	{
		int mat[2][2] = {0,2,3,1};
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
			
	}
	else if(order == 8)
	{
		int mat[8][8] = {	   0, 32,  8, 40,  2, 34, 10, 42,
							  48, 16, 56, 24, 50, 18, 58, 26,
							  12, 44, 04, 36, 14, 46, 06, 38,
							  60, 28, 52, 20, 62, 30, 54, 22,
							  03, 35, 11, 43, 01, 33,  9, 41,
							  51, 19, 59, 27, 49, 17, 57, 25,
							  15, 47, 07, 39, 13, 45, 05, 37,
							  63, 31, 55, 23, 61, 29, 53, 21};
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
	}
	else
	{
		int mat[4][4] = {0,  8,  2, 10,
							12,  4, 14,  6,
							 3, 11,  1,  9,
							15,  7, 13,  5};
		
		
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
	}

	
	for(rowIndex = 0; rowIndex < order; rowIndex++)
	{
		for(colIndex = 0; colIndex < order; colIndex++)
		{
			//cout<<" "<< dither[rowIndex*order + colIndex];
			threshold[rowIndex*order + colIndex] = (dither[rowIndex*order + colIndex] + 0.5) * 255 / (order * order);
			cout<<" "<<threshold[rowIndex*order + colIndex];
		}
		cout<<endl;
	}

		

	for(rowIndex = 0; rowIndex < rowSize; rowIndex = rowIndex+order)
	{
		for(colIndex = 0; colIndex < colSize; colIndex = colIndex+order)
		{
			ditherIndexX = rowIndex % order;
			ditherIndexY = colIndex % order;

			if(inputImageData[rowIndex*colSize + colIndex] > threshold[ditherIndexX*order + ditherIndexY])
			{
				outputImage[rowIndex*colSize + colIndex] = 255;
			}
			else
			{
				outputImage[rowIndex*colSize + colIndex] = 0;
			}

		}
		//cout<<endl;
	}
cout<<"reinit"<<endl;
}
void specialFilter::ditheringBayerLikePattern(int order)
{
	int ditherIndexX, ditherIndexY;
	int rowIndex, colIndex;
	int* dither = new int[order*order];
	float* threshold = new float[order*order];

	cout<<"In here"<<endl;
	if(order == 8)
	{
		int mat[8][8] = {60, 42, 43, 44, 45, 46, 47, 61,
						 41, 33, 24, 25, 26, 27, 34, 48,
						 40, 23, 14, 10, 11, 15, 28, 49,
						 39, 22,  9,  3,  0,  4, 29, 50,
						 38, 21,  8,  2,  1,  5, 30, 51,
						 37, 20, 13,  7,  6, 12, 31, 52,
						 36, 32, 19, 18, 17, 16, 35, 53,
						 63, 59, 58, 57, 56, 55, 54, 62};
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
	}
	else
	{
		int mat[4][4] = {14, 10, 11, 15,
							  9,  3,  0,  4,
							  8,  2,  1,  5,
							 13,  7,  6, 12};
		
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
	}

	
	for(rowIndex = 0; rowIndex < order; rowIndex++)
	{
		for(colIndex = 0; colIndex < order; colIndex++)
		{
			//cout<<" "<< dither[rowIndex*order + colIndex];
			threshold[rowIndex*order + colIndex] = (dither[rowIndex*order + colIndex] + 0.5) * 255 / (order * order);
			cout<<" "<<threshold[rowIndex*order + colIndex];
		}
		cout<<endl;
	}

		

	for(rowIndex = 0; rowIndex < rowSize; rowIndex = rowIndex+order)
	{
		for(colIndex = 0; colIndex < colSize; colIndex = colIndex+order)
		{
			ditherIndexX = rowIndex % order;
			ditherIndexY = colIndex % order;

			if(inputImageData[rowIndex*colSize + colIndex] > threshold[ditherIndexX*order + ditherIndexY])
			{
				outputImage[rowIndex*colSize + colIndex] = 255;
			}
			else
			{
				outputImage[rowIndex*colSize + colIndex] = 0;
			}

		}
		//cout<<endl;
	}
cout<<"reinit"<<endl;
}
void specialFilter::fourGrayLevelPattern(int order)
{
	
	int ditherIndexX, ditherIndexY;
	int rowIndex, colIndex;
	int* dither = new int[order*order];
	float* threshold = new float[order*order];

	float threshVal;
	cout<<"In here"<<endl;
	if(order == 2)
	{
		int mat[2][2] = {0,2,3,1};
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
	}
	else
	{
		/*int mat[4][4] = {14, 10, 11, 15,
						  9,  3,  0,  4,
						  8,  2,  1,  5,
						 13,  7,  6, 12};*/
		int mat[4][4] = { 0,  8,  2, 10,
						 12,  4, 14,  6,
						  3, 11,  1,  9,
						 15,  7, 13,  5};
		for(rowIndex = 0; rowIndex < order; rowIndex++)
			for(colIndex = 0; colIndex < order; colIndex++)
				dither[rowIndex*order+colIndex] = mat[rowIndex][colIndex];
	}

	for(rowIndex = 0; rowIndex < order; rowIndex++)
	{
		for(colIndex = 0; colIndex < order; colIndex++)
		{
			//cout<<" "<< dither[rowIndex*order + colIndex];
			threshold[rowIndex*order + colIndex] = (dither[rowIndex*order + colIndex] + 0.5) * 128 / (order * order);
			cout<<" "<<threshold[rowIndex*order + colIndex];
		}
		cout<<endl;
	}
	for(rowIndex = 0; rowIndex < rowSize; rowIndex = rowIndex+order)
	{
		for(colIndex = 0; colIndex < colSize; colIndex = colIndex+order)
		{
			ditherIndexX = rowIndex % order;
			ditherIndexY = colIndex % order;

			threshVal = threshold[ditherIndexX*order + ditherIndexY];
			if(inputImageData[rowIndex*colSize + colIndex] < threshVal)
			{
				outputImage[rowIndex*colSize + colIndex] = 0;
			}
			else if((inputImageData[rowIndex*colSize + colIndex]>threshVal) 
				&& (inputImageData[rowIndex*colSize + colIndex]<threshVal+64))
			{
				outputImage[rowIndex*colSize + colIndex] = (255/3);
			}
			else if((inputImageData[rowIndex*colSize + colIndex]>threshVal) 
				&& (inputImageData[rowIndex*colSize + colIndex]<threshVal+64*2))
			{
				outputImage[rowIndex*colSize + colIndex] = (2*255/3);
			}
			else
			{
				outputImage[rowIndex*colSize + colIndex] = 255;
			}

		}
		//cout<<endl;
	}
	
}
void specialFilter::errorDiffusionfloyd()
{
	int rowIndex, colIndex;
	int diffRowIndex, diffColIndex;
	float errorVal;
	float* normalizedInput = new float[rowSize*colSize];

	int order = 3;
	int weight = 16;
	float diffusionMat[3][3] = {0,	0,	0,
									0,	0,	7,
									3,  5,  1};
		

	

	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			normalizedInput[rowIndex*colSize+colIndex] = (float)inputImageData[rowIndex*colSize+colIndex]/255;
			///cout<<normalizedInput[rowIndex*colSize+colIndex];
		}
		//cout<<endl;
	}

	for(rowIndex = (order/2); rowIndex < rowSize-(order/2); rowIndex++)
		for(colIndex = (order/2); colIndex < colSize-(order/2); colIndex++)
		{
			if(normalizedInput[rowIndex*colSize+colIndex] > 0.5)
				outputImage[rowIndex*colSize+colIndex] = 255;
			else
				outputImage[rowIndex*colSize+colIndex] = 0;

			//getchar();
			errorVal = normalizedInput[rowIndex*colSize+colIndex] - (float) outputImage[rowIndex*colSize+colIndex] / 255;
			/*if(rowIndex == 0)
					{
						cout<<normalizedInput[(rowIndex)*colSize+(colIndex)]<<endl;
						cout<<errorVal<<endl;
					}*/
			for(diffRowIndex = 0; diffRowIndex < (order/2)+1; diffRowIndex++)
				for(diffColIndex = -(order/2); diffColIndex < (order/2)+1; diffColIndex++)
				{
					

					normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)] = errorVal *
						diffusionMat[diffRowIndex+(order/2)][diffColIndex+(order/2)]/weight +
						normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)];
					
					//if(rowIndex == 0)
					//{
					////	cout<<normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)]<<endl;
					////	cout<<errorVal<<endl;
					//}
				}

		}

		delete normalizedInput;
}
void specialFilter::errorDiffusionJarvis()
{
	int rowIndex, colIndex;
	int diffRowIndex, diffColIndex;
	float errorVal;
	float* normalizedInput = new float[rowSize*colSize];

	
	float diffusionMat[5][5] = {0,0,0,0,0,	
								  0,0,0,0,0,
								  0,0,0,7,5,
								  3,5,7,5,3,
								  1,3,5,3,1};
		int weight = 48;
		int order = 5;
	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			normalizedInput[rowIndex*colSize+colIndex] = (float)inputImageData[rowIndex*colSize+colIndex]/255;
			///cout<<normalizedInput[rowIndex*colSize+colIndex];
		}
		//cout<<endl;
	}

	for(rowIndex = (order/2); rowIndex < rowSize-(order/2); rowIndex++)
		for(colIndex = (order/2); colIndex < colSize-(order/2); colIndex++)
		{
			if(normalizedInput[rowIndex*colSize+colIndex] > 0.5)
				outputImage[rowIndex*colSize+colIndex] = 255;
			else
				outputImage[rowIndex*colSize+colIndex] = 0;

			//getchar();
			errorVal = normalizedInput[rowIndex*colSize+colIndex] - (float) outputImage[rowIndex*colSize+colIndex] / 255;
			/*if(rowIndex == 0)
					{
						cout<<normalizedInput[(rowIndex)*colSize+(colIndex)]<<endl;
						cout<<errorVal<<endl;
					}*/
			for(diffRowIndex = 0; diffRowIndex < (order/2)+1; diffRowIndex++)
				for(diffColIndex = -(order/2); diffColIndex < (order/2)+1; diffColIndex++)
				{
					

					normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)] = errorVal *
						diffusionMat[diffRowIndex+(order/2)][diffColIndex+(order/2)]/weight +
						normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)];
					
					//if(rowIndex == 0)
					//{
					////	cout<<normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)]<<endl;
					////	cout<<errorVal<<endl;
					//}
				}

		}

	delete normalizedInput;
}
void specialFilter::errorDiffusionStucki()
{
	
	int rowIndex, colIndex;
	int diffRowIndex, diffColIndex;
	float errorVal;
	float* normalizedInput = new float[rowSize*colSize];

	
		float diffusionMat[5][5] = {0,0,0,0,0,	
								  0,0,0,0,0,
								  0,0,0,8,4,
								  2,4,8,4,2,
								  1,2,4,2,1};
	int order = 5;
	int weight = 42;
	

	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			normalizedInput[rowIndex*colSize+colIndex] = (float)inputImageData[rowIndex*colSize+colIndex]/255;
			///cout<<normalizedInput[rowIndex*colSize+colIndex];
		}
		//cout<<endl;
	}

	for(rowIndex = (order/2); rowIndex < rowSize-(order/2); rowIndex++)
		for(colIndex = (order/2); colIndex < colSize-(order/2); colIndex++)
		{
			if(normalizedInput[rowIndex*colSize+colIndex] > 0.5)
				outputImage[rowIndex*colSize+colIndex] = 255;
			else
				outputImage[rowIndex*colSize+colIndex] = 0;

			//getchar();
			errorVal = normalizedInput[rowIndex*colSize+colIndex] - (float) outputImage[rowIndex*colSize+colIndex] / 255;
			/*if(rowIndex == 0)
					{
						cout<<normalizedInput[(rowIndex)*colSize+(colIndex)]<<endl;
						cout<<errorVal<<endl;
					}*/
			for(diffRowIndex = 0; diffRowIndex < (order/2)+1; diffRowIndex++)
				for(diffColIndex = -(order/2); diffColIndex < (order/2)+1; diffColIndex++)
				{
					

					normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)] = errorVal *
						diffusionMat[diffRowIndex+(order/2)][diffColIndex+(order/2)]/weight +
						normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)];
					
					//if(rowIndex == 0)
					//{
					////	cout<<normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)]<<endl;
					////	cout<<errorVal<<endl;
					//}
				}

		}

		delete normalizedInput;
}
void specialFilter::errorDiffSerpentine()
{
	int rowIndex, colIndex;
	int diffRowIndex, diffColIndex;
	float errorVal;
	float* normalizedInput = new float[rowSize*colSize];

	float difMatEven[3][3] =	{0,	0,	0,
								0,	0,	7,
								3,  5,  1};

	float difMatOdd[3][3] =		{0,	0,	0,
								7,	0,	0,
								1,  5,  3};
	int order = 3;

	int weight = 16;
	
	for(rowIndex = 0; rowIndex < rowSize; rowIndex++)
		for(colIndex = 0; colIndex < colSize; colIndex++)
		{
			normalizedInput[rowIndex*colSize+colIndex] = (float)inputImageData[rowIndex*colSize+colIndex]/255;
			
		}
//getchar();
	for(rowIndex = (order/2); rowIndex < rowSize-(order/2); rowIndex++)
	{
		if(rowIndex%2 == 0)
		{
			for(colIndex = (order/2); colIndex < colSize-(order/2); colIndex++)
			{
				if(normalizedInput[rowIndex*colSize+colIndex] > 0.5)
					outputImage[rowIndex*colSize+colIndex] = 255;
				else
					outputImage[rowIndex*colSize+colIndex] = 0;

				errorVal = normalizedInput[rowIndex*colSize+colIndex] - (float) outputImage[rowIndex*colSize+colIndex] / 255;
				
				for(diffRowIndex = 0; diffRowIndex < (order/2)+1; diffRowIndex++)
					for(diffColIndex = -(order/2); diffColIndex < (order/2)+1; diffColIndex++)
					{
						normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)] = errorVal *
							difMatEven[diffRowIndex+(order/2)][diffColIndex+(order/2)]/weight +
							normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)];
					}

			}
		}
		else
		{
			
			for(colIndex = colSize-(order/2); colIndex > (order/2); colIndex--)
			{
				if(normalizedInput[rowIndex*colSize+colIndex] > 0.5)
					outputImage[rowIndex*colSize+colIndex] = 255;
				else
					outputImage[rowIndex*colSize+colIndex] = 0;

				errorVal = normalizedInput[rowIndex*colSize+colIndex] - (float) outputImage[rowIndex*colSize+colIndex] / 255;
				
				for(diffRowIndex = -(order/2); diffRowIndex < (order/2)+1; diffRowIndex++)
					for(diffColIndex = -(order/2); diffColIndex < (order/2)+1; diffColIndex++)
					{
						normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)] = errorVal *
							difMatOdd[diffRowIndex+(order/2)][diffColIndex+(order/2)]/weight +
							normalizedInput[(rowIndex+diffRowIndex)*colSize+(colIndex+diffColIndex)];
					}

			}
		}
	}
		delete normalizedInput;
}