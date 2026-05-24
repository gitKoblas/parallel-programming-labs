#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;


vector<double> generate_matrice(int size) {
    vector<double> matrice(size * size);
    for (int i = 0; i < size * size; i++) {
        matrice[i] = (rand() % 10000) / 100;
    }
    return matrice;
}

__global__ void multiply(const double *a, const double *b, double *c,int n)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    double sum = 0;
    if (col < n && row < n)
    {
        for (int i = 0; i < n; i++)
        {
            sum += a[row * n + i] * b[i * n + col];
        }
        c[row * n + col] = sum;
    }
}

int main()
{
    int s;
    cout << "Input the size of block:";
    cin >> s;
    vector<int> sizes = { 200,400,800,1200,1600,2000 };
    for (int size : sizes) {
        vector<double> A(size * size), B(size * size), C(size * size);
        A = generate_matrice(size);
        B = generate_matrice(size);
        double* a, * b, * c;
        cudaMalloc(&a, size * size * sizeof(double));
        cudaMalloc(&b, size * size * sizeof(double));
        cudaMalloc(&c, size * size * sizeof(double));

        cudaMemcpy(a,A.data(), size * size * sizeof(double), cudaMemcpyHostToDevice);
        cudaMemcpy(b, B.data(), size * size * sizeof(double), cudaMemcpyHostToDevice);
        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        
        unsigned int grid_rows = (size + s - 1) / s;
        unsigned int grid_cols = (size + s - 1) / s;
        dim3 dimGrid(grid_cols, grid_rows);
        dim3 dimBlock(s, s);

        cudaEventRecord(start, 0);
        multiply << <dimGrid, dimBlock >> > (a, b, c, size);
        cudaThreadSynchronize();

        cudaEventRecord(stop, 0);
        cudaEventSynchronize(stop);
        cudaMemcpy(C.data(), c, sizeof(double) * size * size, cudaMemcpyDeviceToHost);
        float milliseconds = 0;
        cudaEventElapsedTime(&milliseconds, start, stop);
        cout << "Size:" << size << endl;
        cout << "Time(in milliseconds):" << milliseconds << endl;


        cudaFree(a);
        cudaFree(b);
        cudaFree(c);
    }
}