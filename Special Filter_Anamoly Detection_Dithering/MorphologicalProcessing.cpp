////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "filter.h"

void specialFilter::ImageNegate(unsigned char* imgPtr)
{
	int rowIndex, colIndex;
	for(rowIndex = 0;rowIndex < rowSize;rowIndex++)
		for(colIndex = 0;colIndex < colSize;colIndex++)
		{
			if(imgPtr[rowIndex*colSize+colIndex] == 255)
				imgPtr[rowIndex*colSize+colIndex] = 0;
			else
				imgPtr[rowIndex*colSize+colIndex] = 255;
		}
}
void specialFilter::shrinkingAlgorithm(unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	patternDB dBElement;

	int mat[9];
	int bondWt[9] = {1,2,1,2,0,2,1,2,1};
	char *str;
	int bondNum = 0;
	int count=0;
	bool condCheck;
	int rowIndex, colIndex; 
	int winRowIndex, winColIndex, index =0;

	int* mMatrix = new int[rowSize*colSize];

	for(rowIndex = 0;rowIndex < rowSize;rowIndex++)
	{
		//getchar();
		for(colIndex = 0;colIndex < colSize;colIndex++)
		{
			if(ipImgPtr[rowIndex*colSize+colIndex] == 0)
			{
				mMatrix[rowIndex*colSize+colIndex] = 0;
				count++;
			}
			else
			{
				for(winRowIndex = -1; winRowIndex < 2; winRowIndex++)
					for(winColIndex = -1; winColIndex < 2;winColIndex++)
					{
						mat[index] = ipImgPtr[abs(rowIndex+winRowIndex)*colSize+abs(colIndex+winColIndex)]/255;
						bondNum = bondNum + mat[index] * bondWt[index++];
					}

					condCheck = dBElement.checkConditionTable1(bondNum, mat, SHRINK);

				if(condCheck)
					mMatrix[rowIndex*colSize+colIndex] = 1;
				else
					mMatrix[rowIndex*colSize+colIndex] = ipImgPtr[rowIndex*colSize+colIndex]/255;
				index = 0;
				bondNum = 0;
			}
			
		}
	}

	
	for(rowIndex = 1;rowIndex < rowSize-1;rowIndex++)
	{
		for(colIndex = 1;colIndex < colSize-1;colIndex++)
		{
			if(mMatrix[rowIndex*colSize+colIndex] == 0)
			{
				opImgPtr[rowIndex*colSize+colIndex] = 0;
			}
			else
			{
				for(winRowIndex = -1; winRowIndex < 2; winRowIndex++)
					for(winColIndex = -1; winColIndex < 2;winColIndex++)
					{
						mat[index] = mMatrix[(rowIndex+winRowIndex)*colSize+(colIndex+winColIndex)];
						bondNum = bondNum + mat[index] * bondWt[index++];
					}

				condCheck = dBElement.checkConditionTable2(bondNum, mat, SHRINK);

				if(condCheck)
				{
					opImgPtr[rowIndex*colSize+colIndex] = ipImgPtr[rowIndex*colSize+colIndex];
					count++;
				}
				else
				{
					opImgPtr[rowIndex*colSize+colIndex] = 0;//
					count++;
				}
				index = 0;
				bondNum = 0;
			}
			
		}
	}
//	cout<<count<<endl;
	delete mMatrix;
}

int specialFilter::holeCounter(unsigned char* imgPtr)
{
	int mat[49];
	int bondWt[49] ={1,1,1,2,1,1,1,
					 1,1,2,4,2,1,1,
					 1,2,4,0,4,2,1,
					 1,1,2,4,2,1,1,
					 1,1,1,2,1,1,1};
	int order = 7;
	int count=0;
	int bondNum = 0;
	int rowIndex, colIndex; 
	int winRowIndex, winColIndex, index =0;

	//getchar();
	for(rowIndex = order/2;rowIndex < rowSize-order/2;rowIndex++)
		for(colIndex = order/2;colIndex < colSize-order/2;colIndex++)
		{
			if(imgPtr[rowIndex*colSize+colIndex] > 0)
			{
				for(winRowIndex = -order/2; winRowIndex < (order/2)+1; winRowIndex++)
					for(winColIndex = -order/2; winColIndex < (order/2)+1;winColIndex++)
					{
						mat[index] = imgPtr[(rowIndex+winRowIndex)*colSize+(colIndex+winColIndex)]/255;
						bondNum = bondNum + mat[index] * bondWt[index++];
					}
				if(bondNum < 5)
				{
					loc[count].x_pos = colIndex;
					loc[count].y_pos = rowIndex;
					cout<<rowIndex;
					cout<<" "<<colIndex<<endl;
					count++;
				}
				bondNum = 0;
				index = 0;
			}
		}

	cout<<count<<endl;
	return count;
}
void specialFilter::dilateImage(unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	int rowIndex, colIndex;
	int matRowIndex, matColIndex;
	int mat[3][3];
	int i,j;
	int order = 3;
	int count =0;

	//getchar();
	for(rowIndex = order/2; rowIndex < rowSize-1; rowIndex++)
		for(colIndex = order/2; colIndex < colSize-1; colIndex++)
		{
			for(matRowIndex = -order/2; matRowIndex < (order/2)+1; matRowIndex++)
				for(matColIndex = -order/2; matColIndex < (order/2)+1; matColIndex++)
				{
					i = rowIndex+matRowIndex;
					j = colIndex+matColIndex;

					mat[matRowIndex+order/2][matColIndex+order/2] = ipImgPtr[i*colSize+j]/255;
					
					count = count + mat[matRowIndex+order/2][matColIndex+order/2];
				}
				if(count == 9)
					opImgPtr[rowIndex*colSize+colIndex] = 255;
				else
					opImgPtr[rowIndex*colSize+colIndex] = 0;
				count =0;
		}
}

void specialFilter::locationIndicator(int surroundingType,unsigned char* imgPtr)
{
	int mat[25];
	int bondWt[25] ={1,1,2,1,1,
					 1,2,4,2,1,
					 2,4,0,4,2,
					 1,2,4,2,1,
					 1,1,2,1,1};
	int order = 5;
	int count=0;
	int bondNum = 0;
	int rowIndex, colIndex; 
	int winRowIndex, winColIndex, index = 0;

	int numOfLoc = 0;
	//getchar();
	for(rowIndex = 50;rowIndex < rowSize-50;rowIndex++)
		for(colIndex = 50;colIndex < colSize-50;colIndex++)
		{
			if((imgPtr[rowIndex*colSize+colIndex] == 0 && surroundingType == WHITE) ||
				(imgPtr[rowIndex*colSize+colIndex] > 0 && surroundingType == BLACK))
			{
				for(winRowIndex = -order/2; winRowIndex < (order/2)+1; winRowIndex++)
					for(winColIndex = -order/2; winColIndex < (order/2)+1;winColIndex++)
					{
						mat[index] = imgPtr[(rowIndex+winRowIndex)*colSize+(colIndex+winColIndex)]/255;
						bondNum = bondNum + mat[index] * bondWt[index++];
					}
				if(((bondNum  == 44 && surroundingType == WHITE) || 
					(bondNum < 10 && surroundingType == BLACK))&&
					(loc[numOfLoc-1].x_pos != colIndex && loc[numOfLoc-1].y_pos !=rowIndex))
					{
						loc[numOfLoc].x_pos = colIndex;
						loc[numOfLoc].y_pos = rowIndex;
						cout<<rowIndex;
						cout<<" "<<colIndex<<endl;
						numOfLoc++;
					}
				bondNum = 0;
				index = 0;
			}
		}
		//cout<<numOfLoc<<endl;
}

int specialFilter::findRadiusOFGear(unsigned char* imgPtr)
{
	int colIndex;
	int count =0;

	for(colIndex = centerCol; (colIndex > 0)&& imgPtr[centerRow*colSize+colIndex] > 0; colIndex--)
	{
		count++;	
	}
	cout<<"The Radius of the gear is "<<count<<" pixels"<<endl;
	return count;
}

void specialFilter::findToothpositions(unsigned char* ipImgPtr,unsigned char* opImgPtr, int NumOfTeeth, bool displayMissingGear)
{
	int rowIndex, colIndex;
	int itr;
	float rad;

	for(rowIndex = 0;rowIndex < rowSize;rowIndex++)
		for(colIndex = 0;colIndex < colSize;colIndex++)
		{
			opImgPtr[rowIndex*colSize+colIndex] = 0;
		}
	rowIndex = centerRow;
	colIndex = centerCol;
	/////////display the center of the gear///////////////////
	opImgPtr[(rowIndex+1)*colSize+(colIndex+1)] = 255;
	opImgPtr[(rowIndex-1)*colSize+(colIndex-1)] = 255;
	opImgPtr[(rowIndex+2)*colSize+(colIndex+2)] = 255;
	opImgPtr[(rowIndex-2)*colSize+(colIndex-2)] = 255;
	/////////////////////////////////////////////////////////

	for(itr = 0; itr < NumOfTeeth; itr++)
	{
		rad = itr * (360/NumOfTeeth) * PI / 180;
		rowIndex = centerRow + sin(rad) * radius + 1;
		colIndex = centerCol + cos(rad) * radius ;
		if(displayMissingGear)
		{
			if(ipImgPtr[(rowIndex-2)*colSize+(colIndex-2)] == 0 &&
				ipImgPtr[rowIndex*colSize+colIndex] == 0 &&
				ipImgPtr[(rowIndex)*colSize+(colIndex+1)] == 0 )
			{
				cout<<rowIndex;
				cout<<" "<<colIndex<<endl;

				opImgPtr[rowIndex*colSize+colIndex] = 255;
				opImgPtr[(rowIndex+1)*colSize+(colIndex+1)] = 255;
				opImgPtr[(rowIndex-1)*colSize+(colIndex-1)] = 255;
				/*outputImage[(rowIndex+2)*colSize+(colIndex+2)] = 255;
				outputImage[(rowIndex-2)*colSize+(colIndex-2)] = 255;*/
			}
		}
		else
		{
			if(ipImgPtr[(rowIndex-2)*colSize+colIndex-2] > 0 ||
				ipImgPtr[(rowIndex-1)*colSize+colIndex-1] > 0 ||
				ipImgPtr[rowIndex*colSize+colIndex] > 0 || 
				ipImgPtr[(rowIndex+1)*colSize+(colIndex+1)] > 0 )
			{
				cout<<rowIndex;
				cout<<" "<<colIndex<<endl;

				opImgPtr[rowIndex*colSize+colIndex] = 255;
				opImgPtr[(rowIndex+1)*colSize+(colIndex+1)] = 255;
				opImgPtr[(rowIndex-1)*colSize+(colIndex-1)] = 255;
				/*outputImage[(rowIndex+2)*colSize+(colIndex+2)] = 255;
				outputImage[(rowIndex-2)*colSize+(colIndex-2)] = 255;*/
			}
		}
	}
}

void specialFilter::pathWays(int background)
{
	int rowIndex, colIndex;
	
	int boundary[3][3] = {0,1,0,
						  1,1,1,
						  0,1,0};
	int order = 3;
	int winRowIndex, winColIndex;
	int numOfHoles;
	int count=0, hc=0;
	unsigned char* imageDilate = new unsigned char[rowSize*colSize];
	unsigned char* imageTemp = new unsigned char[rowSize*colSize];
	unsigned char* imageComplement = new unsigned char[rowSize*colSize];

	copyImagedata(inputImageData,imageTemp);

	for(int i = 0; i<2;i++)
	{
		dilateImage(imageTemp,imageDilate);
		copyImagedata(imageDilate,imageTemp);
	}

	copyImagedata(inputImageData,imageTemp);

	numOfHoles = holeCounter(imageDilate);

	cout<<"Number of holes "<<numOfHoles<<endl;

	for(hc = 0; hc<numOfHoles; hc++)
		for(rowIndex = loc[hc].y_pos-5;rowIndex < loc[hc].y_pos+5;rowIndex++)
			for(colIndex = loc[hc].x_pos-5;colIndex < loc[hc].x_pos+5;colIndex++)
			{
				for(winRowIndex =-order/2; winRowIndex<order/2+1;winRowIndex++)
					for(winColIndex =-order/2; winColIndex<order/2+1;winColIndex++)
						count = count+boundary[winRowIndex][winColIndex]*
								inputImageData[(rowIndex+winRowIndex)*colSize+(colIndex+winColIndex)];
				if(count > 0)
					imageTemp[rowIndex*colSize+colIndex] = 0;
				else
					imageTemp[rowIndex*colSize+colIndex] = inputImageData[rowIndex*colSize+colIndex];
			}

			//if(background == WHITE)
			//	ImageNegate(imageTemp);

			setFilepath("../fillHolespcb.raw");
			imageWriter(imageTemp,rowSize*colSize*bytesInPixel);
			
			
			outline(imageTemp,imageComplement);

			setFilepath("../outlinepcb.raw");
			imageWriter(imageComplement,rowSize*colSize*bytesInPixel);

			breakLink(imageComplement,imageTemp);
			
			setFilepath("../linkBreak.raw");
			imageWriter(imageTemp,rowSize*colSize*bytesInPixel);

			shrinkingAlgorithm(imageTemp,outputImage);
			numOfHoles = holeCounter(imageTemp);
			cout<<"Number of pathways "<<numOfHoles<<endl;
			if(background == WHITE)
				ImageNegate(outputImage);

			setFilepath("../shrinkingOutput.raw");
			imageWriter(imageTemp,rowSize*colSize*bytesInPixel);

	delete imageComplement;
	delete imageDilate;
	delete imageTemp;
}

void specialFilter::outline(unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	patternDB dBElement;

	int mat[9];
	int bondWt[9] = {1,2,1,2,0,2,1,2,1};
	char *str;
	int bondNum = 0;
	int count=0;
	bool condCheck;
	int rowIndex, colIndex; 
	int winRowIndex, winColIndex, index =0;

	int* mMatrix = new int[rowSize*colSize];

	for(rowIndex = 0;rowIndex < rowSize;rowIndex++)
	{
		//getchar();
		for(colIndex = 0;colIndex < colSize;colIndex++)
		{
			if(ipImgPtr[rowIndex*colSize+colIndex] == 0)
			{
				mMatrix[rowIndex*colSize+colIndex] = 0;
				count++;
			}
			else
			{
				for(winRowIndex = -1; winRowIndex < 2; winRowIndex++)
					for(winColIndex = -1; winColIndex < 2;winColIndex++)
					{
						mat[index] = ipImgPtr[abs(rowIndex+winRowIndex)*colSize+abs(colIndex+winColIndex)]/255;
						bondNum = bondNum + mat[index] * bondWt[index++];
					}

					condCheck = dBElement.checkConditionTable1(bondNum, mat, SHRINK);

				if(condCheck)
					mMatrix[rowIndex*colSize+colIndex] = ipImgPtr[rowIndex*colSize+colIndex]/255;//1;
				else
					mMatrix[rowIndex*colSize+colIndex] = 0;
				index = 0;
				bondNum = 0;
			}
			
		}
	}

	
	for(rowIndex = 1;rowIndex < rowSize-1;rowIndex++)
	{
		for(colIndex = 1;colIndex < colSize-1;colIndex++)
		{
			if(mMatrix[rowIndex*colSize+colIndex] == 0)
			{
				opImgPtr[rowIndex*colSize+colIndex] = 0;
			}
			else
			{
				for(winRowIndex = -1; winRowIndex < 2; winRowIndex++)
					for(winColIndex = -1; winColIndex < 2;winColIndex++)
					{
						mat[index] = mMatrix[(rowIndex+winRowIndex)*colSize+(colIndex+winColIndex)];
						bondNum = bondNum + mat[index] * bondWt[index++];
					}

				condCheck = dBElement.checkConditionTable2(bondNum, mat, SHRINK);

				if(condCheck)
				{
					opImgPtr[rowIndex*colSize+colIndex] = 255;
					count++;
				}
				else
				{
					opImgPtr[rowIndex*colSize+colIndex] = ipImgPtr[rowIndex*colSize+colIndex];//0;//
					count++;
				}
				index = 0;
				bondNum = 0;
			}
			
		}
	}
//	cout<<count<<endl;
	delete mMatrix;
}

void specialFilter::breakLink(unsigned char* ipImgPtr, unsigned char* opImgPtr)
{
	int a1, b1, c1, a2, b2, c2;

	int rowIndex, colIndex;
//getchar();
	for(rowIndex = 1;rowIndex < rowSize-1;rowIndex++)
		for(colIndex = 1;colIndex < colSize-1;colIndex++)
		{
			if(ipImgPtr[rowIndex*colSize+colIndex] == 255)
			{
				a1 = ipImgPtr[(rowIndex-1)*colSize+(colIndex-1)]/255;
				b1 = ipImgPtr[(rowIndex)*colSize+(colIndex-1)]/255;
				c1 = ipImgPtr[(rowIndex+1)*colSize+(colIndex-1)]/255;

				a2 = ipImgPtr[(rowIndex-1)*colSize+(colIndex+1)]/255;
				b2 = ipImgPtr[(rowIndex)*colSize+(colIndex+1)]/255;
				c2 = ipImgPtr[(rowIndex+1)*colSize+(colIndex+1)]/255;

				if((a1==1||b1==1||c1==1)&&(a2==1||b2==1||c2==1))
					opImgPtr[rowIndex*colSize+colIndex] = 0;
				else
					opImgPtr[rowIndex*colSize+colIndex] = ipImgPtr[rowIndex*colSize+colIndex];

			}
			else
				opImgPtr[rowIndex*colSize+colIndex] = ipImgPtr[rowIndex*colSize+colIndex];
		}
}

void specialFilter::gearTooth(int background, int numOfTeeth)
{
	int itr, maxItr;

	int rowIndex, colIndex;
	
	unsigned char* imageDilate = new unsigned char[rowSize*colSize];
	unsigned char* imageTemp = new unsigned char[rowSize*colSize];
	unsigned char* imageComplement = new unsigned char[rowSize*colSize];

	
	copyImagedata(inputImageData,imageTemp);

	if(background == BLACK)
		ImageNegate(imageTemp);

	maxItr = 16;
	for(itr =0; itr < maxItr;itr++)
	{
		dilateImage(imageTemp,imageDilate);
		copyImagedata(imageDilate,imageTemp);
	}

	for(int i = 0; i<2;i++)
	{
		shrinkingAlgorithm(imageTemp,outputImage);
		copyImagedata(outputImage,imageTemp);
	}

	setFilepath("../gearDilated.raw");
	imageWriter(outputImage,rowSize*colSize*bytesInPixel);

	cout<<"the locations of the center of the 4 circles are"<<endl;
	locationIndicator(BLACK,imageTemp);
	
	copyImagedata(inputImageData,imageTemp);
	
	maxItr = 19;
	for(itr =0; itr < maxItr;itr++)
	{
		dilateImage(imageTemp,imageDilate);
		copyImagedata(imageDilate,imageTemp);
	}

	setFilepath("../gearcenter.raw");
	imageWriter(imageTemp,rowSize*colSize*bytesInPixel);

	cout<<"the center of the gear is ";
	locationIndicator(BLACK,imageTemp);

	centerRow = loc[0].y_pos;
	centerCol = loc[0].x_pos;

	//ImageNegate(imageTemp);
	radius = findRadiusOFGear(inputImageData);
	
	cout<<"position of the gears are "<<endl;
	findToothpositions(inputImageData,outputImage,numOfTeeth,false);
	
	setFilepath("../gearToothPos.raw");
	imageWriter(outputImage,rowSize*colSize*bytesInPixel);

	cout<<"position of the missing gears are "<<endl;
	findToothpositions(inputImageData,outputImage,numOfTeeth,true);

	setFilepath("../gearMissingToothPos.raw");
	imageWriter(outputImage,rowSize*colSize*bytesInPixel);

	//copyImagedata(imageDilate,outputImage);

	/*if(background == BLACK)
			ImageNegate(outputImage);*/

	delete imageComplement;
	delete imageDilate;
	delete imageTemp;
}