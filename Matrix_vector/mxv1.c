#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


int main(int argc, char* argv[]) {

	int m, n, n_local, i,j,local_m,local_n;
	double local_start, local_finish, local_elapsed, elapsed;
	MPI_Comm comm;
	
	m=atoi(argv[1]);
	n=atoi(argv[1]);
	srand(time(NULL));
	
	int v[n], result[n];
	int *A = (int *)malloc(sizeof(int) * m*n);
	int rank;
	int size;
	printf("Vivo\n");
        MPI_Init(&argc, &argv);
	comm = MPI_COMM_WORLD;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	local_m=m/size;
	local_n=n/size;

	if(rank==0){	

		for(i=0;i<m*n;++i)
			A[i]=(rand() %100000);

		for(i=0; i<n; ++i){
			v[i]=(rand() %100000);
			//printf("%d, ",v[i]);
		}
	}
	MPI_Barrier(comm);
	local_start=MPI_Wtime();
	int *local_A = (int *)malloc(sizeof(int) * local_m*n);
	int *local_x = (int *)malloc(sizeof(int) * local_n);
	int *local_y = (int *)malloc(sizeof(int) * local_m);
	int *res = (int *)malloc(sizeof(int) * m);
	MPI_Scatter(A, local_m*n, MPI_INT, local_A,
              local_m*n, MPI_INT, 0, comm);
	MPI_Scatter(v, local_n, MPI_INT, local_x,
              local_n, MPI_INT, 0, comm);
	//MPI_Scatter(result, local_m, MPI_INT, local_y,
              //local_m, MPI_INT, 0, comm);
	
	//for(i=0; i<local_m*n; ++i)
		//printf("Proceso %d, tengo %d\n", rank,local_A[i]);
	//for(i=0; i<local_n; ++i)
		//printf("Proceso %d, tengv %d\n", rank,local_x[i]);
	int *x=(int*)malloc(n*sizeof(int));
	MPI_Allgather(local_x, local_n, MPI_INT, x, local_n, MPI_INT, comm);
	//for(i=0; i<n; ++i)
		//printf("Proceso %d, tengx %d\n", rank,x[i]);
	
	for(i=0; i<local_m; ++i){
		
		local_y[i]=0;
		for(j=0; j<n; ++j){
			local_y[i]+=local_A[i*n+j]*x[j];
			//printf("Proceso %d, opero %d x %d\n", rank,local_A[i*n+j],x[j]);
		}
	}
	free(x);

	MPI_Gather(local_y, local_m, MPI_INT, res, local_m, MPI_INT, 0,
           MPI_COMM_WORLD);
	local_finish=MPI_Wtime();
	local_elapsed=local_finish-local_start;
	MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	if(rank==0){	
		
		for(i=0; i<m; ++i){
			//printf("%d, ",res[i]);
		}
		printf("Elapsed time = %f seconds\n", elapsed);
	}

	MPI_Finalize();	

	return 0;
}
