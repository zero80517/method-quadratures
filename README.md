# Method of Quadratures

An example of using the method of qudratures to solve integral equation:

<p align="center">
  <img src="https://latex.codecogs.com/png.image?\dpi{300}\bg{white}y\left(&space;x&space;\right)&space;-&space;\int\limits_0^1&space;{0.5xty}&space;\left(&space;t&space;\right)dt&space;=&space;\frac{{5x}}{6}"/>
  </br>
  <img src="https://latex.codecogs.com/png.image?\dpi{300}\bg{white}y\left(&space;x&space;\right)&space;=&space;x&space;"/> 
</p>

The Jacobi method is used to solve the corresponding SLAE. 
That method is parallelized using different approaches: OpenMP, MPI and hybrid OpenMP/MPI.
The accelerations are also shown in the results:

![image](https://user-images.githubusercontent.com/66224979/159153887-6f105f2a-3bd3-4c08-a027-a03bfc3cfa2c.png)

