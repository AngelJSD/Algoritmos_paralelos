#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main(){
	
	int n,t;
	cin>>n;
	t=250;
	int A[n][n],B[n][n],C[n][n];
	srand(time(NULL));

	for(int i=0; i<n; ++i){
		
		for(int j=0; j<n; ++j){
			
			A[i][j]=rand()%10;
			B[i][j]=rand()%10;
			C[i][j]=0;
		}
	}
	clock_t tStart = clock();
	for(int i=0; i<n; i+=t){
		
		for(int j=0; j<n; j+=t){
			
			for(int k=0; k<n; k+=t){
				
				for(int a=i; a<min(i+t,n); ++a){

					for(int b=j; b<min(j+t,n); ++b){
						
						for(int c=k; c<min(k+t,n); ++c){
							
							C[a][b]=C[a][b]+A[a][c]*B[c][b];
						}
					}
				}
			}
		}

	}
	printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	for(int i=0; i<n; ++i){
		
		for(int j=0; j<n; ++j){
			
			//cout<<A[i][j]<<",";
		}
		//cout<<endl;
	}

	//cout<<endl;

	for(int i=0; i<n; ++i){
		
		for(int j=0; j<n; ++j){
			
			//cout<<B[i][j]<<",";
		}
		//cout<<endl;
	}

	//cout<<endl;

	for(int i=0; i<n; ++i){
		
		for(int j=0; j<n; ++j){
			
			//cout<<C[i][j]<<",";
		}
		//cout<<endl;
	}

	return 0;

}
