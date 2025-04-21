#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    char message[100];

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Process 0 sends a message to all other processes
        for (int i = 1; i < size; i++) {
            sprintf(message, "Hello from process 0 to process %d", i);
            MPI_Send(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Other processes receive the message from process 0
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received message: %s\n", rank, message);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
