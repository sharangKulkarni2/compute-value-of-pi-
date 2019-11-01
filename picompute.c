#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int size, rank, n;
    double h;
    double mypi;
    int i;
    double pi;
    double x;
    double sum;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        printf("enter num of intervals\n");
        scanf("%d", &n);
        MPI_Bcast(&n, 1, MPI_INT, 0 , MPI_COMM_WORLD);
        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("pi value = %lf\n",pi);
    }else{
        MPI_Bcast(&n, 1, MPI_INT, 0 , MPI_COMM_WORLD);
        h = 1.0 / (double) n;
        sum = 0.0;
        //printf("%d %lf\n", n, h);

        for(i = rank  ; i <= n; i = i + (size-1)){
            x = h * ((double)i - 0.5);
            sum += (4.0 / (1.0 + x*x));
        }
        mypi = h * sum;
        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
        

return 0;
}