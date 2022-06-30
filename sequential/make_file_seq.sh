# compile: LU_seq.cpp
 g++ LU_seq.cpp -o LU_seq
   #making txt file(sequential_output)
 touch sequential_output
 # run:
 #  storing output in file 

 ./LU_seq $1 > sequential_output
  # dispalys the file content
 cat sequential_output
