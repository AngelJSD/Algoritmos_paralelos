#include <iostream>
#include <time.h>
#include <random>

#define MAX 590

using namespace std;

int main(void) {

    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    for(int i=0; i<MAX; ++i){
        for(int j=0; j<MAX; ++j){
            A[i][j]=rand()%10;
            B[i][j]=rand()%10;
        }
    }
    clock_t tStart = clock();
    int acum=0;
    for(int i=0; i<MAX; ++i){

        for(int j=0; j<MAX; ++j){

            for(int k=0; k<MAX; ++k){
                acum+=A[i][k]*B[k][j];
            }
            C[i][j]=acum;
            acum=0;
        }
    }
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<MAX; ++j){
            //cout<<A[i][j]<<",";
        }
        //cout<<endl;
    }
    //cout<<endl;

    for(int i=0; i<MAX; ++i){
        for(int j=0; j<MAX; ++j){
            //cout<<B[i][j]<<",";
        }
        //cout<<endl;
    }
    cout<<endl;

    for(int i=0; i<MAX; ++i){
        for(int j=0; j<MAX; ++j){
            //cout<<C[i][j]<<",";
        }
        //cout<<endl;
    }

    return 0;
}
