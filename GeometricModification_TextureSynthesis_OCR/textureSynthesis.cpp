#include "modification.h"

void modifyImage::blockBasedSynthesis(int blkRSize, int blkCSize)
{
	int rowIndex, colIndex;
	int blkRowIdx, blkColIdx;

	int rowitr = oprowSize/blkRSize;
	int colitr = opcolSize/blkCSize;

	int rowStart = iprowSize/2 - blkRSize/2;
	int colStart = ipcolSize/2 - blkCSize/2;

	unsigned char *blockImg;
	blockImg = new unsigned char[blkRSize*blkCSize*3];

	outputImage = new unsigned char[oprowSize*opcolSize*bytesPerPixelInOutput];

	//int count=0;
	//for(blkRowIdx = 0; blkRowIdx < blkRSize; blkRowIdx++)
	//	for(blkColIdx = 0; blkColIdx < blkCSize; blkColIdx++)
	//	{
	//		blockImg[3*(blkRowIdx*blkCSize+blkColIdx)] = inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))];
	//		blockImg[3*(blkRowIdx*blkCSize+blkColIdx)+1] = inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))+1];
	//		blockImg[3*(blkRowIdx*blkCSize+blkColIdx)+2] = inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))+2];
	//		count = count+1;
	//	}
	//	cout<<count<<endl;
	//	count =0;
	//	getchar();

	for(rowIndex = 0; rowIndex < oprowSize; rowIndex=rowIndex+blkRSize)
		for(colIndex = 0; colIndex < opcolSize; colIndex=colIndex+blkCSize)
		{
			rowStart = rand() * (iprowSize-blkRSize)/(RAND_MAX + 1);
			colStart = rand() * (ipcolSize-blkCSize)/(RAND_MAX + 1);
			for(blkRowIdx = 0; blkRowIdx < blkRSize; blkRowIdx++)
				for(blkColIdx = 0; blkColIdx < blkCSize; blkColIdx++)
				{
					if(rowIndex+blkRowIdx < oprowSize && (colIndex+blkColIdx) < opcolSize)
					{
						outputImage[3*((rowIndex+blkRowIdx)*opcolSize + (colIndex+blkColIdx))] = 
							inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))];
						outputImage[3*((rowIndex+blkRowIdx)*opcolSize + (colIndex+blkColIdx))+1] = 
							inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))+1];
						outputImage[3*((rowIndex+blkRowIdx)*opcolSize + (colIndex+blkColIdx))+2] = 
							inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))+2];
					}//count = count+1;
				}
		}
				
	delete blockImg;
}

void modifyImage::efrosFreemanAlgo(int blkRSize, int blkCSize, int overlapWidth, float maxError, int minCutReq)
{
	int rowIndex, colIndex;
	int blkRowIdx, blkColIdx;

	bool horizontal, vertical;

	int rowitr = oprowSize/blkRSize;
	int colitr = opcolSize/blkCSize;

	int rowStart = 25;
	int colStart = 35;

	unsigned char *blockImg;
	blockImg = new unsigned char[blkRSize*blkCSize*3];

	outputImage = new unsigned char[oprowSize*opcolSize*bytesPerPixelInOutput];

//	getchar();

	modImage = new unsigned char[iprowSize*ipcolSize*bytesInPixel];
	grayScaleConversion(inputImageData, modImage, iprowSize, ipcolSize);

	//////////////////initial block/////////////////////////	
	for(blkRowIdx = 0; blkRowIdx < blkRSize; blkRowIdx++)
	{
		for(blkColIdx = 0; blkColIdx < blkCSize; blkColIdx++)
		{
			blockImg[3*(blkRowIdx*blkCSize+blkColIdx)] = inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))];
			blockImg[3*(blkRowIdx*blkCSize+blkColIdx)+1] = inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))+1];
			blockImg[3*(blkRowIdx*blkCSize+blkColIdx)+2] = inputImageData[3*((rowStart+blkRowIdx)*ipcolSize + (colStart+blkColIdx))+2];
			
		}
	}
	rowIndex = 0;
	colIndex = 0;
	for(rowIndex = 0; rowIndex < oprowSize; rowIndex = rowIndex+blkRSize-overlapWidth)
	{
		rowStart = rowIndex;
		colStart = 0;
		for(colIndex = 0; colIndex < opcolSize; colIndex = colIndex+blkCSize-overlapWidth)
		{
			if(rowIndex > 0)
				horizontal = true;
			else
				horizontal = false;

			if(colIndex > 0)
				vertical = true;
			else
				vertical = false;

			if(horizontal || vertical)
				findSSD(blockImg,blkRSize, (rowIndex-blkRSize+overlapWidth), colIndex, overlapWidth, maxError,horizontal, vertical, minCutReq);
			
			insertBlock(blockImg,blkRSize, blkCSize,rowIndex,colIndex);
		}

		for(blkRowIdx = 0; blkRowIdx < blkRSize; blkRowIdx++)
			for(blkColIdx = 0; blkColIdx < blkCSize; blkColIdx++)
			{
				blockImg[3*(blkRowIdx*blkCSize+blkColIdx)] = outputImage[3*((rowStart+blkRowIdx)*opcolSize + (colStart+blkColIdx))];
				blockImg[3*(blkRowIdx*blkCSize+blkColIdx)+1] = outputImage[3*((rowStart+blkRowIdx)*opcolSize + (colStart+blkColIdx))+1];
				blockImg[3*(blkRowIdx*blkCSize+blkColIdx)+2] = outputImage[3*((rowStart+blkRowIdx)*opcolSize + (colStart+blkColIdx))+2];
				
			}
	}
	delete blockImg;
}
void modifyImage::findSSD(unsigned char *blk, int blkSize, int r, int c, int olapWidth, float err, bool hz, bool vr, int minCutReq)
{
	int rowIndex, colIndex;
	
	float minErr = 1000;
	int minErrRow = 0, minErrCol = 0;

	int outRow = 0, outCol = 0;
	int hOlpSize = olapWidth * blkSize;
	int vOlpSize = olapWidth * blkSize;
	int uprBnd =0, lwrBnd = 0, midBnd = 0;
	float hDiff = 0, vDiff = 0;
	float diff =0;

	int* errorH = new int[olapWidth*blkSize];
	int* errorV = new int[olapWidth*blkSize];
	int* minErrorH = new int[olapWidth*blkSize];
	int* minErrorV = new int[olapWidth*blkSize];
	int index;

	float minDiff = 1000000;

	unsigned char* block = new unsigned char[blkSize*blkSize];
	int innerRow, innerCol;
	int blkR, blkC;
	
	for(index = 0; index < olapWidth*blkSize; index++)
	{
		errorH[index] = 0;
		errorV[index] = 0;
		minErrorH[index] = 0;
		minErrorV[index] = 0;
	}
	grayScaleConversion(blk, block, blkSize, blkSize);

	for(rowIndex = 0; rowIndex < iprowSize+olapWidth-blkSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < ipcolSize+olapWidth-blkSize; colIndex++)
		{
			hDiff = 0;
			vDiff = 0;
			if(hz)
			{
				for(innerCol = 0; innerCol < blkSize; innerCol++)
				{
					blkC = innerCol;
					for(innerRow = 0; innerRow < olapWidth; innerRow++)
					{
						blkR = blkSize - olapWidth + innerRow;
						//blkCSize - olapWidth + innerCol;
						if((colIndex+innerCol)<ipcolSize && (rowIndex+innerRow)<iprowSize)
						{
						//	hDiff = hDiff + pow((double)(blk[blkR*blkSize+blkC] - modImage[(rowIndex+innerRow)*ipcolSize+(colIndex+innerCol)]), 2);
							diff = (outputImage[3*((r+blkR)*opcolSize+(c+blkC))]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))])*
										(outputImage[3*((r+blkR)*opcolSize+(c+blkC))]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))])+
										(outputImage[3*((r+blkR)*opcolSize+(c+blkC))+1]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+1])*
										(outputImage[3*((r+blkR)*opcolSize+(c+blkC))+1]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+1])+
										(outputImage[3*((r+blkR)*opcolSize+(c+blkC))+2]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+2])*
										(outputImage[3*((r+blkR)*opcolSize+(c+blkC))+2]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+2]);
							errorH[innerRow * blkSize + innerCol] = diff;
							hDiff = hDiff + diff;
						}
					}
				}
					hDiff = hDiff/(hOlpSize*hOlpSize*3);
			}
			if(vr)
			{
				for(innerRow = 0; innerRow < blkSize; innerRow++)
				{
					blkR = innerRow;//blkRSize - olapWidth + innerRow;
					for(innerCol = 0; innerCol < olapWidth; innerCol++)
					{
						blkC = blkSize - olapWidth + innerCol;
						if((colIndex+innerCol)<ipcolSize && (rowIndex+innerRow)<iprowSize)
						{
							diff = pow((double)(block[blkR*blkSize+blkC] - modImage[(rowIndex+innerRow)*ipcolSize+(colIndex+innerCol)]), 2);
							/*vDiff = vDiff + (blk[3*(blkR*blkCSize+blkC)]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))])*
											(blk[3*(blkR*blkCSize+blkC)]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))])+
											(blk[3*(blkR*blkCSize+blkC)+1]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+1])*
											(blk[3*(blkR*blkCSize+blkC)+1]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+1])+
											(blk[3*(blkR*blkCSize+blkC)+2]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+2])*
											(blk[3*(blkR*blkCSize+blkC)+2]-inputImageData[3*((rowIndex+innerRow)*ipcolSize+(colIndex+innerCol))+2]);*/
							errorV[innerRow * olapWidth + innerCol] = diff;
							vDiff = vDiff + diff;
						}
					}
				}
				vDiff = vDiff/(vOlpSize*vOlpSize);
			}
			if(minErr > (hDiff+vDiff))
			{
				minErr = hDiff+vDiff;
				minErrRow = rowIndex;
				minErrCol = colIndex;
				for(index = 0; index < olapWidth*blkSize; index++)
				{
					minErrorH[index] = errorH[index];
					minErrorV[index] = errorV[index];
				}
			}
		}
	}

	for(innerRow = 0; innerRow < blkSize; innerRow++)
		for(innerCol = 0; innerCol < blkSize; innerCol++)
		{
			blk[3*(innerRow*blkSize+innerCol)] = inputImageData[3*((minErrRow+innerRow)*ipcolSize+(minErrCol+innerCol))];
			blk[3*(innerRow*blkSize+innerCol)+1] = inputImageData[3*((minErrRow+innerRow)*ipcolSize+(minErrCol+innerCol))+1];
			blk[3*(innerRow*blkSize+innerCol)+2] = inputImageData[3*((minErrRow+innerRow)*ipcolSize+(minErrCol+innerCol))+2];
		}
	if(minCutReq == 1)
	{
		if(hz)
		{
			innerCol = 0;
			minDiff = 100000;
			for(innerRow = 0; innerRow < olapWidth; innerRow++)
			{
				if(minDiff > minErrorH[innerRow * blkSize + innerCol])
				{
					minDiff = minErrorH[innerRow * blkSize + innerCol];
					minErrRow = innerRow;
				}
			}
			for(innerCol = 1; innerCol < blkSize; innerCol++)
			{
				lwrBnd = minErrRow-1;
				midBnd = minErrRow;
				uprBnd = minErrRow+1;

				if(lwrBnd  < 0)
					lwrBnd = 0;
				if(uprBnd > olapWidth)
					uprBnd = olapWidth;
				minDiff = minErrorH[lwrBnd * blkSize + innerCol];
				if(minDiff > minErrorH[midBnd * blkSize + innerCol] || 
					minDiff > minErrorH[uprBnd * blkSize + innerCol])
				{
					if(minErrorH[midBnd * blkSize + innerCol] > minErrorH[uprBnd * blkSize + innerCol])
					{
						minErrRow = uprBnd;
					}
					else
						minErrRow = midBnd;
				}
				else
					minErrRow = lwrBnd; 

				/*if(minErrRow < 0)
					minErrRow = 0;
				if(minErrRow > olapWidth)
					minErrRow = olapWidth;*/

				for(innerRow = 0; innerRow < minErrRow; innerRow++)
				{
					blkR = blkSize - olapWidth + innerRow;
					blk[3*(innerRow*blkSize+innerCol)] = outputImage[3*((r+blkR)*opcolSize+(c+innerCol))];
					blk[3*(innerRow*blkSize+innerCol)+1] = outputImage[3*((r+blkR)*opcolSize+(c+innerCol))+1];
					blk[3*(innerRow*blkSize+innerCol)+2] = outputImage[3*((r+blkR)*opcolSize+(c+innerCol))+2];
				}
			}
		}
		outRow = r + blkSize - olapWidth;
		outCol = c - blkSize + olapWidth;
		if(vr)
		{
			innerRow = 0;
			minDiff = 100000;
			for(innerCol = 0; innerCol < olapWidth; innerCol++)
			{
				if(minDiff > minErrorV[innerCol])
				{
					minDiff = minErrorV[innerRow * olapWidth + innerCol];
					minErrCol = innerCol;
				}
			}
			for(innerRow = 1; innerRow < blkSize; innerRow++)
			{
				lwrBnd = minErrCol-1;
				midBnd = minErrCol;
				uprBnd = minErrCol+1;

				if(lwrBnd  < 0)
					lwrBnd = 0;
				if(uprBnd > olapWidth-1)
					uprBnd = olapWidth-1;

				minDiff = minErrorV[innerRow * olapWidth + lwrBnd];

				if(minDiff > minErrorV[innerRow * olapWidth + midBnd] || 
					minDiff > minErrorV[innerRow * olapWidth + uprBnd])
				{
					if(minErrorV[innerRow * olapWidth + midBnd] > minErrorV[innerRow * olapWidth + uprBnd])
					{
						minErrCol = uprBnd;
					}
					else
						minErrCol = midBnd;
				}
				else
					minErrCol = lwrBnd;

				/*if(minErrCol < 0)
					minErrCol = 0;
				if(minErrCol > olapWidth)
					minErrCol = olapWidth;*/

				for(innerCol = 0; innerCol < minErrCol; innerCol++)
				{
					blkC = blkSize - olapWidth + innerCol;
					blk[3*(innerRow*blkSize+innerCol)] = outputImage[3*((outRow+innerRow)*opcolSize+(outCol+blkC))];
					blk[3*(innerRow*blkSize+innerCol)+1] = outputImage[3*((outRow+innerRow)*opcolSize+(outCol+blkC))+1];
					blk[3*(innerRow*blkSize+innerCol)+2] = outputImage[3*((outRow+innerRow)*opcolSize+(outCol+blkC))+2];
				}
			}
		}
	}
	
	delete block;
	delete errorH;
	delete errorV;
	delete minErrorH;
	delete minErrorV;
}

void modifyImage::insertBlock(unsigned char *blk, int blkRSize, int blkCSize, int rowStart, int colStart)
{
	int rowIndex, colIndex;

	for(rowIndex = 0; rowIndex < blkRSize; rowIndex++)
		for(colIndex = 0; colIndex < blkCSize; colIndex++)
		{
			if((rowIndex+rowStart) < oprowSize && (colIndex+colStart) < opcolSize)
			{
				outputImage[3*((rowIndex+rowStart)*opcolSize+(colIndex+colStart))] = blk[3*(rowIndex*blkCSize+colIndex)];
				outputImage[3*((rowIndex+rowStart)*opcolSize+(colIndex+colStart))+1] = blk[3*(rowIndex*blkCSize+colIndex)+1];
				outputImage[3*((rowIndex+rowStart)*opcolSize+(colIndex+colStart))+2] = blk[3*(rowIndex*blkCSize+colIndex)+2];
			}
		}
}

void modifyImage::grayScaleConversion(unsigned char* ipImg, unsigned char* opImg, int r, int c)
{
	int rowIndex, colIndex;

	for(rowIndex = 0; rowIndex < r; rowIndex++)
		for(colIndex = 0; colIndex < c; colIndex++)
		{
			opImg[rowIndex*c+colIndex] = (ipImg[3*(rowIndex*c+colIndex)] + ipImg[3*(rowIndex*c+colIndex)+1] +
											ipImg[3*(rowIndex*c+colIndex)+2])/3;
		}
}