# Method of Quadratures

An example of using the method of qudratures to solve integral equation:

$$y\left( x \right) - \int\limits_0^1 {0.5xty} \left( t \right)dt = \frac{{5x}}{6}$$

$$y\left( x \right) = x$$

The Jacobi method is used to solve the corresponding SLAE. 
That method is parallelized using different approaches: OpenMP, MPI and hybrid OpenMP/MPI.
The accelerations are also shown in the results.
