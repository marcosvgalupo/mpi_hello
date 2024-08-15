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

    const int PING_PONG_LIMIT = 100;


    //Initialize the MPI environment. The two arguments to MPI Init are not
    //currently used by MPI implementations, but are there in case future
    //implementations might ned the arguments.
    MPI_Init(NULL, NULL);

    //Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_size != 2){
        fprintf(stderr, "World size must be two for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    //Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    int ping_pong_count = 0;
    int partner_rank = (world_rank + 1) % 2;
    while(ping_pong_count < PING_PONG_LIMIT){
        if(world_rank == ping_pong_count % 2){
            //Increment the ping pong count before you send it
            ping_pong_count++;
            MPI_Ssend(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("%d sent and incremented ping_pong_count %d to %d\n", world_rank, ping_pong_count, partner_rank);
        }
        else{
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d received ping_pong_count %d from %d\n", world_rank, ping_pong_count, partner_rank);
        }
    }

    //Finalize the MPI environment. No more MPI calls can be made after this.
    MPI_Finalize();


}