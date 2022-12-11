#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void cal_row()
{

	float array[64][64];
	int i = 0, j = 0;

	for (i = 0; i < 64; i++)
	{
		for (j = 0; j < 64; j++)
		{
			array[i][j] = (float) sqrt(i * j);
			printf("%f\t",array[i][j]);
		}
		printf("\n");
	}
}

void cal_col()
{

	float array[64][64];
	int i = 0, j = 0;
	
	for (i = 0; i < 64; i++)
	{
		for (j = 0; j < 64; j++)
		{
			array[j][i] = (float) sqrt(j * i);
			printf("%f\t",array[j][i]);
		}
		printf("\n");
	}
}


int main(void)
{
	//cal_row();
	cal_col();
	return EXIT_SUCCESS;
}