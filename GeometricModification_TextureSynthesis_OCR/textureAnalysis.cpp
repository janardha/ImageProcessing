#include "modification.h"

void modifyImage::filterbankFormation()
{
	int idx1, idx2;
	int index1, index2;
	//lawsvactor has L5, E5, S5, W5, R5 in the order given
	int lawsVector[25] = {1, 4, 6, 4, 1,
						-1, -2, 0, 2, 1,
						-1, 0, 2, 0, -1,
						-1, 2, 0, -2, 1,
						1, -4, 6, -4, 1};

	int tempVec1[5], tempVec2[5];
	for(index1 = 0; index1 < 5; index1++)
	{
		for(idx1 = 0; idx1 < 5; idx1++)
			tempVec1[idx1] = lawsVector[index1*5+idx1];

		for(index2 = 0; index2 < 5; index2++)
		{
			for(idx1 = 0; idx1 < 5; idx1++)
				tempVec2[idx1] = lawsVector[index2*5+idx1];

			for(idx1 = 0; idx1 < 5; idx1++)
				for(idx2 = 0; idx2 < 5; idx2++)
				{
					filterBank[index1*5+index2].bank[idx1*5+idx2] = tempVec1[idx1]*tempVec2[idx2];
				}
		}
	}
//	getchar();
	for(index1 = 0; index1 < numOfFeaturesVec; index1 ++)
	{
		tIP[index1].img = new double[iprowSize*ipcolSize];
	}
}

void modifyImage::transformDomainConversion(unsigned char* ipImg)
{
	int rowIndex, colIndex;
	int rIdx,cIdx;
	int index;
	int imageRowMask, imageColMask;
	double sum = 0;

	for(index =0; index < 25; index++)
		for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
			for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			{
				for(rIdx = -2; rIdx < 3; rIdx++)
					for(cIdx = -2; cIdx < 3; cIdx++)
					{
						imageRowMask = rowIndex + rIdx;
						imageColMask = colIndex + cIdx;
						if(imageRowMask >=0 && imageColMask >=0)
							sum = sum + filterBank[index].bank[(rIdx+2)*5+(cIdx+2)] * 
								ipImg[abs(imageRowMask)*ipcolSize + abs(imageColMask)];
					}
					tIP[index].img[rowIndex*ipcolSize+colIndex] = sum/25;
					sum=0;
			}
		/*for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
			for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			{
				outputImage[rowIndex*ipcolSize+colIndex] = tIP[11].img[rowIndex*ipcolSize+colIndex];
			}*/
		/*	for(index = 1; index < 25; index= index+4){
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			outputImage[rowIndex*ipcolSize+colIndex] = tIP[index].img[rowIndex*ipcolSize+colIndex];
	imageWriter(outputImage, iprowSize*ipcolSize);
	getchar();
}*/
	
}

void modifyImage::energyComputation(int order)
{
	int rowIndex, colIndex;
	int rIdx,cIdx;
	int index;
	int imageRowMask, imageColMask;
	double sum = 0;
	double* imgStore = new double[iprowSize*ipcolSize];

	
	setFilepath("..\energy.raw");
	for(index =0; index < 25; index++)
	{
		for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
			for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			{
				for(rIdx = -order/2; rIdx < ((order/2)+1); rIdx++)
					for(cIdx = -order/2; cIdx < ((order/2)+1); cIdx++)
					{
						imageRowMask = rowIndex + rIdx;
						imageColMask = colIndex + cIdx;
						if(imageRowMask >=0 && imageColMask >=0 &&
							imageRowMask <iprowSize && imageColMask <ipcolSize)
							sum = sum + tIP[index].img[abs(imageRowMask)*ipcolSize + abs(imageColMask)] * 
											tIP[index].img[abs(imageRowMask)*ipcolSize + abs(imageColMask)];
					}
					imgStore[rowIndex*ipcolSize+colIndex] = sum;///(order*order);
					sum=0;
			}

		for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
			for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			{
				tIP[index].img[rowIndex*ipcolSize+colIndex] = imgStore[rowIndex*ipcolSize+colIndex];
				
			}
		
	}
	
	/*if(imgStore)
		delete imgStore;*/
}

void modifyImage::normalizeTransformedImg()
{
	int rowIndex, colIndex;
	int index;

	for(index = 1; index < 25; index++)
		for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
			for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			{
				if(tIP[0].img[rowIndex*ipcolSize+colIndex] !=0)
					tIP[index].img[rowIndex*ipcolSize+colIndex] = tIP[index].img[rowIndex*ipcolSize+colIndex] / 
															tIP[0].img[rowIndex*ipcolSize+colIndex];
			}
	/*for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
			outputImage[rowIndex*ipcolSize+colIndex] = tIP[16].img[rowIndex*ipcolSize+colIndex];*/

}

void modifyImage::deleteFilterbanks()
{
	int index;
	for(index = 0; index < numOfFeaturesVec; index++)
		if(tIP[index].img)
			delete tIP[index].img;
}
void modifyImage::avgFeatureVec()
{
	int index;
	int rowIndex, colIndex;
	float avgVal = 0;
	
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			for(index = 1; index < 25; index++)
				avgVal = avgVal + tIP[index].img[rowIndex*ipcolSize+colIndex];
			outputImage[rowIndex*ipcolSize+colIndex] = avgVal/24;
		}
}