# compile: LU_pthread.cpp
 g++ -pthread LU_pthread.cpp -o LU_pthread
   #making txt file(parallel_pthread_output)
 touch pthread_output
 # run:
 #  storing output in file 
 ./LU_pthread $1 $2 > pthread_output
 
 # dispalys the file content
 cat pthread_output

