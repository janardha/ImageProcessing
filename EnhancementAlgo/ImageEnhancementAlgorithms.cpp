////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//28th September 2012
////////////////////////////////////////////////////////
#include "processImage.h"


void processImage::grayScaleConverter_luminosity()
{
	/* using the formula g = 0.21 REd + 0.72 * Green + 0.07 * Blue*/
	int grayImageIndex = 0;
	int colorImageIndex = 0;

	printf("inside gray scale luminosity method\n");

	grayImage = (unsigned char *)malloc(rowSize*colSize);
	
	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
	{
		grayImage[grayImageIndex] = 0.21 * inputImageData[colorImageIndex++] + 
										0.72 * inputImageData[colorImageIndex++] +
										0.07 * inputImageData[colorImageIndex++];

	}

	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
		outputImage[grayImageIndex] = grayImage[grayImageIndex];

	bytesPerPixelInOutput = 1;
}

void processImage::grayScaleConverter_avg()
{
	int grayImageIndex = 0;
	int colorImageIndex = 0;

	
	printf("inside gray scale averaging method\n");

	
	
	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
	{
		grayImage[grayImageIndex] = (inputImageData[colorImageIndex++] + 
										inputImageData[colorImageIndex++] +
										inputImageData[colorImageIndex++]) / 3;
		
	}

	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
		outputImage[grayImageIndex] = grayImage[grayImageIndex];

	bytesPerPixelInOutput = 1;
}


void processImage::histogramGeneration(unsigned char* imageHist)
{
	
	int grayImageIndex;
	int histIndex;
	int grayLevel;
	int maxVal = 0;
	
	int max = 0;
	int min =0;
//	cout<<"INside histogram"<<endl;
	//open the file to write the histgram into
	int errorNum = fopen_s(&hist_out,"../histOut.dat","wb");
	if(errorNum)
	{
		cout<<"Error: The file cannot be opened"<<endl;
		return;
	}

	for(histIndex = 0; histIndex < 256; histIndex++)
		histogram[histIndex] = 0;

	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
	{
		grayLevel = imageHist[grayImageIndex];
		
		histogram[grayLevel]++;
	}
	
	for(histIndex = 0; histIndex < 256; histIndex++)
		fprintf(hist_out,"%d\n",histogram[histIndex]);

	//fwrite(histogram, sizeof(int), 256, hist_out);
	fclose(hist_out);

}

void processImage::linearFiltering()
{
	//Observing the histogram the concetration is high between 0 and 50
	// hence normalizing the this range to 0-255
	// all the pixel above 50 are equated to 255
	// using formula G = Gmin + (Gmax-Gmin)/(Fmax - Fmin)*(F - Fmin)
	int imageIndex;

	
	for(imageIndex = 0;imageIndex < rowSize*colSize; imageIndex++)
		if(grayImage[imageIndex]<70)
			outputImage[imageIndex] = 5 + (120/70) * grayImage[imageIndex];
		else
			outputImage[imageIndex] = 255;//;150 + ((255-150)/(255 - 70))*(grayImage[imageIndex] - 70);//grayImage[imageIndex];
}

void processImage::squareRootFiltering()
{
	//Observing the histogram the concetration is high between 0 and 50
	// hence normalizing the this range to 0-255
	// all the pixel above 50 are equated to 255
	// using formula G = Gmin + (Gmax-Gmin)/(Fmax - Fmin)*(F - Fmin)
	int imageIndex;

	for(imageIndex = 0;imageIndex < rowSize*colSize; imageIndex++)
		if(grayImage[imageIndex]<50)
			outputImage[imageIndex] = 0+(255/50) * sqrt((double)grayImage[imageIndex]);
		else
			outputImage[imageIndex] = 255;// grayImage[imageIndex];

}

void processImage::cumulativeHistogramEqualization()
{
	int imageIndex;
	int histIndex;
	float cumulativeHist[256];

	histogramGeneration(inputImageData);

	int errorNum = fopen_s(&hist_out,"../cumulative.dat","wb");
	if(errorNum)
	{
		cout<<"Error: The file cannot be opened"<<endl;
		return;
	}
	for(histIndex = 0; histIndex < 256; histIndex++)
	{
		cumulativeHist[histIndex] = 0;
		
	}

	cumulativeHist[0] = histogram[0];
	for(histIndex = 1; histIndex < 256; histIndex++)
	{
		cumulativeHist[histIndex] = cumulativeHist[histIndex - 1] + histogram[histIndex];
		
	}
	for(histIndex = 0; histIndex < 256; histIndex++)
		fprintf(hist_out,"%f\n",cumulativeHist[histIndex]);

	for(histIndex = 0; histIndex < 256; histIndex++)
	{
		cumulativeHist[histIndex] = cumulativeHist[histIndex] / (rowSize *colSize);
	}

	for(imageIndex = 0; imageIndex < rowSize*colSize; imageIndex++)
	{
		histIndex = grayImage[imageIndex];
		
		outputImage[imageIndex] = (255 - 15)*cumulativeHist[histIndex] + 15;
	}

	

	fclose(hist_out);

	histogramGeneration(outputImage);
	
}

void processImage::digitalHistogramEqulization()
{
	int inputHistLevel = 0;
	int outputHistogram[256];
	int inputHist[256];
	int imageIndex;
	int rowIndex;
	int colIndex;
	int localHistIndex = 0;
	int histIndex = 0;

	histogramGeneration(grayImage);
	for(localHistIndex = 0; localHistIndex < 256; localHistIndex++)
	{
		//making a local copy of the histogram that is generated for input image
		inputHist[localHistIndex] = histogram[localHistIndex]; 
		//initializing the output histogram to zero
		outputHistogram[localHistIndex] = 0;
//		cout<<inputHist[localHistIndex]<<endl;
	}

//	while loop is run until all the pixels of the input are assigned to the output
//	which happens when the input gray level reaches 255 and the histogram value reaches zero

	while(!(inputHistLevel == 255 && inputHist[inputHistLevel] <= 0))
	{
		//image is scanned for a particular input gray level 
		//the loop is reset everytime a input gray level reaches zero
		for(imageIndex = 0; imageIndex < rowSize * colSize; imageIndex++)
		{
			if(outputHistogram[histIndex] >= (rowSize*colSize/256) && histIndex < 255)
			{
				//if the output gray level reaches saturation it is incremented
				histIndex++;
			}
			
			if(inputHist[inputHistLevel] <= 0 && inputHistLevel < 255)
			{
				//when the input histlevel has no more pixels available in that particular graylevel
				//the input level is incremented and the counter is reset to start scanning for the 
				//top most pixel
				inputHistLevel++;
				imageIndex = 0;
			}
			
			if(grayImage[imageIndex] == inputHistLevel)
			{
				//every time a output put is assigned with the output graylevel
				//output histogram graylevel value is incremented by 1
				//and at the same time the input histogram gray level is decremeted by 1
				outputImage[imageIndex] = histIndex;
				outputHistogram[histIndex]++;
				inputHist[inputHistLevel]--;
			}
		}
	}
	histogramGeneration(outputImage);
}
void processImage::localContrastEnhancement()
{
	//Observing the histogram the concetration is high between 0 and 50
	// hence normalizing the this range to 0-120
	// all the pixel above 50 arenormalized to 120-255
	// using formula G = Gmin + (Gmax-Gmin)/(Fmax - Fmin)*function(F - Fmin)
	int imageIndex;

	//the gray levels 
	for(imageIndex = 0;imageIndex < rowSize*colSize; imageIndex++)
		if(grayImage[imageIndex]< 70)
			outputImage[imageIndex] = 5+(150/70) *(grayImage[imageIndex]);
		else
			outputImage[imageIndex] = 155 + ((255-155)/(255 - 70))*(grayImage[imageIndex] - 70);
}
