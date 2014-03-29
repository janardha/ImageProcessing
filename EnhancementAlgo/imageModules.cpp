//Rajani Janardhana
//janardha@usc.edu
//28th September 2012

#include "homework_1.h"
void homework_1::imageReader(int image_prop, char *image_path[])
{
	//int errorNum = fopen_s(&Input_file_pointer,image_path[2],"rb");
	int errorNum = fopen_s(&Input_file_pointer,"c:/users/public/images/desk.raw","rb");

	if(errorNum)
	{
		cout<<"Error: The file cannot be opened"<<endl;
	}
	rowSize = atoi(image_path[4]);
	colSize = atoi(image_path[5]);
	bytesInPixel = atoi(image_path[6]);

	cout<<"row size = "<<rowSize<<endl;
	cout<<"col size = "<<colSize<<endl;
	cout<<"bytes in pixel size = "<<bytesInPixel<<endl;

	Input_image_data = (unsigned char *)malloc(rowSize*colSize*bytesInPixel);
	fread(Input_image_data,sizeof(unsigned char), rowSize*colSize*bytesInPixel,Input_file_pointer);

	cout<<Input_image_data[10]<<endl;
	cout<<"File read successful"<<endl;

	fclose(Input_file_pointer);
	//free(Input_image_data);
}
void homework_1::imageWriter(char *image_path[])
{
	int errorNum = fopen_s(&Output_file_pointer,image_path[3],"wb");
	if(errorNum)
	{
		cout<<"Error: The file cannot be opened"<<endl;
		return;
	}

	cout<<Output_image[10]<<endl;

	fwrite(Output_image, sizeof(unsigned char), rowSize*colSize*bytesPerPixelInOutput, Output_file_pointer);
	fclose(Output_file_pointer);

}

void homework_1::grayScaleConverter_luminosity()
{
	int grayImageIndex = 0;
	int colorImageIndex = 0;

	printf("inside gray scale luminosity method\n");

	Gray_image = (unsigned char *)malloc(rowSize*colSize);
	
	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
	{
		Gray_image[grayImageIndex] = 0.21 * Input_image_data[colorImageIndex++] + 
										0.72 * Input_image_data[colorImageIndex++] +
										0.07 * Input_image_data[colorImageIndex++];

	}


	Output_image = Gray_image;
	bytesPerPixelInOutput = 1;
}

void homework_1::grayScaleConverter_avg()
{
	int grayImageIndex = 0;
	int colorImageIndex = 0;

	
	printf("inside gray scale averaging method\n");

	Gray_image = (unsigned char *)malloc(rowSize*colSize);
	
	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
	{
		Gray_image[grayImageIndex] = (Input_image_data[colorImageIndex++] + 
										Input_image_data[colorImageIndex++] +
										Input_image_data[colorImageIndex++]) / 3;
		
	}

	Output_image = Gray_image;
	bytesPerPixelInOutput = 1;
}

void homework_1::defaultDisplayInput()
{
	Output_image = Input_image_data;
	bytesPerPixelInOutput = 3;
}

void homework_1::histogramGeneration()
{
	
	int grayImageIndex;
	int histIndex;
	int grayLevel;
	int maxVal = 0;
	
	cout<<"INside histogram"<<endl;
	//open the file to write the histgram into
	int errorNum = fopen_s(&hist_out,"c:/users/public/images/histOut.dat","wb");
	if(errorNum)
	{
		cout<<"Error: The file cannot be opened"<<endl;
		return;
	}

	for(histIndex = 0; histIndex < 256; histIndex++)
		histogram[histIndex] = 0;

	for(grayImageIndex = 0; grayImageIndex < rowSize*colSize; grayImageIndex++)
	{
		grayLevel = Gray_image[grayImageIndex];
		
		histogram[grayLevel]++;
	}
	for(histIndex = 0; histIndex < 256; histIndex++)
		fprintf(hist_out,"%d\n",histogram[histIndex]);

	//fwrite(histogram, sizeof(int), 256, hist_out);
	fclose(hist_out);

}
