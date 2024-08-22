#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(){

    MPI_Init(NULL, NULL);
    
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // if(world_size != 2){
    //     fprintf(stderr, "must use two processes for this examples\n");
    //     MPI_Abort(MPI_COMM_WORLD, 1);
    // }


    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int MAX_NUMBERS = 2000;
    int number_amount;
    int numbers[MAX_NUMBERS];

    if(world_rank == 0){
        
        srand(time(NULL));
        number_amount = ((rand() / (float) RAND_MAX) * 1001 ) + 1000;


        for(int i = 0; i < number_amount; i++){
            numbers[i] = (rand() / (float) RAND_MAX) * 100;
        }

        // Send the amount of integers to process one
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("0 sent %d numbers to 1\n", number_amount);

        MPI_Recv(&somatorio, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

    } else {

        int somatorio = 0;
        MPI_Status status;

        //Receive at most MAX_NUMBERS from process zero
        MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);


        //After receiving the message, check the status to determine how many
        //numbers were actually received
        MPI_Get_count(&status, MPI_INT, &number_amount);

        for (int i = 0; i < number_amount; i++){
            somatorio += numbers[i];
        }

        MPI_Send(&somatorio, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        //Print off the amount of numbers, and also print additional information
        //in the status object
        printf("%d received %d numbers from 0. Message source = %d, tag = %d\n", world_rank, number_amount, status.MPI_SOURCE, status.MPI_TAG); 
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}