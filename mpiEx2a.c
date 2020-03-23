#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int rank, size;
  int    namelen;
  char   processor_name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(NULL,NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name,&namelen);

  if (rank == 0){
	 printf("Yo soy el maestro y existen %d procesos\n",size);
  }else{
	 printf("Yo soy un proceso con identificador %d de %d procesos en ejecucion %s\n",rank,size, processor_name);
  };
  MPI_Finalize();
}
