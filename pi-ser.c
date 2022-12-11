#include <stdio.h>
#include <stdlib.h> 

#define sqr(x)	((x)*(x))
#define DARTS 100000
#define ROUNDS 100


double pi_cal(int darts)
{
	double x_coord,y_coord,pi,r;              
	int score,n;
	score = 0;

	for (n = 1; n <= darts; n++)
	{
		r = (double)rand() / (double)RAND_MAX;
		x_coord = (2.0 * r) - 1.0;
		
		r = (double)rand() / (double)RAND_MAX;
		y_coord = (2.0 * r) - 1.0;

		if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
			score++;
	}
	pi = 4.0 * (double)score / (double)darts;
	return(pi);
}



int main()
{
	double pi = 0;          	
	double pi_avg = 0;       	
	srandom (5);              
	
	for (int i = 0; i < ROUNDS; i++)
	{
	   pi = pi_cal(DARTS);
	   pi_avg = ((pi_avg * i) + pi) / (i + 1);
	}
	printf(" Final PI = %10.8f\n", pi_avg);
	printf("\nReal value of PI: 3.1415926535897 \n");
	return 0;
}