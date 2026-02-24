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

void save_matrix(vector<vector<double>>& result) {
    std::ofstream file("matrix_c++.txt");

    file << result.size()<<endl;


    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            file << result[i][j];
            if (j < result.size() - 1) file << " ";
        }
        file << endl;
    }

}

int main()
{
    cout << "Input file name for matrice 1:";
    string filename_1;
    cin >> filename_1;
    vector<vector<double>> matrice_1 = load_matrix_from_file(filename_1);
    cout << "Input file name for matrice 2:";
    string filename_2;
    cin >> filename_2;
    vector<vector<double>> matrice_2 = load_matrix_from_file(filename_2);
    auto start = high_resolution_clock::now();
    vector<vector<double>> result = multiply(matrice_1,matrice_2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    save_matrix(result);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    cout << "Matrice size: " << result.size() << "x" << result.size() << endl;
    verification();
}
