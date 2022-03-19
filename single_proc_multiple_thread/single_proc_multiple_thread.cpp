#include "defxx.h"
#include "initxx.h"
#include "tlsxx.h"

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>

int main(int argc, char* argv[]) {
  if (argc == 3) {
    double tic = omp_get_wtime();

    int num_thread = omp_get_max_threads();

    // init IE params
    double a = 0., b = 1.;
    int num_points = std::stoi(argv[1]);
    int num_iters = std::stoi(argv[2]);

    // allocate memory for full data
    double* pX = (double*)malloc(sizeof(double) * num_points);
    double* pF = (double*)malloc(sizeof(double) * num_points);
    double* pC = (double*)malloc(sizeof(double) * num_points);
    double* pLocalA = (double*)malloc(sizeof(double) * num_thread * num_points);
    double* pY = (double*)malloc(sizeof(double) * num_points);
    int size_pLocalY = num_points;
    double* pLocalY = (double*)malloc(sizeof(double) * size_pLocalY);

    // initialize vectors
    InitX(pX, a, b, num_points);
    InitF(pX, pF, num_points);
    InitC(pC, a, b, num_points);
    InitY(pY, num_points);
    InitY(pLocalY, size_pLocalY);

    for (int t = 0; t < num_iters; t++) {
      // do method Jacobi
      double sum = 0.;
#pragma omp parallel for private(sum)
      for (int local_idx = 0; local_idx < size_pLocalY; local_idx++) {
        int thread_id = omp_get_thread_num();
        int global_idx = local_idx;
        InitA(pX, pC, &pLocalA[thread_id * num_points], global_idx, num_points);
        sum = 0.;
        for (int j = 0; j <= global_idx - 1; j++)
          sum += pLocalA[thread_id * num_points + j] * pY[j];
        for (int j = global_idx + 1; j < num_points; j++)
          sum += pLocalA[thread_id * num_points + j] * pY[j];
        pLocalY[local_idx] = (pF[global_idx] - sum) /
                             pLocalA[thread_id * num_points + global_idx];
      }

#pragma omp parallel for
      for (int i = 0; i < num_points; i++) pY[i] = pLocalY[i];
    }

    // save answer
    double toc = omp_get_wtime();
    double wtime = toc - tic;

    SaveEval2File(pX, pY, num_points, num_iters);
    SaveTime2File(num_points, num_iters, wtime);

    delete[] pX;
    delete[] pF;
    delete[] pC;
    delete[] pLocalA;
    delete[] pY;
    delete[] pLocalY;

    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}