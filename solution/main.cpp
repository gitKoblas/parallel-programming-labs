#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <omp.h>
#include <windows.h>

using namespace std;
using namespace std::chrono;

vector<vector<double>> get_matrix(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Can not open these file" << endl;
        return {};
    }
    int size;
    in >> size;
    vector<vector<double>> matrix(size, vector<double>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            in >> matrix[i][j];
        }
    }
    in.close();
    return matrix;
}

vector<vector<double>> matrix_miltiplier(const vector<vector<double>> &A, const vector<vector<double>> &B, int threads)
{
    int A_size = A.size();
    int B_size = B.size();
    if (A_size != B_size)
    {
        cout << "Can not multiply these matrix" << endl;
        return {};
    }
    vector<vector<double>> C(A_size, vector<double>(A_size, 0.0));
    omp_set_num_threads(threads);
#pragma omp parallel for collapse(2)
    for (int i = 0; i < A_size; ++i)
    {
        for (int k = 0; k < A_size; ++k)
        {
            for (int j = 0; j < A_size; ++j)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

void set_Cores(int cores)
{
    DWORD_PTR mask = 0;

    for (int i = 0; i < cores; i++)
    {
        mask |= (1ULL << i);
    }
    SetProcessAffinityMask(GetCurrentProcess(), mask);
}

vector<vector<double>> random_matrix(int size)
{
    vector<vector<double>> matrix(size, vector<double>(size, 0.0));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distrib(-100, 100);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = distrib(gen);
        }
    }
    return matrix;
}

void write_matrix(const vector<vector<double>> &matrix, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Can not save in this directory" << endl;
        return;
    }
    int size = matrix.size();
    file << size << endl;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            file << setprecision(15) << matrix[i][j];
            if (j < size - 1)
            {
                file << " ";
            }
        }
        file << endl;
    }
}

void make_report(const string &filename)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cout << "Can not write report in this directory" << endl;
        return;
    }
    vector<int> sizes = {200, 400, 800, 1200, 1600, 2000};
    vector<int> threads_counts = {1, 2, 4, 8, 12}; 
    vector<int> cores_counts = {1, 2, 4, 6};
    file << left << setw(10) << "Cores" << setw(12) << "Threads" << setw(15) << "Matrix Size" << "Time (microseconds)" << endl;
    for (int cores : cores_counts)
    {
        set_Cores(cores);
        for (int threads : threads_counts)
        {
            for (int size : sizes)
            {
                vector<vector<double>> matrix_1 = random_matrix(size);
                vector<vector<double>> matrix_2 = random_matrix(size);
                auto start = high_resolution_clock::now();
                vector<vector<double>> result_matrix = matrix_miltiplier(matrix_1, matrix_2, threads);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                file << left << setw(10) << cores << setw(12) << threads << setw(15) << size << duration.count() << endl;
            }
            file << "----------------------------------------------------------------" << endl;
        } 
    }
    file.close();
}

int main()
{
    make_report("report.txt");
}
