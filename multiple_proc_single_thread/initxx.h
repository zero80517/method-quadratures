#pragma once

void InitX(double *pX, double a, double b, int num_points) {
  double h = (b - a) / (num_points - 1);
  for (int i = 0; i < num_points; i++) pX[i] = a + h * i;
}

void InitF(double *pX, double *pF, int num_points) {
  for (int i = 0; i < num_points; i++) pF[i] = 5. * pX[i] / 6.;
}

void InitC(double *pC, double a, double b, int num_points) {
  double h = (b - a) / (num_points - 1); 
  // Trapezoidal rule
  for (int i = 0; i < num_points; i++)
    pC[i] = (i == 0 || i == num_points - 1) ? h / 2 : h; 
}

void InitY(double *pY, int num_points) {
  for (int i = 0; i < num_points; i++) pY[i] = 0.;
}

double Kernel(double x_i, double x_j) { return 0.5 * x_i * x_j; }

void InitA(double *pX, double *pC, double *pLocalA, int global_idx,
           int num_points) {
  for (int j = 0; j <= global_idx - 1; j++)
    pLocalA[j] = -pC[j] * Kernel(pX[global_idx], pX[j]);
  pLocalA[global_idx] =
      1. - pC[global_idx] * Kernel(pX[global_idx], pX[global_idx]);
  for (int j = global_idx + 1; j < num_points; j++)
    pLocalA[j] = -pC[j] * Kernel(pX[global_idx], pX[j]);
}
