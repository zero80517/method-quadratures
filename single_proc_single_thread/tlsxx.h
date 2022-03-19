#pragma once

#include "defxx.h"

#include <stdio.h>
#include <time.h>

#include <string>

// See https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
// and https://en.cppreference.com/w/c/chrono/strftime
std::string CurrentDateTime() {
  // current date/time based on current system
  time_t now = time(0);
  char buf[256] = {0};
  strftime(buf, sizeof(buf), "%d%m%Y_%H%M%S", localtime(&now));

  return std::string(buf);
}

void SaveEval2File(double* pX, double* pY, int num_points, int num_iters) {
  FILE* pFile;
  
  std::string filename = std::string("ss_") + std::to_string(num_points) +
                         std::string("_") + std::to_string(num_iters) +
                         std::string(".txt");

  pFile = fopen(filename.c_str(), "w");

  for (int i = 0; i < num_points; i++)
    fprintf(pFile, "%1.15e %1.15e\n", pX[i], pY[i]);

  fclose(pFile);
}

void SaveTime2File(int num_points, int num_iters, double wtime) {
  FILE* pFile;

  std::string filename = std::string("ss_") + std::to_string(num_points) +
                         std::string("_") + std::to_string(num_iters) +
                         std::string("_wtime") + std::string(".txt");

  pFile = fopen(filename.c_str(), "a");

  fprintf(pFile, "%f\n", wtime);

  fclose(pFile);
}
