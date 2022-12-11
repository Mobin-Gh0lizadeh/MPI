#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>


float matrix[64][64];

void createMatrix()
{
    int i = 0, j = 0;

    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 64; j++)
        {
            matrix[i][j] = i * j;

        }

    }
}

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_rank == 0)
    {
        createMatrix();
    }

    int row = 0;
    int col = 0;
    int send_count = (int) (64 / (world_size - 1)); 
    int receive_count = send_count;

    for (row = 0; row < 64; row++)
    {
        float matrix_recieve[64];

        MPI_Scatter(matrix[row], send_count, MPI_FLOAT, matrix_recieve, receive_count, MPI_FLOAT, 0, MPI_COMM_WORLD);


        if (world_rank != 0)
        {
            for(col=0; col < send_count; col++)
            {
               matrix_recieve[col] = (float)sqrtf(matrix_recieve[col]);               
            }

        }

        MPI_Gather(matrix_recieve, send_count, MPI_FLOAT,matrix[row], receive_count, MPI_FLOAT,0, MPI_COMM_WORLD);
    }

    if (world_rank == 0)
    {
        int final_row = 0;
        int final_col = 0;
        for (final_row = 0; final_row < 64; final_row++)
        {
            for (final_col = 0; final_col < 64; final_col++)
            {
                printf("%f\t", matrix[final_row][final_col]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();

    return 0;
}
