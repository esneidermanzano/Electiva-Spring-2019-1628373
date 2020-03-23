#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
        int size, rank, dest, source, count, namelen, tag=1;
        int inmsg, outmsg=0;
        MPI_Status Stat;

        char   mc_name[MPI_MAX_PROCESSOR_NAME];

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Get_processor_name(mc_name,&namelen);

        dest = rank+1;
        source = rank-1;
        if (rank == 0) {
		  source = size-1;
		  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	   }else{
	   if(rank== size-1){
	     dest = 0;
	   };
	   MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	   outmsg = inmsg +1;
	   MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	};

        MPI_Get_count(&Stat, MPI_INT, &count);
        printf("Task %d on machine %s: Send %d, and Received %d from task %d  \n",
                   rank, mc_name,outmsg, inmsg, Stat.MPI_SOURCE);

        MPI_Finalize();
}
