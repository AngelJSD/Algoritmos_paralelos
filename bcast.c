#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int Bcast(int in_val, int my_rank, int p, MPI_Comm comm);

int main(int argc, char* argv[]) {
   int p, my_rank;
   MPI_Comm comm;
   int result, in_val;
   double my_start, my_finish, my_elapsed;

   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   if (my_rank == 0) {
      printf("Enter an int\n");
      scanf("%d", &in_val);
   }
   MPI_Barrier(MPI_COMM_WORLD); 
   my_start=MPI_Wtime();
   //result = Bcast(in_val, my_rank, p, comm);
   MPI_Bcast(&in_val, 1, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Barrier(MPI_COMM_WORLD); 
   my_finish=MPI_Wtime();
   my_elapsed=my_finish-my_start;
   //printf("Proc %d > result = %d, time = %f\n", my_rank, result, my_elapsed);
   printf("Proc %d > result = %d, time = %f\n", my_rank, in_val, my_elapsed);

   MPI_Finalize();
   return 0;
}  /* main */


/*-----------------------------------------------------------------*/
/* Function:    Bcast
 *           r     001 010 100 
 *           -     --- --- ---
 *           0 000 001 010 100  
 *           1 001 000 011 101
 *           2 010  x  000 110
 *           3 011  x  001 111
 *           4 100  x   x  000
 *           5 101  x   x  001
 *           6 110  x   x  010
 *           7 111  x   x  011
 */
int Bcast(int in_val, int my_rank, int p, MPI_Comm comm) {
   int        partner;
   unsigned   bitmask = 1;
   int        participate = bitmask << 1;

//#  ifdef DEBUG
   printf("Proc %d > bitmask = %d\n", my_rank, bitmask);
   fflush(stdout);
//#  endif
   while (bitmask < p) {
      if (my_rank < participate) {
         partner = my_rank ^ bitmask;
//#        ifdef DEBUG
         printf("Proc %d > bitmask = %d, partner = %d\n",
            my_rank, bitmask, partner);
         fflush(stdout);
//#        endif
         if (my_rank < partner) {
            if (partner < p )
               MPI_Send(&in_val, 1, MPI_INT, partner, 0, comm);
         } else {
            MPI_Recv(&in_val, 1, MPI_INT, partner, 0, comm, 
                  MPI_STATUS_IGNORE); 
         }
      }
      bitmask <<= 1;
      participate <<= 1;
   }
   return in_val;

}  /* Bcast */
