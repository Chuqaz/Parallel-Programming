#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <omp.h>
#include <windows.h>

using namespace std::chrono;
using namespace std;

vector<vector<double>> multiply(vector<vector<double>>& a, vector<vector<double>>& b,int threads) {
    int size = a.size();
    vector<vector<double>> result(size, vector<double>(size, 0.0));

    omp_set_num_threads(threads);
#pragma omp parallel for collapse(2)
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double sum = 0.0;
                for (int k = 0; k < size; k++) {
                    sum += a[i][k] * b[k][j];
                }
                result[i][j] = sum;
            }
        }
    return result;
}


vector<vector<double>> generate_matrice(int size) {
    vector<vector<double>> matrice(size, vector<double>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrice[i][j] = (rand() % 10000) / 100;
        }
    }
    return matrice;
}

void setCoreAffinity(int cores) {
    DWORD_PTR mask = 0;

    for (int i = 0; i < cores; i++) {
        mask |= (1ULL << i);
    }
    SetProcessAffinityMask(GetCurrentProcess(), mask);
}

int main()
{
    cout << "Input the cores numbers of cores:";
    int core;
    cin >> core;
    cout << "Input the cores numbers of threads:";
    int threads;
    cin >> threads; 

    setCoreAffinity(core);
    
    vector<int> sizes = { 200,400,800,1200,1600 };
    for (int size : sizes) {
        vector<vector<vector<double>>> matrices_group_1;
        vector<vector<vector<double>>> matrices_group_2;
        matrices_group_1.push_back(generate_matrice(size));
        matrices_group_2.push_back(generate_matrice(size));

        cout << "Running the programm with size = " << size << endl;
        cout << "Pair number \t| Execution time(microseconds)" << endl;

        for (int i = 0; i < matrices_group_1.size(); i++) {
            auto start = high_resolution_clock::now();
            auto result = multiply(matrices_group_1[i], matrices_group_2[i], threads);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "\t" << i << "\t| \t" << duration.count() << endl;
        }
    }
}
