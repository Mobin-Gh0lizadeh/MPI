#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 

#define sqr(x)	((x)*(x))
#define DARTS 100000   
#define ROUNDS 100      
#define MASTER 0  

double cal_pi(int darts)
{
	double x_coord,y_coord,pi,r; 		
	int score,n;
	score = 0;

	for (n = 1; n <= darts; n++)
	{
		r = (double) rand() / (double) RAND_MAX;
		x_coord = (2.0 * r) - 1.0;
		r = (double) rand() / (double) RAND_MAX;
		y_coord = (2.0 * r) - 1.0;
		if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
			score++;
	}
	
	pi = 4.0 * (double) score / (double) darts;
	return (pi);
}
   

int main(int argc, char *argv[])
{

	double home_pi, pi,avepi, pirecv, pisum;
	int taskid, numtasks, source, mtype, rc, i, n;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	
	printf("MPI task %d has started \n", taskid);

	srandom(taskid);
	avepi = 0;
	for (i = 0; i < ROUNDS; i++)
	{
		home_pi = cal_pi(DARTS);
		if (taskid != MASTER)
		{
			mtype = i;
			rc = MPI_Send(&home_pi, 1, MPI_DOUBLE, MASTER, mtype,MPI_COMM_WORLD);
			if (rc != MPI_SUCCESS)
			{
				printf("%d: Send failure on round %d\n", taskid, mtype);
			}
		}
		else
		{
			mtype = i;
			pisum = 0;
			for (n = 1; n < numtasks; n++)
			{
				rc = MPI_Recv(&pirecv, 1, MPI_DOUBLE, MPI_ANY_SOURCE, mtype,MPI_COMM_WORLD, &status);
				pisum = pisum + pirecv;
			}

			pi = (pisum + home_pi) / numtasks;
			avepi = ((avepi * i) + pi) / (i + 1);
			printf("After %4d rounds, average value of PI is: %10.8f\n", ((i + 1)), avepi);
		}
	}

	if (taskid == MASTER)
		printf("Real value of PI: 3.1415926535897 \n");
	MPI_Finalize();
	return 0;

}