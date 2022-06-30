# compile: LU_seq.cpp
 g++ sequential/LU_seq.cpp -o LU_seq
   #making txt file(sequential_output)
 touch sequential/sequential_output
 # run:
 #  storing output in file 
 ./LU_seq $1 > sequential/sequential_output
 
 # compile: LU_omp.cpp
 g++ -fopenmp omp_parallel/LU_omp.cpp -o LU_omp
 # making txt file(omp_output) 
 touch omp_parallel/omp_output
 # run:
 #storing output in file
 ./LU_omp $1 $2 > omp_parallel/omp_output
 
 # compile: Lu_pthread.cpp
 g++ -pthread pthread_parallel/LU_pthread.cpp -o LU_pthread
   #making txt file(pthread_output)
 touch pthread_parallel/pthread_output
 # run:
 #  storing output in file 
 ./LU_pthread $1 $2 > pthread_parallel/pthread_output
 
#  # dispalys the file content
cat sequential/sequential_output
cat omp_parallel/omp_output
cat pthread_parallel/pthread_output