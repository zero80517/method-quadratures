#include "defxx.h"
#include "initxx.h"
#include "tlsxx.h"

#include <math.h>
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);  // Initialize MPI envrnmt

  double tic = MPI_Wtime();

  if (argc == 3) {
    // Determine root's rank
    int root_rank = 0;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // ID of current process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Number of processes

    // number of processes must be equals to the number of physical cores
    if (size != NUM_PHYSICAL_CORES) {
      printf(
          "This application is meant to be run with "
          "number of processes to be equals to number of physical cores.\n");
      MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // init IE params
    double a = 0., b = 1.;
    int num_points = std::stoi(argv[1]);
    int num_iters = std::stoi(argv[2]);

    // vector dimension must be multiple of the number of processes
    if (num_points % size != 0) {
      printf(
          "This application is meant to be run with "
          "vector dimension is multiple of the number of processes.\n");
      MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // allocate memory for full data
    double* pX = (double*)malloc(sizeof(double) * num_points);
    double* pF = (double*)malloc(sizeof(double) * num_points);
    double* pC = (double*)malloc(sizeof(double) * num_points);
    double* pLocalA = (double*)malloc(sizeof(double) * num_points);
    double* pY = (double*)malloc(sizeof(double) * num_points);
    int size_pLocalY = num_points / size;
    double* pLocalY = (double*)malloc(sizeof(double) * size_pLocalY);

    // initialize vectors
    InitX(pX, a, b, num_points);
    InitF(pX, pF, num_points);
    InitC(pC, a, b, num_points);
    InitY(pY, num_points);
    InitY(pLocalY, size_pLocalY);

    for (int t = 0; t < num_iters; t++) {
      // broadcast a vector from the root to all other processes in the same
      // communicator
      MPI_Bcast(pY, num_points, MPI_DOUBLE, root_rank, MPI_COMM_WORLD);

      // do method Jacobi in the different processes
      double sum = 0.;
      for (int local_idx = 0; local_idx < size_pLocalY; local_idx++) {
        
        int global_idx = rank * size_pLocalY + local_idx;
        InitA(pX, pC, pLocalA, global_idx, num_points);
        sum = 0.;
        for (int j = 0; j <= global_idx - 1; j++) sum += pLocalA[j] * pY[j];
        for (int j = global_idx + 1; j < num_points; j++)
          sum += pLocalA[j] * pY[j];
        pLocalY[local_idx] = (pF[global_idx] - sum) / pLocalA[global_idx];
        
      }

      // gather a vector in root
      MPI_Gather(pLocalY, size_pLocalY, MPI_DOUBLE, pY, size_pLocalY,
                 MPI_DOUBLE, root_rank, MPI_COMM_WORLD);
    }

    // save answer
    double toc = MPI_Wtime();
    double wtime = toc - tic;

    if (rank == root_rank) {
      SaveEval2File(pX, pY, num_points, num_iters);
      SaveTime2File(num_points, num_iters, wtime);
    }

    delete[] pX;
    delete[] pF;
    delete[] pC;
    delete[] pLocalA;
    delete[] pY;
    delete[] pLocalY;

    MPI_Finalize();  // Terminate MPI environment

    return EXIT_SUCCESS;
  }

  MPI_Finalize();  // Terminate MPI environment

  return EXIT_FAILURE;
}
