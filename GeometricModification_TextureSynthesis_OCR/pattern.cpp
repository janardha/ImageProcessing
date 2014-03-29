#include "modification.h"
patternDB::patternDB()
{
	//matrixString=NULL;
	genPattern();
}
patternDB::~patternDB()
{
	//do nothing
}
void patternDB::convert2String(char *matstr,int mat[])
{
	int index = 0;
//	char matpattern[10];

	if(mat[index] == 0)
		strcpy(matstr, "0");
	else
		strcpy(matstr, "1");
	for(index = 1; index < 4; index++)
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
void patternDB::genPattern()
{
	tblDB table;

	table.pattern[0] = "1111";
	table.numOfPattern = 1;
	bitquad[0] = table;
	
	table.pattern[0] = "0111";
	table.pattern[1] = "1011";
	table.pattern[2] = "1110";
	table.pattern[3] = "1101";
	table.numOfPattern = 4;
	bitquad[1] = table;

	table.pattern[0] = "0011";
	table.pattern[1] = "1010";
	table.pattern[2] = "1100";
	table.pattern[3] = "0101";
	table.numOfPattern = 4;
	bitquad[2] = table;

	table.pattern[0] = "0010";
	table.pattern[1] = "1000";
	table.pattern[2] = "0100";
	table.pattern[3] = "0001";
	table.numOfPattern = 4;
	bitquad[3] = table;

	table.pattern[0] = "0000";
	table.numOfPattern = 1;
	bitquad[4] = table;

	table.pattern[0] = "0110";
	table.pattern[1] = "1001";
	table.numOfPattern = 2;
	bitquad[5] = table;
}

int patternDB::checkPattern(char *str)
{
	int innerloop, index;
	bool setVar = false;
	int maxItr;

	for(index = 0; index < 6; index++)
	{
		maxItr = bitquad[index].numOfPattern;
		for(innerloop = 0; innerloop < maxItr; innerloop++)
		{
			if(strcmp(str,bitquad[index].pattern[innerloop]) == 0)
			{
				setVar = true;
				break;
			}

		}
		if(setVar)
			break;
	}
	return index;
}