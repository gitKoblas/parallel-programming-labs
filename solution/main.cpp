#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

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

vector<vector<double>> matrix_miltiplier(const vector<vector<double>> &A, const vector<vector<double>> &B)
{
    int A_size = A.size();
    int B_size = B.size();
    if (A_size != B_size)
    {
        cout << "Can not multiply these matrix" << endl;
        return {};
    }
    vector<vector<double>> C(A_size, vector<double>(A_size, 0.0));
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

void verification()
{
    system("py result_check.py");
}

void make_report(int size, const string &filename)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cout << "Can not write report in this directory" << endl;
        return;
    }
    vector<vector<double>> matrix_1 = random_matrix(size);
    vector<vector<double>> matrix_2 = random_matrix(size);
    auto start = high_resolution_clock::now();
    vector<vector<double>> result_matrix = matrix_miltiplier(matrix_1, matrix_2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    file << "Matrix size: " << size << endl;
    file << "C++ Execution time: " << duration.count() << " microseconds" << endl;
    file.close();
    write_matrix(matrix_1, "matrix_1.txt");
    write_matrix(matrix_2, "matrix_2.txt");
    write_matrix(result_matrix, "result.txt");
    verification();
}

int main()
{
    make_report(5, "report.txt");
    make_report(10, "report.txt");
    make_report(15, "report.txt");
    make_report(20, "report.txt");
    make_report(25, "report.txt");
    make_report(50, "report.txt");
    make_report(100, "report.txt");
    make_report(500, "report.txt");
    make_report(1000, "report.txt");
}
