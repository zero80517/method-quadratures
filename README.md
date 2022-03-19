# Method of Quadratures

An example of using the method of qudratures to solve integral equation:

<p align="center">
  <img src="https://latex.codecogs.com/svg.image?{y\left(&space;x&space;\right)&space;-&space;\int\limits_0^1&space;{0.5xty}&space;\left(&space;t&space;\right)dt&space;=&space;\frac{{5x}}{6}}#gh-light-mode-only"/> 
  <img src="https://latex.codecogs.com/svg.image?{\color{white}y\left(&space;x&space;\right)&space;-&space;\int\limits_0^1&space;{0.5xty}&space;\left(&space;t&space;\right)dt&space;=&space;\frac{{5x}}{6}}#gh-dark-mode-only"/> 
  </br>
  <img src="https://latex.codecogs.com/svg.image?{y\left(&space;x&space;\right)&space;=&space;x&space;}#gh-light-mode-only"/> 
  <img src="https://latex.codecogs.com/svg.image?{\color{white}y\left(&space;x&space;\right)&space;=&space;x&space;}#gh-dark-mode-only"/>
</p>

The Jacobi method is used to solve the corresponding SLAE. 
That method is parallelized using different approaches: OpenMP, MPI and hybrid OpenMP/MPI.
The accelerations are also shown in the results.
