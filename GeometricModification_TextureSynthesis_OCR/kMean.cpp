#include "modification.h"

void modifyImage::kmeanAlgorithm()
{
	int N = 5;
	int numOfFeatures = 26;
	int numOfTextures = 5;
	double errorTol = 0.000001;
	int index;
	int rowIndex, colIndex;
	float dist[5] = {0,0,0,0,0};

	//getchar();
	double **distance = (double **)malloc(sizeof(double)*numOfFeatures);
	int *output = new int[iprowSize*ipcolSize];
	double **centroids =  (double**)calloc(numOfTextures, sizeof(double*));
	for(index = 0; index < numOfFeatures; index++)
	{
		distance[index] = (double *)malloc(sizeof(double)*iprowSize*ipcolSize);
	}

	for(index = 0; index < numOfTextures; index++)
	{
		centroids[index] = (double*)calloc(numOfFeatures, sizeof(double));
	}
	
	for(index = 0; index < numOfFeatures; index++)
	{
		centroids[0][index] = tIP[index].img[10*ipcolSize+10];
		centroids[1][index] = tIP[index].img[10*ipcolSize+192];
		centroids[2][index] = tIP[index].img[128*ipcolSize+128];
		centroids[3][index] = tIP[index].img[192*ipcolSize+10];
		centroids[4][index] = tIP[index].img[192*ipcolSize+192];
	}

	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			tIP[25].img[rowIndex*ipcolSize+colIndex] = (double)rowIndex*0.05/iprowSize;
			tIP[26].img[rowIndex*ipcolSize+colIndex] = (double)colIndex*0.05/ipcolSize;
		}
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			for(index = 0; index < numOfFeatures; index++)
			{
				distance[index][rowIndex*ipcolSize+colIndex] = tIP[index+1].img[rowIndex*ipcolSize+colIndex];
			//	cout<<distance[index][rowIndex*ipcolSize+colIndex];
			}
		//	getchar();
		}
	//	getchar();
			output = k_means(distance, iprowSize*ipcolSize, numOfFeatures, numOfTextures, errorTol, centroids);

	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
		//	cout<<output[rowIndex*ipcolSize+colIndex];
			outputImage[rowIndex*ipcolSize+colIndex] = output[rowIndex*ipcolSize+colIndex]*255/5;
		}
	//	cout<<endl;
	}


	////////////free all memeory used////////////
	delete output;
	for(index = 0; index < numOfFeatures; index++)
	{
		free(distance[index]);
	}
	free(distance);
	free(centroids);
	////////////////////////////////////////////
}

void modifyImage::kmeanAlgorithmReducedFeatures()
{
	int N = 5;
	int numOfFeatures = 15;
	int numOfTextures = 5;
	double errorTol = 0.000001;
	int index;
	int rowIndex, colIndex;
	float dist[5] = {0,0,0,0,0};

	//getchar();
	double **distance = (double **)malloc(sizeof(double)*numOfFeatures);
	int *output = new int[iprowSize*ipcolSize];
	double **centroids =  (double**)calloc(numOfTextures, sizeof(double*));
	for(index = 0; index < numOfFeatures; index++)
	{
		distance[index] = (double *)malloc(sizeof(double)*iprowSize*ipcolSize);
	}

	for(index = 0; index < numOfTextures; index++)
	{
		centroids[index] = (double*)calloc(numOfFeatures, sizeof(double));
	}
	
	for(index = 0; index < numOfFeatures; index++)
	{
		centroids[0][index] = tIP[index].img[10*ipcolSize+10];
		centroids[1][index] = tIP[index].img[10*ipcolSize+192];
		centroids[2][index] = tIP[index].img[128*ipcolSize+128];
		centroids[3][index] = tIP[index].img[192*ipcolSize+10];
		centroids[4][index] = tIP[index].img[192*ipcolSize+192];
	}

	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
			tIP[25].img[rowIndex*ipcolSize+colIndex] = (double)rowIndex*0.05/iprowSize;
			tIP[26].img[rowIndex*ipcolSize+colIndex] = (double)colIndex*0.05/ipcolSize;
		}
	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
				distance[0][rowIndex*ipcolSize+colIndex] = tIP[1].img[rowIndex*ipcolSize+colIndex];
				distance[1][rowIndex*ipcolSize+colIndex] = tIP[2].img[rowIndex*ipcolSize+colIndex];
				distance[2][rowIndex*ipcolSize+colIndex] = tIP[6].img[rowIndex*ipcolSize+colIndex];
				distance[3][rowIndex*ipcolSize+colIndex] = tIP[8].img[rowIndex*ipcolSize+colIndex];
				distance[4][rowIndex*ipcolSize+colIndex] = tIP[10].img[rowIndex*ipcolSize+colIndex];
				distance[5][rowIndex*ipcolSize+colIndex] = tIP[11].img[rowIndex*ipcolSize+colIndex];
				distance[6][rowIndex*ipcolSize+colIndex] = tIP[12].img[rowIndex*ipcolSize+colIndex];
				distance[7][rowIndex*ipcolSize+colIndex] = tIP[15].img[rowIndex*ipcolSize+colIndex];
				distance[8][rowIndex*ipcolSize+colIndex] = tIP[16].img[rowIndex*ipcolSize+colIndex];
				distance[9][rowIndex*ipcolSize+colIndex] = tIP[18].img[rowIndex*ipcolSize+colIndex];
				distance[10][rowIndex*ipcolSize+colIndex] = tIP[20].img[rowIndex*ipcolSize+colIndex];
				distance[11][rowIndex*ipcolSize+colIndex] = tIP[14].img[rowIndex*ipcolSize+colIndex];
				distance[12][rowIndex*ipcolSize+colIndex] = tIP[22].img[rowIndex*ipcolSize+colIndex];
				distance[13][rowIndex*ipcolSize+colIndex] = tIP[25].img[rowIndex*ipcolSize+colIndex];
				distance[14][rowIndex*ipcolSize+colIndex] = tIP[26].img[rowIndex*ipcolSize+colIndex];
			
		//	getchar();
		}
	//	getchar();
			output = k_means(distance, iprowSize*ipcolSize, numOfFeatures, numOfTextures, errorTol, centroids);

	for(rowIndex = 0; rowIndex < iprowSize; rowIndex++)
	{
		for(colIndex = 0; colIndex < ipcolSize; colIndex++)
		{
		//	cout<<output[rowIndex*ipcolSize+colIndex];
			outputImage[rowIndex*ipcolSize+colIndex] = output[rowIndex*ipcolSize+colIndex]*255/5;
		}
	//	cout<<endl;
	}


	////////////free all memeory used////////////
	delete output;
	for(index = 0; index < numOfFeatures; index++)
	{
		free(distance[index]);
	}
	free(distance);
	free(centroids);
	////////////////////////////////////////////
}