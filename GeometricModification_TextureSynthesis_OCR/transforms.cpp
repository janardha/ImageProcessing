#include "modification.h"

void modifyImage::insertPiece(unsigned char* ipImg, unsigned char* opImg, char *argv[])//, unsigned char* piece
{
	int rowIndex, colIndex;
	int innerRIndex, innerCIndex;
	int rI;
	float theta;
	float avgVal = 0;
	float xScaleRatio = 0, yScaleRatio = 0;
	
	modImage = new unsigned char[iprowSize*ipcolSize*bytesInPixel];
	
	////////////read piece.raw///////////////
	iprowSize = atoi(argv[9]);
	ipcolSize = atoi(argv[10]);
	setFilepath(argv[8]);
	
	unsigned char *newImg = new unsigned char[iprowSize*ipcolSize*bytesInPixel];
	newImg = imageReader();
	/////////////////////////////////////////
	cout<<"Coordinates of ends of piece.raw are"<<endl;
	getCoordinates(newImg, WHITE, bytesInPixel);

		cout<<loc[0].r_pos<<", "<<loc[0].c_pos<<endl;
		cout<<loc[1].r_pos<<", "<<loc[1].c_pos<<endl;
		cout<<loc[2].r_pos<<", "<<loc[2].c_pos<<endl;
		cout<<loc[3].r_pos<<", "<<loc[3].c_pos<<endl;

	theta = getTheta();
	rotateImage(newImg,modImage,-theta);
	
	translateImage(modImage,newImg, -73, 77.5);

	rowIndex = 5;
	for(colIndex = 0; colIndex < ipcolSize; colIndex++)
	{
		avgVal = (newImg[3*(rowIndex*ipcolSize+colIndex)] + 
			newImg[3*(rowIndex*ipcolSize+colIndex)+1] + 
			newImg[3*(rowIndex*ipcolSize+colIndex)+2])/3;
		if(avgVal == 255)
			break;
	}
	opcolSize = colIndex-2;
	cout<<opcolSize<<endl;
	colIndex = 5;
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
	{
		avgVal = (newImg[3*(rowIndex*ipcolSize+colIndex)] + 
			newImg[3*(rowIndex*ipcolSize+colIndex)+1] + 
			newImg[3*(rowIndex*ipcolSize+colIndex)+2])/3;
		if(avgVal == 255)
			break;
	}
	oprowSize = rowIndex-2;
	cout<<oprowSize<<endl;

	//delete modImage;
	modImage = new unsigned char[oprowSize*opcolSize*bytesInPixel];

	for(rowIndex = 0; rowIndex < oprowSize; rowIndex++)
		for(colIndex = 0; colIndex < opcolSize; colIndex++)
		{
			modImage[3*(rowIndex*oprowSize+colIndex)] = newImg[3*(rowIndex*ipcolSize+colIndex)];
			modImage[3*(rowIndex*oprowSize+colIndex)+1] = newImg[3*(rowIndex*ipcolSize+colIndex)+1];
			modImage[3*(rowIndex*oprowSize+colIndex)+2] = newImg[3*(rowIndex*ipcolSize+colIndex)+2];
		}
	rI = oprowSize;
	iprowSize = oprowSize;
	ipcolSize = opcolSize;
	xScaleRatio = (float)PIECESIZE / oprowSize;
	yScaleRatio = (float)PIECESIZE / opcolSize;

	cout<<xScaleRatio<<endl;
	cout<<yScaleRatio<<endl;
	
	opcolSize = PIECESIZE;
	oprowSize = PIECESIZE;

	newImg = new unsigned char[oprowSize*opcolSize*bytesInPixel];
	scaleImage(modImage,newImg,xScaleRatio,yScaleRatio);
	//getchar();
	////////read lion.raw and set the row and column parameters/////////////////////
	cout<<"Coordinates of hole in lion.raw are"<<endl;
	iprowSize = atoi(argv[5]);
	ipcolSize = atoi(argv[6]);
	oprowSize = iprowSize;
	opcolSize = ipcolSize;
	//////////////////////////////////////////

	getCoordinates(inputImageData, BLACK, bytesInPixel);

		cout<<loc[0].r_pos<<", "<<loc[0].c_pos<<endl;
		cout<<loc[1].r_pos<<", "<<loc[1].c_pos<<endl;
		cout<<loc[2].r_pos<<", "<<loc[2].c_pos<<endl;
		cout<<loc[3].r_pos<<", "<<loc[3].c_pos<<endl;

	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			opImg[3*(rowIndex*ipcolSize+colIndex)] = inputImageData[3*(rowIndex*ipcolSize+colIndex)];
			opImg[3*(rowIndex*ipcolSize+colIndex)+1] = inputImageData[3*(rowIndex*ipcolSize+colIndex)+1];
			opImg[3*(rowIndex*ipcolSize+colIndex)+2] = inputImageData[3*(rowIndex*ipcolSize+colIndex)+2];
		}

	for(innerRIndex =0,rowIndex = loc[1].r_pos-2; rowIndex < loc[3].r_pos+1; innerRIndex++,rowIndex++)
		for(innerCIndex =0, colIndex = loc[0].c_pos-1; colIndex < loc[2].c_pos+1; innerCIndex++,colIndex++)
		{
			opImg[3*(rowIndex*ipcolSize+colIndex)] = newImg[3*(innerRIndex*PIECESIZE+innerCIndex)];
			opImg[3*(rowIndex*ipcolSize+colIndex)+1] = newImg[3*(innerRIndex*PIECESIZE+innerCIndex)+1];
			opImg[3*(rowIndex*ipcolSize+colIndex)+2] = newImg[3*(innerRIndex*PIECESIZE+innerCIndex)+2];
		}
	
	/*rowIndex = loc[1].r_pos-2;
	for(colIndex = loc[0].c_pos; colIndex < loc[2].c_pos+1; colIndex++)
	{
		opImg[3*(rowIndex*ipcolSize+colIndex)] = inputImageData[3*(rowIndex*ipcolSize+colIndex)];
		opImg[3*(rowIndex*ipcolSize+colIndex)+1] = inputImageData[3*(rowIndex*ipcolSize+colIndex)+1];
		opImg[3*(rowIndex*ipcolSize+colIndex)+2] = inputImageData[3*(rowIndex*ipcolSize+colIndex)+2];
	}
	colIndex = loc[0].c_pos;
	for(rowIndex = loc[1].r_pos; rowIndex < loc[3].r_pos+1; rowIndex++)
	{
		opImg[3*(rowIndex*ipcolSize+colIndex)] = inputImageData[3*(rowIndex*ipcolSize+colIndex)];
		opImg[3*(rowIndex*ipcolSize+colIndex)+1] = inputImageData[3*(rowIndex*ipcolSize+colIndex)+1];
		opImg[3*(rowIndex*ipcolSize+colIndex)+2] = inputImageData[3*(rowIndex*ipcolSize+colIndex)+2];
	}*/
}

void modifyImage::spatialWarping(unsigned char *ipImg, unsigned char *opImg, char *argv[],int imgComb)
{
	int index = 0;
	//getchar();
	segregateImage(ipImg);
	
	//////////second image//////////////
	setFilepath(argv[8]);
	modImage = imageReader();
	modOut = new unsigned char[iprowSize*ipcolSize*bytesInPixel];
	
	///////////////////////////////////////

	for(index = 0; index < numOfTriangles; index++)
	{
		setControlPoints(index,imgComb);
		findSpatialCoefficients(numOfControlPoints);
		mappcoefficients(ipImg,opImg,0);
		//mappcoefficients(modImage,modOut,1);
	}

	segregateImage(modImage);
	for(index = 0; index < numOfTriangles; index++)
	{
		setControlPoints(index,imgComb);
		findSpatialCoefficients(numOfControlPoints);
		mappcoefficients(modImage,modOut,1);
	}
	setFilepath(argv[9]);
	imageWriter(modOut,iprowSize*ipcolSize*bytesInPixel);
}
void modifyImage::findSpatialCoefficients(int NCP)
{
	int index;
	int rowIndex, colIndex;
	double *secondOrderMatrix = new double[NCP*6];

	double tempProd = 0;
	float xCtrlPt = 0;
	float yCtrlPt = 0;

	double tempProd1 = 0;
	float xCtrlPt1 = 0;
	float yCtrlPt1 = 0;
	/*float *transposeMat = new float[6*NCP];
	float *tMat = new float[6*NCP];
	float *prodMat = new float[6*6];*/
	double *invMat = new double[6*6];

	for(index = 0; index < NCP; index++)
	{
		xCtrlPt = (loc[2*index].c_pos + loc[2*index+1].c_pos)/2 - 0.5;////the locations are the pixel values
		yCtrlPt = iprowSize + 0.5 - (loc[2*index].r_pos + loc[2*index+1].r_pos)/2;

		secondOrderMatrix[index*6 + 0] = 1;
		secondOrderMatrix[index*6 + 1] = xCtrlPt;
		secondOrderMatrix[index*6 + 2] = yCtrlPt;
		secondOrderMatrix[index*6 + 3] = xCtrlPt*xCtrlPt;
		secondOrderMatrix[index*6 + 4] = xCtrlPt*yCtrlPt;
		secondOrderMatrix[index*6 + 5] = yCtrlPt*yCtrlPt;
	}

	inverseMatrix(secondOrderMatrix,invMat);
	///////////////////spatial coefficients for more than 6 points///////////
	/////////////////transpose////////////////////
	//for(rowIndex = 0; rowIndex < NCP; rowIndex++)
	//	for(colIndex = 0; colIndex < 6; colIndex++)
	//		transposeMat[colIndex*NCP + rowIndex] = secondOrderMatrix[rowIndex*6 +colIndex];

	//////////////////////matrix multiplication/////////////
	//for(rowIndex = 0; rowIndex < 6; rowIndex++)
	//	for(colIndex = 0; colIndex < 6; colIndex++)
	//	{
	//		for(index = 0; index < NCP; index++)
	//		{
	//			tempProd = tempProd + transposeMat[rowIndex*NCP + index] * secondOrderMatrix[index*6 + colIndex];
	//		}
	//		prodMat[rowIndex*6 + colIndex] = tempProd;
	//		tempProd = 0;
	//	}

	//inverseMatrix(prodMat,invMat);

	////////finding inv(A) * transpose(A);
	//for(rowIndex = 0; rowIndex < 6; rowIndex++)
	//	for(colIndex = 0; colIndex < NCP; colIndex++)
	//	{
	//		for(index = 0; index < 6; index++)
	//		{
	//			tempProd = tempProd + invMat[rowIndex* 6 + index] * transposeMat[index*NCP + colIndex];
	//		}
	//		tMat[rowIndex*NCP + colIndex] = tempProd;
	//		tempProd = 0;
	//	}
	////////finding a coefficients///////////////
	for(rowIndex = 0; rowIndex < 6; rowIndex++)
	{
		for(index = 0; index < NCP; index++)
		{
			////the locations are the pixel values
			
				xCtrlPt = (loc[2*index].c_pos) - 0.5;
				tempProd = tempProd + invMat[rowIndex*NCP + index] * xCtrlPt;
			
				xCtrlPt1 = (loc[2*index+1].c_pos) - 0.5;
				tempProd1 = tempProd1 + invMat[rowIndex*NCP + index] * xCtrlPt1;
			
		}
		coeffVec[rowIndex].Acoeff = tempProd;
		tempProd = 0;
		coeffVec1[rowIndex].Acoeff = tempProd1;
		tempProd1 = 0;
	}
	////////finding b coefficients///////////////
	for(rowIndex = 0; rowIndex < 6; rowIndex++)
	{
		for(index = 0; index < NCP; index++)
		{
			
				yCtrlPt = iprowSize + 0.5 - (loc[2*index].r_pos);
				tempProd = tempProd + invMat[rowIndex*NCP + index] * yCtrlPt;
			
				yCtrlPt1 = iprowSize + 0.5 - (loc[2*index+1].r_pos);
				tempProd1 = tempProd1 + invMat[rowIndex*NCP + index] * yCtrlPt1;
			
		}
		coeffVec[rowIndex].Bcoeff = tempProd;
		tempProd = 0;
		coeffVec1[rowIndex].Bcoeff = tempProd1;
		tempProd1 = 0;
	}
	////////////////////////////////////////////////

	delete secondOrderMatrix;
	/*delete transposeMat;
	delete tMat;
	delete prodMat;*/
	delete invMat;
}
void modifyImage::imageMorphing(unsigned char *ipImgStart, unsigned char *ipImgEnd, unsigned char *opImg, double alpha)
{
	int imgIndex;
	//getchar();
	for(imgIndex = 0; imgIndex < iprowSize*ipcolSize*3; imgIndex++)
	{
		opImg[imgIndex] = ipImgStart[imgIndex] * (1 - alpha)+ ipImgEnd[imgIndex]*alpha;// * alpha;
	}
}


void modifyImage::inverseMatrix(double *ipmat, double *opmat)
{
	int dim = 6;
	double *augMat = new double[dim*dim];
	double temp[6][6];
	double *inv = new double[dim*dim];
	double *transpose = new double[dim*dim];
	int rI,cI;
	int itr1=0, itr2=0;
	int index1=0, index2 =0;
	double determinant = 0;
	//////////////initialization////////////
	
	for(cI = 0; cI< dim*dim; cI++)
	 {
		 augMat[cI] = 0;
		 inv[cI] = 0;
	 }
	
	 for(cI = 0; cI< dim*dim; cI++)
		 augMat[cI] = ipmat[cI];
	
	////////////////inverse using cofactor/////////////
	for(index1 =0; index1 < dim; index1++)
		for(index2 = 0; index2 < dim; index2++)
		{
			itr1 =0;
			itr2 =0;
			for(rI = 0; rI < dim; rI++)
				for(cI = 0; cI< dim; cI++)
				{
					temp[rI][cI] = 0;
					if(rI != index1 && cI != index2)
					{
						temp[itr1][itr2] = augMat[rI*dim+cI];
						if(itr2 < (dim-2))
							itr2++;
						else
						{
							itr2 = 0;
							itr1++;
						}
					}
				}
				inv[index1*dim+index2] = pow((double)-1,(index1+index2))*determinantOfMat(temp,dim-1);
		}

	for(rI = 0; rI < dim; rI++)
		for(cI = 0; cI< dim; cI++)
			transpose[cI*dim+rI] = inv[rI*dim+cI];

	///////////////////////////////////////////////////
	for(rI = 0; rI < dim; rI++)
		for(cI = 0; cI< dim; cI++)
			temp[rI][cI] = augMat[rI*dim+cI]; 

	determinant = determinantOfMat(temp,dim);

	cout<<determinant<<endl;

		for(cI = 0; cI< dim*dim; cI++)
			inv[cI] = transpose[cI] / determinant;

	/////////////////////////////////////////////////////
	for(rI = 0; rI < dim; rI++)
	{
		for(cI = 0; cI< dim; cI++)
			cout<<" " <<inv[rI*dim+cI];
		cout<<endl;
	}
	///////////inverse matrix output////////////////////
	
		for(cI = 0; cI< dim*dim; cI++)
			opmat[cI] = inv[cI]; 
	////////////////////////////////////////////////////
	delete augMat;
	delete inv;
	delete transpose;
}

double modifyImage::determinantOfMat(double ipMat[6][6],float order)
{
	int rowIndex, colIndex;
	int index, itr1, itr2;
	float sign = 1;
	double intermediateMat[6][6];
	double DofM;
	if(order == 1)
	{
		return ipMat[0][0];
	}
	else
	{
		DofM = 0;

		for(index = 0; index < order; index ++)
		{
			itr1 = 0;
			itr2 = 0;

			for(rowIndex =0; rowIndex<order; rowIndex++)
				for(colIndex =0; colIndex<order; colIndex++)
				{
					intermediateMat[rowIndex][colIndex] = 0;
					if(rowIndex !=0 && colIndex!=index)
					{
						intermediateMat[itr1][itr2] = ipMat[rowIndex][colIndex];

						if(itr2<(order-2))
							itr2++;
						else
						{
							itr2=0;
							itr1++;
						}
					}
				}
				DofM = DofM + sign * (ipMat[0][index] * determinantOfMat(intermediateMat, order-1));
				sign = -1 * sign;
			}
		}
	return DofM;
}
int modifyImage::bilinearT(unsigned char *ipImg, float pPrime, float qPrime)
{
	int rowVal, colVal;
	float rowRem, colRem;

	int opVal;
	rowVal = (int) pPrime;
	colVal = (int) qPrime;

	rowRem = pPrime - rowVal;
	colRem = qPrime - colVal;
	if(rowVal >=0 && rowVal < iprowSize-1 && colVal >=0 && colVal < ipcolSize-1)
		opVal = (1-rowRem)*(1-colRem)*ipImg[rowVal * ipcolSize + colVal] + 
			(1-rowRem)*(colRem)*ipImg[rowVal * ipcolSize + (colVal+1)] +
			(rowRem)*(1-colRem)*ipImg[(rowVal+1) * ipcolSize + colVal] +
			(rowRem)*(colRem)*ipImg[(rowVal+1) * ipcolSize + (colVal+1)] ;
	else
		opVal = 0;

	return opVal;
}
void modifyImage::getCoordinates(unsigned char *ipImg,int bkgrnd, int bytesperPixel)
{
	int* binImg = new int[iprowSize*ipcolSize];
	float avgVal;
	int rowIndex, colIndex;

	int minRow = iprowSize, maxRow = 0;
	int minCol = ipcolSize, maxCol = 0;

	//getchar();
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			if(bytesperPixel == 3)
				avgVal = (ipImg[3*(rowIndex*ipcolSize+colIndex)] + 
					ipImg[3*(rowIndex*ipcolSize+colIndex)+1] + 
					ipImg[3*(rowIndex*ipcolSize+colIndex)+2])/3;
			else
				avgVal = ipImg[rowIndex*ipcolSize+colIndex];

			if((avgVal < 255 && bkgrnd == WHITE) || (avgVal == 255 && bkgrnd == BLACK))
			{
				binImg[rowIndex*ipcolSize+colIndex] = 0;
				//outputImage[rowIndex*ipcolSize+colIndex] = 0;

				if(rowIndex <= minRow)
				{
					minRow = rowIndex;
					loc[1].r_pos = minRow;
					loc[1].c_pos = colIndex;
				}
				if(rowIndex > maxRow)
				{
					maxRow = rowIndex;
					loc[3].r_pos = maxRow;
					loc[3].c_pos = colIndex;
				}
				if(colIndex < minCol)
				{
					minCol = colIndex;
					loc[0].r_pos = rowIndex;
					loc[0].c_pos = minCol;
				}
				if(colIndex >= maxCol && colIndex < ipcolSize)
				{
					maxCol = colIndex;
					loc[2].r_pos = rowIndex;
					loc[2].c_pos = maxCol;
				}
			}
			else
			{
				binImg[rowIndex*ipcolSize+colIndex] = 1;
				//outputImage[rowIndex*ipcolSize+colIndex] = 255;

			}
		}

		rowMin = minRow;
		colMin = minCol;
		rowMax = maxRow;
		colMax = maxCol;

//		cout<<minRow<<endl;
//		cout<<maxRow<<endl;
//		cout<<minCol<<endl;
//		cout<<maxCol<<endl;

//		cout<<loc[0].r_pos<<", "<<loc[0].c_pos<<endl;
//		cout<<loc[1].r_pos<<", "<<loc[1].c_pos<<endl;
//		cout<<loc[2].r_pos<<", "<<loc[2].c_pos<<endl;
//		cout<<loc[3].r_pos<<", "<<loc[3].c_pos<<endl;
	//delete binImg;
}

float modifyImage::getTheta()
{
	float theta;
	int colDif, rowDif;

	colDif = loc[3].c_pos - loc[0].c_pos;
	rowDif = loc[3].r_pos - loc[0].r_pos;

	theta = atan((double)colDif/rowDif)*180/3.14159;

	cout<<theta<<endl;

	colDif = abs(loc[3].c_pos - loc[2].c_pos);
	rowDif = abs(loc[3].r_pos - loc[2].r_pos);

	theta = atan((double)rowDif/colDif)*180/3.14159;

	cout<<theta<<endl;

	return theta;
}

void modifyImage::segregateImage(unsigned char *ipImg)
{
	int rowIndex, colIndex;

	for(rowIndex = 0; rowIndex< iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			redComp[rowIndex*ipcolSize+colIndex] = ipImg[3*(rowIndex*ipcolSize+colIndex)];
			greenComp[rowIndex*ipcolSize+colIndex] = ipImg[3*(rowIndex*ipcolSize+colIndex)+1];
			blueComp[rowIndex*ipcolSize+colIndex] = ipImg[3*(rowIndex*ipcolSize+colIndex)+2];
		}
}

void modifyImage::rotateImage(unsigned char *ipImg, unsigned char *opImg, float theta)
{
	float pPrime, qPrime;

	int rowIndex, colIndex;

	theta = theta * 3.14159 /180;
	segregateImage(ipImg);

	for(rowIndex = 0; rowIndex< iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			///Modify for different sizes for ip and op
			pPrime = iprowSize + 0.5 + sin(theta) * (colIndex - 0.5) - cos(theta) * (iprowSize + 0.5 - rowIndex);
			qPrime = cos(theta) * (colIndex - 0.5) + sin(theta) * (iprowSize + 0.5 - rowIndex) + 0.5;

			opImg[3*(rowIndex*ipcolSize+colIndex)] = bilinearT(redComp,pPrime,qPrime);
			opImg[3*(rowIndex*ipcolSize+colIndex)+1] = bilinearT(greenComp,pPrime,qPrime);
			opImg[3*(rowIndex*ipcolSize+colIndex)+2] = bilinearT(blueComp,pPrime,qPrime);
		}

		setFilepath("../rotatedImage.raw");
		imageWriter(opImg, opcolSize*oprowSize*3);
}

void modifyImage::scaleImage(unsigned char* ipImg, unsigned char* opImg, float sx, float sy)
{
	float pPrime, qPrime;

	int rowIndex, colIndex;

	segregateImage(ipImg);

	for(rowIndex = 0; rowIndex<oprowSize; rowIndex++)
		for(colIndex = 0; colIndex < opcolSize; colIndex++)
		{
			///Modify for different sizes for ip and op
			pPrime = iprowSize + 0.5 - (oprowSize + 0.5 - rowIndex)/sy; ///check might be wrong
			qPrime = (colIndex - 0.5)/sx + 0.5;

			opImg[3*(rowIndex*opcolSize+colIndex)] = bilinearT(redComp,pPrime,qPrime);
			opImg[3*(rowIndex*opcolSize+colIndex)+1] = bilinearT(greenComp,pPrime,qPrime);
			opImg[3*(rowIndex*opcolSize+colIndex)+2] = bilinearT(blueComp,pPrime,qPrime);
		}

		setFilepath("../scaledImage.raw");
		imageWriter(opImg, opcolSize*oprowSize*3);
}

void modifyImage::translateImage(unsigned char* ipImg, unsigned char* opImg, float tx, float ty)
{
	float pPrime, qPrime;

	int rowIndex, colIndex;

	segregateImage(ipImg);

	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			pPrime = rowIndex + (0) + ty; ///Modify for different sizes for ip and op
			qPrime = colIndex - tx;

			opImg[3*(rowIndex*ipcolSize+colIndex)] = bilinearT(redComp,pPrime,qPrime);
			opImg[3*(rowIndex*ipcolSize+colIndex)+1] = bilinearT(greenComp,pPrime,qPrime);
			opImg[3*(rowIndex*ipcolSize+colIndex)+2] = bilinearT(blueComp,pPrime,qPrime);
		}
		setFilepath("../translatedImage.raw");
		imageWriter(opImg, opcolSize*oprowSize*3);
}
void modifyImage::setControlPoints(int triangleNum, int imgComb)
{
	int index;
	int *imagePtr = new int[30];
	FILE *coordinate;
	switch(triangleNum)
	{
	case 0:
		if(imgComb == 0)
			coordinate = fopen("../lionromneytriangle1.txt","rb");
		else if(imgComb == 1)
			coordinate = fopen("../romneyObamatriangle1.txt","rb");
		else
			coordinate = fopen("../extraCreditriangle1.txt","rb");
		//fread(imagePtr,sizeof(int), 24,coordinate);
		break;
	case 1:
		if(imgComb == 0)
			coordinate = fopen("../lionromneytriangle2.txt","rb");
		else if(imgComb == 1)
			coordinate = fopen("../romneyObamatriangle2.txt","rb");
		else
			coordinate = fopen("../extraCreditriangle2.txt","rb");
		break;
	case 2:
		if(imgComb == 0)
			coordinate = fopen("../lionromneytriangle3.txt","rb");
		else if(imgComb == 1)
			coordinate = fopen("../romneyObamatriangle3.txt","rb");
		else
			coordinate = fopen("../extraCreditriangle3.txt","rb");
		break;
	case 3:
		if(imgComb == 0)
			coordinate = fopen("../lionromneytriangle4.txt","rb");
		else if(imgComb == 1)
			coordinate = fopen("../romneyObamatriangle4.txt","rb");
		else
			coordinate = fopen("../extraCreditriangle4.txt","rb");
		break;
	}
	for(index = 0; index<12; index++)
		{
			fscanf(coordinate,"%d\n", &loc[index].r_pos);
			fscanf(coordinate,"%d\n", &loc[index].c_pos);
		}
	fclose(coordinate);
}

void modifyImage::mappcoefficients(unsigned char* ipImg, unsigned char* opImg, int imgNum)
{
	int rowIndex = 0, colIndex = 0;
	int a1=0, b1 = 0, c1 = 0;
	int a2=0, b2 = 0, c2 = 0;//// coefficients of line equation ax+by = c
	int xMid = 0, yMid =0;
	float uVal =0, vVal = 0;
	float pPrime = 0, qPrime = 0;
	float AB=0, BC=0, CA=0;
	int signAB = 0, signBC=0, signCA=0; 
	float xk=0, yj=0;
	
	yMid = (loc[4].r_pos + loc[5].r_pos)/2;
	xMid = (loc[4].c_pos + loc[5].c_pos)/2;
	////////////////triangle method/////////////////

	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
	{
		yj = iprowSize + 0.5 - rowIndex;
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			xk = colIndex - 0.5;
			AB = (loc[0].r_pos-rowIndex)*(xMid-colIndex) - (yMid-rowIndex)*(loc[0].c_pos-colIndex);
			BC = (yMid-rowIndex)*(loc[2].c_pos-colIndex) - (loc[2].r_pos-rowIndex)*(xMid-colIndex);
			CA = (loc[2].r_pos-rowIndex)*(loc[0].c_pos-colIndex) - (loc[0].r_pos-rowIndex)*(loc[2].c_pos-colIndex);

			if(AB ==0)
				signAB = 1;
			else
				signAB = (int)abs(AB)/AB;
			if(BC ==0)
				signBC = 1;
			else
				signBC = (int)abs(BC)/BC;
			if(CA ==0)
				signCA = 1;
			else
				signCA = (int)abs(CA)/CA;

			if((signAB == signBC)&&(signBC == signCA))
			{
				if(imgNum == 0)
				{
					uVal = coeffVec[0].Acoeff + coeffVec[1].Acoeff*xk + coeffVec[2].Acoeff*yj + 
						coeffVec[3].Acoeff*xk*xk + coeffVec[4].Acoeff*xk*yj + coeffVec[5].Acoeff*yj*yj;

					vVal = coeffVec[0].Bcoeff + coeffVec[1].Bcoeff*xk + coeffVec[2].Bcoeff*yj + 
						coeffVec[3].Bcoeff*xk*xk + coeffVec[4].Bcoeff*xk*yj + coeffVec[5].Bcoeff*yj*yj;
				}
				else
				{
					uVal = coeffVec1[0].Acoeff + coeffVec1[1].Acoeff*xk + coeffVec1[2].Acoeff*yj + 
						coeffVec1[3].Acoeff*xk*xk + coeffVec1[4].Acoeff*xk*yj + coeffVec1[5].Acoeff*yj*yj;

					vVal = coeffVec1[0].Bcoeff + coeffVec1[1].Bcoeff*xk + coeffVec1[2].Bcoeff*yj + 
						coeffVec1[3].Bcoeff*xk*xk + coeffVec1[4].Bcoeff*xk*yj + coeffVec1[5].Bcoeff*yj*yj;
				}

				pPrime = iprowSize + 0.5 - vVal;
				qPrime = uVal+0.5;
				opImg[3*(rowIndex*ipcolSize+colIndex)] = bilinearT(redComp,pPrime,qPrime);
				opImg[3*(rowIndex*ipcolSize+colIndex)+1] = bilinearT(greenComp,pPrime,qPrime);
				opImg[3*(rowIndex*ipcolSize+colIndex)+2] = bilinearT(blueComp,pPrime,qPrime);
			}
		}
	}
	
}
