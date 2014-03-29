////////////////////////////////////////////////////////
//Rajani Janardhana
//janardha@usc.edu
//19th October 2012
////////////////////////////////////////////////////////
#include "filter.h"
patternDB::patternDB()
{
	//matrixString=NULL;
	generateConditionalTables();
	generateUnconditionalTableShrinkNthin();
}
patternDB::~patternDB()
{
	//do nothing
}
bool patternDB::checkConditionTable1(int bondNo, int mat[], int MorphType)
{
	char matrixString[10];
	bool setVar = false;
	int index, maxItr;
	//getchar();
	convert2String(matrixString,mat);

	if(((C1Table[bondNo-1].shrink) && MorphType == SHRINK) || 
		((C1Table[bondNo-1].thin) && MorphType == THIN) ||
		((C1Table[bondNo-1].skeletonize) && MorphType == SKEL))
	{
		maxItr = C1Table[bondNo-1].numOFPatterns;
		for(index = 0; index < maxItr; index++)
		{
			if(strcmp(matrixString,C1Table[bondNo-1].pattern[index]) == 0)
				setVar = true;
		}	
	}
	else if(bondNo == 4 && (MorphType == THIN || MorphType == SKEL) && !setVar)
	{
		maxItr = C1Table[11].numOFPatterns; 
		for(index = 0; index < maxItr; index++)
		{
			if(strcmp(matrixString,C1Table[11].pattern[index]) == 0)
				setVar = true;
		}	
	}
	else if(bondNo == 6 && (MorphType == THIN || MorphType == SHRINK) && !setVar)
	{
		maxItr = C1Table[12].numOFPatterns; 
		for(index = 0; index < maxItr; index++)
		{
			if(strcmp(matrixString,C1Table[12].pattern[index]) == 0)
				setVar = true;
		}
	}
	return setVar;
}
bool patternDB::checkConditionTable2(int bondNo, int mat[], int MorphType)
{
	char matrixString[10];
	bool setVar = false;
	int index, maxItr;
	//getchar();
	convert2String(matrixString, mat);

	if(((C2TableST[bondNo-1].shrink) && MorphType == SHRINK) || 
		((C2TableST[bondNo-1].thin) && MorphType == THIN))
	{
		maxItr = C2TableST[bondNo-1].numOFPatterns;
		for(index = 0; (index < maxItr) && !setVar; index++)
		{
			if(strcmp(matrixString,C2TableST[bondNo-1].pattern[index]) == 0)
				setVar = true;
		}	
	}
	else if((C2TableK[bondNo-1].skeletonize) && MorphType == SKEL)
	{
		maxItr = C2TableK[bondNo-1].numOFPatterns;
		for(index = 0; (index < maxItr) && !setVar; index++)
		{
			if(strcmp(matrixString,C2TableK[bondNo-1].pattern[index]) == 0)
				setVar = true;
		}
	}

	return setVar;
}
void patternDB::convert2String(char *matstr,int mat[])
{
	int index = 0;
//	char matpattern[10];

	if(mat[index] == 0)
		strcpy(matstr, "0");
	else
		strcpy(matstr, "1");
	for(index = 1; index < 9; index++)
	{
		if(mat[index] == 0)
			strcat(matstr, "0");
		else
			strcat(matstr, "1");
	}
	 
//	cout<<mat[0]<<mat[1]<<mat[2]<<mat[3]<<mat[4]<<mat[5]<<mat[6]<<mat[7]<<mat[8]<<endl;
//	cout<<matpattern<<endl;
//	return matrixString;
}
void patternDB::generateConditionalTables()
{
	tblDB table;

	table.bond = 1;
	table.pattern[0] = "001010000";
	table.pattern[1] = "100010000";
	table.pattern[2] = "000010100";
	table.pattern[3] = "000010001";
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = false;

	C1Table[0] = table;

	table.bond = 2;
	table.pattern[0] = "000011000";
	table.pattern[1] = "010010000";
	table.pattern[2] = "000110000";
	table.pattern[3] = "000010010";
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = false;

	C1Table[1] = table;

	table.bond = 3;
	table.pattern[0] = "001011000";
	table.pattern[1] = "011010000";
	table.pattern[2] = "110010000";
	table.pattern[3] = "100110000";
	table.pattern[4] = "000110100";
	table.pattern[5] = "000010110";
	table.pattern[6] = "000010011";
	table.pattern[7] = "000011001";
	table.numOFPatterns = 8;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = false;

	C1Table[2] = table;

	table.bond = 4;
	table.pattern[0] = "001011001";
	table.pattern[1] = "111010000";
	table.pattern[2] = "100110100";
	table.pattern[3] = "000010111";
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = true;
	table.thin = true;

	C1Table[3] = table;

	table.bond = 5;
	table.pattern[0] = "110011000";
	table.pattern[1] = "010011001";
	table.pattern[2] = "011110000";
	table.pattern[3] = "001011010";
	table.pattern[4] = "011011000";
	table.pattern[5] = "110110000";
	table.pattern[6] = "000110110";
	table.pattern[7] = "000011011";
	table.numOFPatterns = 8;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C1Table[4] = table;

	table.bond = 6;
	table.pattern[0] = "111011000";
	table.pattern[1] = "011011001";
	table.pattern[2] = "111110000";
	table.pattern[3] = "110110100";
	table.pattern[4] = "100110110";
	table.pattern[5] = "000110111";
	table.pattern[6] = "000011111";
	table.pattern[7] = "001011011";
	table.numOFPatterns = 8;
	table.shrink = true;
	table.skeletonize = true;
	table.thin = true;

	C1Table[5] = table;

	table.bond = 7;
	table.pattern[0] = "111011001";
	table.pattern[1] = "111110100";
	table.pattern[2] = "100110111";
	table.pattern[3] = "001011111";
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = true;
	table.thin = true;

	C1Table[6] = table;

	table.bond = 8;
	table.pattern[0] = "011011011";
	table.pattern[1] = "111111000";
	table.pattern[2] = "110110110";
	table.pattern[3] = "000111111";
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = true;
	table.thin = true;

	C1Table[7] = table;

	table.bond = 9;
	table.pattern[0] = "111011011";
	table.pattern[1] = "011011111";
	table.pattern[2] = "111111100";
	table.pattern[3] = "111111001";
	table.pattern[4] = "111110110";
	table.pattern[5] = "110110111";
	table.pattern[6] = "100111111";
	table.pattern[7] = "001111111";

	table.numOFPatterns = 8;
	table.shrink = true;
	table.skeletonize = true;
	table.thin = true;

	C1Table[8] = table;

	table.bond = 10;
	table.pattern[0] = "111011111";
	table.pattern[1] = "111111101";
	table.pattern[2] = "111110111";
	table.pattern[3] = "101111111";
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = true;
	table.thin = true;

	C1Table[9] = table;

	table.bond = 11;
	table.pattern[0] = "111111011";
	table.pattern[1] = "111111110";
	table.pattern[2] = "110111111";
	table.pattern[3] = "011111111";
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C1Table[10] = table;
	
	table.bond = 4;
	table.pattern[0] = "010011000";
	table.pattern[1] = "010110000";
	table.pattern[2] = "000110010";
	table.pattern[3] = "000011010";
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = true;

	C1Table[11] = table;

	table.bond = 6;
	table.pattern[0] = "110011001";
	table.pattern[1] = "011110100";
	table.numOFPatterns = 2;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C1Table[12] = table;

}

void patternDB::generateUnconditionalTableShrinkNthin()
{
	tblDB table;

	//M is assumed to be 1 and A, B, C and D values are varied and sorted into groups based on bond

	table.bond = 1;
	table.pattern[0] = "001010000";
	table.pattern[1] = "100010000";
	table.numOFPatterns = 2;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[0] = table;

	table.bond = 2;
	table.pattern[0] = "000010010";
	table.pattern[1] = "000011000";
	table.numOFPatterns = 2;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[1] = table;

	table.bond = 3;
	//L-cluster
	table.pattern[0] = "001011000";
	table.pattern[1] = "011010000";
	table.pattern[2] = "110010000";
	table.pattern[3] = "100110000";
	table.pattern[4] = "000110100";
	table.pattern[5] = "000010110";
	table.pattern[6] = "000010011";
	table.pattern[7] = "000011001";
	//vee branch d=0;
	table.pattern[8] = "101010100";//a=1 || c=1
	table.pattern[9] = "100010101";//a=1 || c=1
	table.pattern[10] = "001010101";//a=1 || c=1
	table.pattern[11] = "101010001";//a=1 || c=1

	table.numOFPatterns = 12;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[2] = table;

	table.bond = 4;
	//4-connected Offset
	table.pattern[0] = "011110000";
	table.pattern[1] = "110011000";
	table.pattern[2] = "010011001";
	table.pattern[3] = "001011010";
	//spur corner cluster
	table.pattern[4] = "011010100";//a=1
	table.pattern[5] = "001011100";//b=1
	table.pattern[6] = "100110001";//a=1
	table.pattern[7] = "110010001";//b=1
	table.pattern[8] = "001110100";//a=1
	table.pattern[9] = "001010110";//b=1
	table.pattern[10] = "100010011";//a=1
	table.pattern[11] = "100011001";//b=1
	//vee branch d=0
	table.pattern[12] = "101010101";////a=c=1
	table.pattern[13] = "101010010";////b=1
	table.pattern[14] = "100011100";////b=1
	table.pattern[15] = "010010101";////b=1
	table.pattern[16] = "001110001";//b=1
	table.numOFPatterns = 17;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[3] = table;

	table.bond = 5;
	//corner cluster
	table.pattern[0] = "110110000"; //d=0
	//diagonal branch d = 0
	table.pattern[1] = "010011100";//a=1, b=1
	table.pattern[2] = "010110001";//a=1, b=1
	table.pattern[3] = "001110010";//a=1, b=1
	table.pattern[4] = "100011010";//a=1, b=1
	//vee branch d=0
	table.pattern[5] = "101010110";//a=1, b=1
	table.pattern[6] = "100011101";//a=1, b=1
	table.pattern[7] = "011010101";//a=1, b=1
	table.pattern[8] = "101110001";//a=1, b=1
	table.pattern[9] = "101010011";//c=1, b=1
	table.pattern[10] = "101011100";//c=1, b=1
	table.pattern[11] = "110010101";//c=1, b=1
	table.pattern[12] = "001110101";//c=1, b=1
	table.pattern[13] = "111010100";
	table.pattern[14] = "111010001";
	table.pattern[15] = "101011001";
	table.pattern[16] = "101110100";

	table.numOFPatterns = 17;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[4] = table;

	table.bond = 6;
	//Spur corner cluster
	table.pattern[0] = "011011100";//a=1, b=1
	table.pattern[1] = "110110001";//a=1, b=1
	table.pattern[2] = "001110110";//a=1, b=1
	table.pattern[3] = "100011011";//a=1, b=1
	//tee branch d = 0
	table.pattern[4] = "010111000";
	table.pattern[5] = "000111010";
	table.pattern[6] = "101110010";
	table.pattern[7] = "010011010";
	table.pattern[8] = "110110100"; 
	table.pattern[9] = "111110000";
	table.pattern[10] = "110011100";
	table.pattern[11] = "010011101";
	table.pattern[12] = "011110001";
	table.pattern[13] = "010110101";
	table.pattern[14] = "001110011";
	table.pattern[15] = "101011010";
	table.pattern[16] = "100011110";
	table.pattern[17] = "111010101";
	table.pattern[18] = "111010010";
	table.pattern[19] = "101011101";
	table.pattern[20] = "101110101";

	table.numOFPatterns = 21;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[5] = table;

	table.bond = 7;
	//diagonal branch d = 1
	table.pattern[0] = "110011101";
	table.pattern[1] = "011110101";
	table.pattern[2] = "101110011";
	table.pattern[3] = "101011110";
	table.pattern[4] = "110111000";
	table.pattern[5] = "110110010";
	table.pattern[6] = "110110101";
	table.pattern[7] = "111110001";
	table.pattern[8] = "111110100";
	table.pattern[9] = "010111100";
	table.pattern[10] = "010111001";
	table.pattern[11] = "011111000";
	table.pattern[12] = "001111010";
	table.pattern[13] = "000111011";
	table.pattern[14] = "100111010";
	table.pattern[15] = "000111110";
	table.pattern[16] = "011110010";
	table.pattern[17] = "010110110";
	table.pattern[18] = "010110011";
	table.pattern[19] = "010011110";
	table.pattern[20] = "010011011";
	table.pattern[21] = "110011010";
	table.pattern[22] = "011011010";
	table.pattern[23] = "111010011";
	table.pattern[24] = "111010110";
	table.pattern[25] = "111011001";
	table.pattern[26] = "111011100";
	table.pattern[27] = "101011011";
	table.pattern[28] = "101110110";
	table.pattern[29] = "101111001";
	table.pattern[30] = "101111100";


	table.numOFPatterns = 31;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[6] = table;

	table.bond = 8;
	//tee branch d = 1
	table.pattern[0] = "110111100";
	table.pattern[1] = "011111001";
	table.pattern[2] = "001111011";
	table.pattern[3] = "100111110";
	table.pattern[4] = "111110010";
	table.pattern[5] = "010110111";
	table.pattern[6] = "010011111";
	table.pattern[7] = "111011010";
	table.pattern[8] = "110110011";
	table.pattern[9] = "110111001";
	table.pattern[10] = "111110101";
	table.pattern[11] = "110110110";
	table.pattern[12] = "111111000";
	table.pattern[13] = "111010111";
	table.pattern[14] = "111011101";
	table.pattern[15] = "101011111";
	table.pattern[16] = "101110111";
	table.pattern[17] = "101111010";
	table.pattern[18] = "101111101";

	table.numOFPatterns = 19;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[7] = table;

	table.bond = 9;
	
	//vee branch d=1
	table.pattern[0] = "111111100";//a=1
	table.pattern[1] = "110110111";//a=1
	table.pattern[2] = "001111111";//a=1
	table.pattern[3] = "100011011";//a=1
	table.pattern[4] = "111111001";//c=1
	table.pattern[5] = "111110110";//c=1
	table.pattern[6] = "100111111";//c=1
	table.pattern[7] = "011011111";//c=1
	table.pattern[8] = "110111010";
	table.pattern[9] = "110111101";
	table.pattern[10] = "111110011";
	table.pattern[11] = "111011011";
	table.pattern[12] = "111011110";
	table.pattern[13] = "111111100";
	table.pattern[14] = "101111011";
	table.pattern[15] = "101111110";

	table.numOFPatterns = 16;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[8] = table;

	table.bond = 10;
	
	//vee branch d=1
	table.pattern[0] = "111111010";//b=1
	table.pattern[1] = "110111110";//b=1
	table.pattern[2] = "010111111";//b=1
	table.pattern[3] = "011111011";//b=1
	table.pattern[4] = "111111101";//a=1 & c=1
	table.pattern[5] = "111110111";//a=1 & c=1
	table.pattern[6] = "101111111";//a=1 & c=1
	table.pattern[7] = "111011111";//a=1 & c=1
	table.pattern[8] = "110111011";
	table.numOFPatterns = 9;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[9] = table;

	table.bond = 11;
	
	//vee branch d =1
	table.pattern[0] = "111111110";//a=b=1 || b=c=1
	table.pattern[1] = "110111111";//a=b=1 || b=c=1
	table.pattern[2] = "011111111";//a=b=1 || b=c=1
	table.pattern[3] = "111111011";//a=b=1 || b=c=1
	table.numOFPatterns = 4;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[10] = table;

	table.bond = 12;
	//corner cluster d = 1
	//vee branch d = 1, A =1, B=1, C=1
	table.pattern[0] = "111111111";
	table.numOFPatterns = 1;
	table.shrink = true;
	table.skeletonize = false;
	table.thin = true;

	C2TableST[11] = table;
}


void patternDB::generateUnconditionalTableSkeletonize()
{
	tblDB table;

	//M is assumed to be 1 and A, B, C and D values are varied and sorted into groups based on bond

	table.bond = 1;
	//spur
	table.pattern[0] = "000010001";
	table.pattern[1] = "000010100";
	table.pattern[2] = "001010000";
	table.pattern[3] = "100010000";
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[0] = table;

	table.bond = 2;
	//single 4- connection
	table.pattern[0] = "000010010";
	table.pattern[1] = "000011000";
	table.pattern[2] = "000110000";
	table.pattern[3] = "010010000";
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[1] = table;

	table.bond = 3;
	//vee branch d=0;
	table.pattern[8] = "101010100";//a=1 || c=1
	table.pattern[9] = "100010101";//a=1 || c=1
	table.pattern[10] = "001010101";//a=1 || c=1
	table.pattern[11] = "101010001";//a=1 || c=1
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[2] = table;

	table.bond = 4;
	//L corner
	table.pattern[0] = "010011000";
	table.pattern[1] = "010110000";
	table.pattern[2] = "000011010";
	table.pattern[3] = "000110010";
	//vee branch d=0
	table.pattern[4] = "101010101";////a=c=1
	table.pattern[5] = "101010010";////b=1
	table.pattern[6] = "100011100";////b=1
	table.pattern[7] = "010010101";////b=1
	table.pattern[8] = "001110001";//b=1
	table.numOFPatterns = 9;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[3] = table;

	table.bond = 5;
	//corner cluster d=0
	table.pattern[0] = "110110000";
	table.pattern[1] = "000011011";
	//diagona branch d=0
	table.pattern[2] = "010011100";
	table.pattern[3] = "010110001";
	table.pattern[4] = "001110010";
	table.pattern[5] = "011011010";
	//vee branch d=0
	table.pattern[6] = "101010110";//a=1, b=1
	table.pattern[7] = "100011101";//a=1, b=1
	table.pattern[8] = "011010101";//a=1, b=1
	table.pattern[9] = "101110001";//a=1, b=1
	table.pattern[10] = "101010011";//c=1, b=1
	table.pattern[11] = "101011100";//c=1, b=1
	table.pattern[12] = "110010101";//c=1, b=1
	table.pattern[13] = "001110101";//c=1, b=1
	table.numOFPatterns = 14;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[4] = table;

	table.bond = 6;
	//tee branch d=0
	table.pattern[0] = "010111000";
	table.pattern[1] = "010110010";
	table.pattern[2] = "000111010";
	table.pattern[3] = "010011010";
	
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[5] = table;

	table.bond = 7;
	//diagonal branch d =1
	table.pattern[0] = "110011101";
	table.pattern[1] = "011110101";
	table.pattern[2] = "101110011";
	table.pattern[3] = "101011110";
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[6] = table;

	table.bond = 9;
	
	//vee branch d=1
	table.pattern[0] = "111111100";//a=1
	table.pattern[1] = "110110111";//a=1
	table.pattern[2] = "001111111";//a=1
	table.pattern[3] = "100011011";//a=1
	table.pattern[4] = "111111001";//c=1
	table.pattern[5] = "111110110";//c=1
	table.pattern[6] = "100111111";//c=1
	table.pattern[7] = "011011111";//c=1
	table.numOFPatterns = 8;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[8] = table;

	table.bond = 10;
	
	//vee branch d=1
	table.pattern[0] = "111111010";//b=1
	table.pattern[1] = "110111110";//b=1
	table.pattern[2] = "010111111";//b=1
	table.pattern[3] = "011111011";//b=1
	table.pattern[4] = "111111101";//a=1 & c=1
	table.pattern[5] = "111110111";//a=1 & c=1
	table.pattern[6] = "101111111";//a=1 & c=1
	table.pattern[7] = "111011111";//a=1 & c=1
	table.numOFPatterns = 8;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[9] = table;

	table.bond = 11;
	
	//vee branch d =1
	table.pattern[0] = "111111110";//a=b=1 || b=c=1
	table.pattern[1] = "110111111";//a=b=1 || b=c=1
	table.pattern[2] = "011111111";//a=b=1 || b=c=1
	table.pattern[3] = "111111011";//a=b=1 || b=c=1
	table.numOFPatterns = 4;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[10] = table;

	table.bond = 12;
	//tee branch d = 1
	//corner cluster d = 1
	//vee branch d=1, a=b=c=1
	table.pattern[0] = "111111111";
	table.numOFPatterns = 1;
	table.shrink = false;
	table.skeletonize = true;
	table.thin = false;

	C2TableK[11] = table;
}