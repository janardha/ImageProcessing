#include "modification.h"

void modifyImage::grayAlgo(unsigned char* ipImg)
{
	int rowIndex, colIndex;
	patternDB pDB;

	int Q[6] = {0,0,0,0,0,0};
	int mat[4] = {0,0,0,0};
	int indexN;
	char str[5];
	float Area = 0, EulerNum = 0, Perimeter = 0;
	float normArea = 0, normPerimeter = 0;
	float circ = 0, normCirc = 0;

	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
		for(colIndex = 0; colIndex<ipcolSize; colIndex++)
		{
			mat[0] = ipImg[rowIndex*ipcolSize+colIndex];
			mat[1] = ipImg[rowIndex*ipcolSize+(colIndex+1)];
			mat[2] = ipImg[(rowIndex+1)*ipcolSize+(colIndex)];
			mat[3] = ipImg[(rowIndex+1)*ipcolSize+(colIndex+1)];

			pDB.convert2String(str,mat);
			indexN = pDB.checkPattern(str);

			Q[indexN]++;
		}

	/////////////////////finding area/////////////////////
	Area = (Q[1] + 2 * Q[2] + 3 * Q[3] + 4 * Q[4] + 2 * Q[5])/4;
//	cout<<"Area "<<Area<<endl;
	normArea = Area / boundedArea;
//	cout<<"NOrmalized Area "<<normArea<<endl;
	/////////////////////////////////////////////////////
	//////////////////finding Perimeter//////////////////
	Perimeter = (Q[1] + Q[2] + Q[3] + 2 * Q[5]);
//	cout<<"Perimeter "<<Perimeter<<endl;

	normPerimeter = Perimeter / (2 * ((rowMax - rowMin) + (colMax - colMin)));
//	cout<<"normalized Perimeter "<<normPerimeter<<endl;
	/////////////////////////////////////////////////////
	//////////////////circularity////////////////////////
	circ = 4 * 3.14159 * Area / (Perimeter * Perimeter);
//	cout<<"circularity "<<circ<<endl;

	normCirc = 4 * 3.14159 * normArea / (normPerimeter * normPerimeter);
//	cout<<"normalized circularity "<<normCirc<<endl;
	/////////////////////////////////////////////////////
	//////////////////finding Euler Num//////////////////
//	EulerNum = (Q[1] - Q[3] + 2 * Q[5])/4; //4-connectivity
//	cout<<"euler number "<<EulerNum<<endl;
	EulerNum = (Q[1] - Q[3] - 2 * Q[5])/4; //8-connectivity
//	cout<<"euler number "<<EulerNum<<endl;
	/////////////////////////////////////////////////////

	normalizedArea = normArea;
	normalizedPerimeter = normPerimeter;
	eulerNumber = EulerNum;
	cirularity = circ;
}

void modifyImage::binaryConvertion(unsigned char *ipImg, unsigned char *opImg)
{
	int rowIndex, colIndex;
	float imgMean;

	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
		for(colIndex = 0; colIndex<ipcolSize; colIndex++)
		{
			imgMean = (ipImg[3*(rowIndex*ipcolSize+colIndex)]+ipImg[3*(rowIndex*ipcolSize+colIndex)+1]+
						ipImg[3*(rowIndex*ipcolSize+colIndex)+2])/3;
			if(imgMean > 100)
				opImg[rowIndex*ipcolSize+colIndex] = 255;
			else
				opImg[rowIndex*ipcolSize+colIndex] = 0;
		}
}

void modifyImage::trainingSet(char *lastPath, int maxItr, int extraCredit)
{
	int index = 1;
	char *p = "";
	char substr[3];
	//int zcr = 0;
	modImage = new unsigned char[iprowSize*ipcolSize];
	//getchar();
	
//	strcpy(imagePath1,"c:/users/public/images/ee569_hw3/prob3/1.raw");

	bytesPerPixelInOutput = 1;
	do{
		inputImageData = imageReader();

		if(extraCredit)
		{
			//do some more processing
		}
		else
			binaryConvertion(inputImageData, modImage);
		preprocessing(modImage);
		
		getCoordinates(modImage, WHITE, 1);
		boundedArea = (rowMax - rowMin) * (colMax - colMin);

		grayAlgo(modImage);
		spatialmoment(modImage);

		zeroCountCol = zeroCrossing(modImage,ipcolSize/2, 1); ///1 for zcr along the column
	//	cout<<"zcr column "<<zeroCountCol<<endl;

		zeroCountRow = zeroCrossing(modImage,iprowSize/2, 0); ///1 for zcr along the column
	//	cout<<"zcr row "<<zeroCountRow<<endl;

		determineCharacter();

	//	imageWriter(modImage, ipcolSize*iprowSize);
		itoa(index,substr,10);
		p = strstr(imagePath,substr);
		itoa(index+1,substr,10);

		if(index >=9)
		{
			setFilepath(lastPath);
		}
		else
			strncpy(p,substr,1);
	//	p = 
		puts(imagePath);

		
		index++;
		//getchar();
	}while(index <= maxItr);
}

void modifyImage::preprocessing(unsigned char *img)
{
	int rowIndex, colIndex;
	int blkR =0, blkC =0;
	int bond = 0;
	int mask[9] = {1,1,1,1,0,1,1,1,1};

	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
		for(colIndex = 0; colIndex<ipcolSize; colIndex++)
		{
			if((rowIndex < 10 || rowIndex > iprowSize-10) || 
				(colIndex < 10 || colIndex > ipcolSize-10))
				img[rowIndex*ipcolSize+colIndex] = 255;
		}

	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
		for(colIndex = 0; colIndex<ipcolSize; colIndex++)
		{
			for(blkR = -1; blkR<2; blkR++)
				for(blkC = -1; blkC<2; blkC++)
				{
					bond = bond + mask[(blkR+1)*3+(blkC+1)] * img[abs(rowIndex+blkR)*ipcolSize+abs(colIndex+blkC)]/255;
				}
			if(bond == 0 && img[rowIndex*ipcolSize+colIndex] == 255)
				img[rowIndex*ipcolSize+colIndex] = 0;
		}
	//		/*if(bond < 8)
	//			img[rowIndex*ipcolSize+colIndex] = 255;*/
	//	}
}

void modifyImage::spatialmoment(unsigned char *ipImg)
{
	int rowIndex, colIndex;
	float rowMoment =0, colMoment = 0;
	int zeroOrderMoment = 0;
	float crossMoment = 0;
	float xCentroid = 0, yCentroid = 0;


	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
		for(colIndex = 0; colIndex<ipcolSize; colIndex++)
		{
			zeroOrderMoment = zeroOrderMoment + ipImg[rowIndex*ipcolSize+colIndex]/255;
			rowMoment = rowMoment + (iprowSize - rowIndex + 0.5) * ipImg[rowIndex*ipcolSize+colIndex]/255;
			colMoment = colMoment + (colIndex + 0.5) * ipImg[rowIndex*ipcolSize+colIndex]/255;
		}

	rowMoment = rowMoment / iprowSize;
	colMoment = colMoment / ipcolSize;
	
	yCentroid = rowMoment / zeroOrderMoment;
	xCentroid = colMoment / zeroOrderMoment;

	xCOG = xCentroid;
	yCOG = yCentroid;

//	cout<<"Centroid x "<<xCentroid<<endl;
//	cout<<"Centroid y "<<yCentroid<<endl;
//	rowMoment = 0;
//	colMoment = 0;
////	zeroOrderMoment = 0;
//	for(rowIndex = 0; rowIndex<iprowSize; rowIndex++)
//		for(colIndex = 0; colIndex<ipcolSize; colIndex++)
//		{
//			crossMoment = crossMoment + (rowIndex + 0.5 - xCentroid) * (colIndex + 0.5 - yCentroid) 
//													* ipImg[rowIndex*ipcolSize+colIndex]/255;
//			rowMoment = rowMoment + pow((rowIndex + 0.5 - xCentroid),2) * ipImg[rowIndex*ipcolSize+colIndex]/255;
//			colMoment = colMoment + pow((colIndex + 0.5 - yCentroid),2) * ipImg[rowIndex*ipcolSize+colIndex]/255;
//		}
//
//		Order2RMoment = rowMoment / (iprowSize*iprowSize);
//		Order2CMoment = colMoment / (ipcolSize*ipcolSize);
//		Order2CrossMoment = crossMoment / (ipcolSize*iprowSize);
//		
//		////////////////normalization/////////////////////
//		Order2RMoment = Order2RMoment / zeroOrderMoment;
//		Order2CMoment = Order2CMoment / zeroOrderMoment;
//		Order2CrossMoment = Order2CrossMoment / zeroOrderMoment;
//		/////////////////////////////////////////////////
//
//		lambda1 = 0.5 * (Order2RMoment + Order2CMoment) + 0.5 * sqrt(pow(Order2RMoment,2) + pow(Order2CMoment,2) 
//												- 2 * Order2CMoment*Order2RMoment + 4 * pow(Order2CrossMoment,2));
//
//		lambda2 = 0.5 * (Order2RMoment + Order2CMoment) - 0.5 * sqrt(pow(Order2RMoment,2) + pow(Order2CMoment,2) 
//												- 2 * Order2CMoment*Order2RMoment + 4 * pow(Order2CrossMoment,2));
//
//	cout<<Order2RMoment<<endl;
//	cout<<Order2CMoment<<endl;
//	cout<<Order2CrossMoment<<endl;
//
//	cout<<"lambda1 "<<lambda1<<endl;
//	cout<<"lambda2 "<<lambda2<<endl;

}

int modifyImage::zeroCrossing(unsigned char *ipImg, int index, int rowORcol)
{
	int rowIndex = 0, colIndex = 0;
	int zeroCross =0;

	//modImage = new unsigned char[iprowSize*ipcolSize];
	
	//binaryConvertion(inputImageData, modImage);

	if(rowORcol == 1)
		for(rowIndex = 1; rowIndex<iprowSize; rowIndex++)
		{
			if((ipImg[rowIndex*ipcolSize+index]/255 == 0) && (ipImg[(rowIndex-1)*ipcolSize+index]/255 == 1))
				zeroCross++;
		}
	else if(rowORcol == 0)
		for(colIndex = 1; colIndex<ipcolSize; colIndex++)
		{
			if((ipImg[index*ipcolSize+colIndex]/255 == 0) && (ipImg[index*ipcolSize+(colIndex-1)]/255 == 1))
				zeroCross++;
		}
	else
		for(colIndex = 1,rowIndex =1; colIndex<ipcolSize; colIndex++,rowIndex++)
		{
			if((ipImg[rowIndex*ipcolSize+colIndex]/255 == 0) && (ipImg[(rowIndex-1)*ipcolSize+(colIndex-1)]/255 == 1))
				zeroCross++;
		}
//		cout<<zeroCross<<endl;
	return zeroCross;
}

void modifyImage::determineCharacter()
{
	if(eulerNumber == 2)
	{
		cout<<"THE CHARACTER is 8"<<endl;
	}
	else if(eulerNumber == 3)
	{
		if(xCOG > 0.5 && yCOG > 0.5)
			cout<<"THE CHARACTER is 6"<<endl;
		else
		{
			if(cirularity < 0.14)
				cout<<"THE CHARACTER is 9"<<endl;
			else
				cout<<"THE CHARACTER is J"<<endl;
		}
	}
	else
	{
		if(zeroCountCol == 3)
		{
			if(xCOG < 0.5)
				cout<<"THE CHARACTER is 5"<<endl;
			else
				cout<<"THE CHARACTER is F"<<endl;
		}
		else if(zeroCountCol == 2)
		{
			// shifted column zero crossing 
			
			if(cirularity < 0.8 && normalizedPerimeter > 1.6)
				cout<<"THE CHARACTER is C"<<endl;
			else
			{
				zeroCountCol = zeroCrossing(modImage,0, 3); ///1 for zcr along the column
				if(zeroCountCol == 1)
					if(xCOG > 0.5)
						cout<<"THE CHARACTER is F"<<endl;
					else
						cout<<"THE CHARACTER is J"<<endl;
				else
					cout<<"THE CHARACTER is 7"<<endl;
			}
		}
		else
		{
			if(zeroCountRow == 1)
				cout<<"THE CHARACTER is J"<<endl;
			else
			{
				if(xCOG < 0.5)
					cout<<"THE CHARACTER is U"<<endl;
				else
					cout<<"THE CHARACTER is K"<<endl;
			}
		}
	}
}