#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<time.h>
#include <chrono>
#include <vector>
using namespace std ;

void print(double** matrix, int n){
	for(int i = 0; i < n; i++){
	   for(int j = 0; j < n; j++){
		   cout << matrix[i][j] << "  ";
	   }
	   cout<< endl;
   }
   cout<<endl;	
}

void mul(double** m1,double** m2,double** res,int n){
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			res[i][j]=0;
			for(int k=0;k<n;++k){
				res[i][j]+= m1[i][k]*m2[k][j];
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int n = stoi(argv[1]);
	
	double **a, **a_copy, **u, **l, **p_matrix, **PA, **LU;
	a = new double* [n];
	a_copy = new double* [n];
	u = new double* [n];
	l = new double* [n];
	p_matrix = new double* [n];
	PA = new double* [n];
	LU = new double* [n];
	
	auto start = std::chrono::high_resolution_clock::now();	
	
	for(int i=0; i < n; i++){
		a[i] = new double[n];
		u[i] = new double[n];
		l[i] = new double[n];
		a_copy[i] = new double[n];
		p_matrix[i] = new double[n];
		PA[i] = new double[n];
		LU[i] = new double[n];
	}
   
	vector<int> p(n,0);
	double drand48();

	srand48(time(NULL));

	for(int i =0; i < n; i++){
		p[i] = i;		
		for(int j = 0; j < n; j++){
			if( j < i ){
				u[i][j] = 0.0;
				l[i][j] = drand48();
			}
			else if(j == i){
				l[i][j] = 1.0;
				u[i][j] = drand48();
			}
			else{
				u[i][j] = drand48();
				l[i][j] = 0.0;
			}
			p_matrix[i][j]=0.0;
			a[i][j] = drand48();
			a_copy[i][j] = a[i][j];		   
		}  
	}
	
	double maxi;	// finds max in given col(k)
	int kdash;	
	
	// all cols
	for(int k = 0; k < n; k++){
		maxi = 0.0;
		auto startfor = std::chrono::high_resolution_clock::now();	
	
		// start finding max from diagonal elt(bcoz previous row already processed by col before it)
		// loop for all rows of given col k(to find max)
		for(int i = k; i < n; i++){
			if(fabs(a[i][k])> maxi){
				maxi = fabs(a[i][k]);
				//index of max element
				kdash = i;
			}
		}
		
		//Singular Matrix(all elts in that row = 0.0)
		if(maxi==0.0){
			cerr<<"Singular matrix."<<endl;
			exit(0);
		}
		
		//swapping p[k] & p[k'] 
		int temp_p = p[k];
		p[k] = p[kdash];
		p[kdash] = temp_p;
		
		//swapping rows A[k] & A[k']
		double* temp_a = a[k];
		a[k] = a[kdash];
		a[kdash] = temp_a;

		//swapping rows l[k] & l[k']
		// tmpdbl
		double temp_l=0.0;
		for(int i = 0; i < k; i++){
			temp_l = l[k][i];
			l[k][i] = l[kdash][i];
			l[kdash][i] = temp_l;
		}
		
		u[k][k] = a[k][k];
		
		//assigning l[][],u[][] updated values
		for(int i = k+1; i < n; i++){
		   l[i][k] = a[i][k]*1.0/u[k][k];
		   u[k][i] = a[k][i];
		}
		
		double temp_u[n-k-1] ;
		for(int i=0;i<n-k-1;i++){
			temp_u[i]=u[k][i+k+1];
		}

		double *temps;
		double val ;
		int j=0;
	
		//upating A[][]
		for(int i = k+1; i < n; i++){
			val=l[i][k] ;
			//pointer to ith row of A matrix
			temps=a[i] ;
			for(j = k+1; j<n; j++){
				// a(i,j) = a(i,j) - l(i,k)*u(k,j)
				temps[j] -= val*temp_u[j-k-1];	
			}
		}
	}
	
	auto end = std::chrono::high_resolution_clock::now();

	// // avoiding printing(easier to compare)
	// cout<<"Original matrix\n";
 //    print(a_copy,n);
 //    cout<<"L matrix\n";
 //    print(l,n);
 //    cout<<"U matrix\n";
 //    print(u,n);
 //    cout<<"P array\n";
 //    for(int i=0;i<n;++i){
 //        cout<<p[i]<<" ";
 //    }
 //    cout<<"\n\n";

	// for(int i=0;i<n;++i){
	// 	p_matrix[i][p[i]] = 1.0;
	// }

	// mul(p_matrix,a_copy,PA,n);
	// mul(l,u,LU,n);

	// printf("PA:-\n");
	// print(PA,n);

	// printf("LU:-\n");
	// print(LU,n);

	double time_spent = chrono::duration_cast<chrono::microseconds>(end-start).count()/1000000.0;
    cout<<"Serial Time: "<< fixed << time_spent<<endl;
    
	FILE * outputFile, * sizeFile, *threadFile; 
    
    // comparison:- Size v/s Time
    // writing exec time 
    outputFile = fopen ("time.txt","a");
    fprintf (outputFile,"%lf",time_spent);
    fprintf(outputFile,"\n");
    
    //writing size
    sizeFile = fopen ("size.txt","a");
    fprintf (sizeFile,"%d",n);
    fprintf(sizeFile,"\n");
	
	//Free the allocated matrices
	for(int i=0; i < n; i++){
		delete a[i];
		delete u[i];
		delete l[i];
		delete a_copy[i];
		delete p_matrix[i];
		delete PA[i];
		delete LU[i];
	}
	delete a,u,l,a_copy,p_matrix,PA,LU;
	
	return 0;
}