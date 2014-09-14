/* 
 * File:   main.cpp
 * Author: chamath
 *
 * Created on September 14, 2014, 8:13 AM
 */

#include <cstdlib>
#include<iostream>
#include<iomanip>
#include<omp.h>
#include <sys/time.h>


using namespace std;

/*
 * 
 */

double getWallTime();
double getCPUTime();

void serialProgram(int dimension);
void parallelProgram(int dimension);


int main(int argc, char** argv) {

    for(int n=1000;n<1100;n=n+100){
        cout <<"Size: "<< n<< "--: "<< endl;
        serialProgram(n);
        cout<<"\n";
    }
    


    


}


double getWallTime() {
    struct timeval time;
    if (gettimeofday(&time, NULL)) {
        //  Handle error
        return 0;
    }
    return (double) time.tv_sec + (double) time.tv_usec * .000001;
}

double getCPUTime() {
    return (double) clock() / CLOCKS_PER_SEC;
}

void serialProgram(int dimension) {
    double matrix1[dimension][dimension];
    double matrix2[dimension][dimension];
    double wall0;
    double wall1;
    double cpu0;
    double cpu1;

    double answer[dimension][dimension];

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix1[i][j] = (double) rand() / (double) (RAND_MAX);
            matrix2[i][j] = (double) rand() / (double) (RAND_MAX);
        }
    }
    //  Start timers
    wall0 = getWallTime();
    cpu0 = getCPUTime();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            answer[i][j] = 0.0;
            for (int k = 0; k < dimension; k++) {

                answer[i][j] += matrix1[i][k] * matrix2[k][j];

            }
        }

    }
    //  Stop timers for serial 
    wall1 = getWallTime();
    cpu1 = getCPUTime();
    cout << "Serial Program: "<< endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
    //end of serial program
    
    //start of parallel program
    //  Start timers
    wall0 = getWallTime();
    cpu0 = getCPUTime();
    
    #pragma omp parallel for
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            answer[i][j] = 0.0;
            for (int k = 0; k < dimension; k++) {

                answer[i][j] += matrix1[i][k] * matrix2[k][j];

            }
        }

    }
    //  Stop timers
    wall1 = getWallTime();
    cpu1 = getCPUTime();
    cout << "Parallel Program: "<< endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
}

void parallelProgram(int dimension) {
    double matrix1[dimension][dimension];
    double matrix2[dimension][dimension];

    double answer[dimension][dimension];

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix1[i][j] = (double) rand() / (double) (RAND_MAX);
            matrix2[i][j] = (double) rand() / (double) (RAND_MAX);
        }
    }

    //  Start timers
    double wall0 = getWallTime();
    double cpu0 = getCPUTime();
    
    #pragma omp parallel for
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            answer[i][j] = 0.0;
            for (int k = 0; k < dimension; k++) {

                answer[i][j] += matrix1[i][k] * matrix2[k][j];

            }
        }

    }
    //  Stop timers
    double wall1 = getWallTime();
    double cpu1 = getCPUTime();
    cout << "Parallel Program: "<< endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
}