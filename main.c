#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

/**
 * mpicc <arquivo>.c -o <nome_compilavel>
 * mpirun -np 4 <nome_compilavel>
 * mpirun -np 4 --hostfile hostfile <nome_compilavel>
 * 
 * comando: export HWLOC_HIDE_ERRORS=2
 */

int main(int argc, char** argv){

    //Initialize the MPI environment. The two arguments to MPI Init are not
    //currently used by MPI implementations, but are there in case future
    //implementations might ned the arguments.
    MPI_Init(NULL, NULL);

    //Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    //Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if(world_rank == 0){
        sleep(2);
    }


    // Print off a hello message
    printf("Hello world from processor %s, rand %d, out of %d processors\n", processor_name, world_rank, world_size);


    //While every process isn't in this step, all of them will wait till every process is here (blocked by a "barrier")
    MPI_Barrier(MPI_COMM_WORLD);

    printf("Finalizing process %d out of %d processors\n", world_rank, world_size);

    //Finalize the MPI environment. No more MPI calls can be made after this.
    MPI_Finalize();


}