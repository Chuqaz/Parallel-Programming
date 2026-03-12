#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

vector<vector<double>> load_matrix_from_file(string &filename) {
    std::ifstream in(filename);

    if (!in.is_open()) {
        cout << "Mistake.The programm cannot open the file.";
        return {};
    }

    int size;
    in >> size;

    vector<vector<double>> matrix(size, vector<double>(size));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            in >> matrix[i][j];
        }
    }
    in.close();
    return matrix;
}

vector<vector<double>> multiply(vector<vector<double>>& a, vector<vector<double>>& b) {
    int size = a.size();

    vector<vector<double>> result(size, vector<double>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

void verification() {
    system("py check.py");
}

vector<vector<double>> generate_matrice(int size) {
    vector<vector<double>> matrice(size, vector<double>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrice[i][j] = rand() / 100;
        }
    }
    return matrice;
}

void save_matrix(vector<vector<vector<double>>>& result,string filename) {
    std::ofstream file(filename);

    file << result.size()<<endl;
    file << result[0].size() << endl;

    for (int n = 0; n < result.size(); n++) {
        for (int i = 0; i <result[n].size(); i++) {
            for (int j = 0; j < result[n].size(); j++) {
                file << result[n][i][j] << " ";
            }
            file << endl;
        }
        file << endl;
    }
    file.close();
}

int main()
{
    cout << "Code in C++" << endl;
    cout << "Input a size for generating matrices:";
    int size;
    cin >> size;
    cout << "Input file name for matrices group 1:";
    string filename_1;
    cin >> filename_1;
    cout << "Input file name for matrices group 2:";
    string filename_2;
    cin >> filename_2;
    vector<vector<vector<double>>> matrices_group_1;
    for (int i = 0; i < 10; i++) {
        matrices_group_1.push_back(generate_matrice(size));
    }
    save_matrix(matrices_group_1, filename_1);
    vector<vector<vector<double>>> matrices_group_2;
    for (int i = 0; i < 10; i++) {
        matrices_group_2.push_back(generate_matrice(size));
    }
    save_matrix(matrices_group_2, filename_2);
    vector<vector<vector<double>>> matrices_group_result;
    for (int i = 0; i < matrices_group_1.size(); i++) {
        auto start = high_resolution_clock::now();
        vector<vector<double>> result = multiply(matrices_group_1[i], matrices_group_2[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Pair number " << i << endl;
        cout << "Execution time: " << duration.count() << " microseconds" << endl;
        matrices_group_result.push_back(result);
    }
    string filename_3 = "matrix_c++.txt";
    save_matrix(matrices_group_result, filename_3);
    verification();
}
