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

void serialProgram();
void serialProgramWithOptimizations();
void parallelProgram();
void parallelProgramWithOptimizations();

double **matrix1;
double **matrix2;//transpose of matrix3
double **matrix3;

int dimension;

int main(int argc, char** argv) {

    for (int n = 100; n < 1100; n = n + 100) {
        dimension = n;
        cout << "Size: " << n << "--: " << endl;
        
        matrix1 = new double *[dimension];
        matrix2 = new double *[dimension];
        matrix3 = new double *[dimension];
        for (int i = 0; i < dimension; i++) {
            matrix1[i] = new double[dimension];
            matrix2[i] = new double[dimension];
            matrix3[i]=new double[dimension];
        }
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                matrix1[i][j] = (double) rand() / (double) (RAND_MAX);
                matrix3[i][j] = (double) rand() / (double) (RAND_MAX);
            }
        }
        //transpose the second matrix
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                matrix2[j][i]=matrix3[i][j];
                
            }
        }
        serialProgram();
        serialProgramWithOptimizations();
        parallelProgram();
        parallelProgramWithOptimizations();
        cout << "\n";
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

void serialProgram() {

    double answer[dimension][dimension];

    //  Start timers
    double wall0 = getWallTime();
    double cpu0 = getCPUTime();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            answer[i][j]= 0.0;
            for (int k = 0; k < dimension; k++) {

                answer[i][j] += matrix1[i][k] * matrix3[k][j];

            }
            
        }

    }
    //  Stop timers for serial 
    double wall1 = getWallTime();
    double cpu1 = getCPUTime();
    cout << "Serial Program: " << endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
    //end of serial program

}


void serialProgramWithOptimizations() {

    double answer[dimension][dimension];

    //  Start timers
    double wall0 = getWallTime();
    double cpu0 = getCPUTime();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            double temp = 0.0;
            for (int k = 0; k < dimension; k++) {

                temp += matrix1[i][k] * matrix2[j][k];

            }
            answer[i][j]=temp;
        }

    }
    //  Stop timers for serial 
    double wall1 = getWallTime();
    double cpu1 = getCPUTime();
    cout << "Serial Program With Optimizations: " << endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
    //end of serial program

}


void parallelProgram() {


    double answer[dimension][dimension];

    //  Start timers
    double wall0 = getWallTime();
    double cpu0 = getCPUTime();

#pragma omp parallel for 
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            answer[i][j] = 0.0; //to reduce memory updates
            for (int k = 0; k < dimension; k++) {

                answer[i][j] += matrix1[i][k] * matrix3[k][j];

            }
            
        }

    }
    //  Stop timers
    double wall1 = getWallTime();
    double cpu1 = getCPUTime();
    cout << "Parallel Program: " << endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
}


void parallelProgramWithOptimizations() {


    double answer[dimension][dimension];

    //  Start timers
    double wall0 = getWallTime();
    double cpu0 = getCPUTime();

#pragma omp parallel for 
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            double temp = 0.0; //to reduce memory updates
            for (int k = 0; k < dimension; k++) {

                temp += matrix1[i][k] * matrix2[j][k];

            }
            answer[i][j]=temp;
        }

    }
    //  Stop timers
    double wall1 = getWallTime();
    double cpu1 = getCPUTime();
    cout << "Parallel Program With Optimizations: " << endl;
    cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1 - cpu0 << endl;
}