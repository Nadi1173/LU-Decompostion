# compile: LU_omp.cpp
 g++ -fopenmp LU_omp.cpp -o LU_omp
 # making txt file(parallel_omp_output) 
 touch omp_output
 # run:
 #storing output in file
 ./LU_omp $1 $2 > omp_output
  # dispalys the file content
 cat omp_output
