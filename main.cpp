#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <filesystem>

using namespace std;

vector<vector<int>> multiplyMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    vector<vector<int>> C(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;

//    int n = A.size();
//    vector<vector<int>> C(n, vector<int>(n, 0));
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            C[i][j] = A[i][j] - B[i][j];
//        }
//    }
//    return C;
}

vector<vector<int>> sumMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
//    int rowsA = A.size();
//    int rowsB = B.size();
//    int colsA = A[0].size();
//    int colsB = B[0].size();
//    vector<vector<int>> C(rowsA, vector<int>(colsA, 0));
//
//    if (rowsA != rowsB || colsA != colsB) {
//        cerr << "Failed. Matrices are not the same size! " << endl;
//        return C;
//    }
//
//    for (int i = 0; i < rowsA; i++) {
//        for (int j = 0; j < colsA; j++) {
//            C[i][j] = A[i][j] + B[i][j];
//        }
//    }
//    return C;
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int rowsB = B.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    vector<vector<int>> C(rowsA, vector<int>(colsA, 0));

    if (rowsA != rowsB || colsA != colsB) {
        cerr << "Failed. Matrices are not the same size! " << endl;
        return C;
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

int nearestPowerOfTwo(int n) {
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

// add extra rows and cols
std::vector<std::vector<int>> makeMatrixToPowerOfTwo(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int extraRows = nearestPowerOfTwo(rows);
    int extraCols = nearestPowerOfTwo(cols);

    vector<vector<int>> newMatrix(extraRows, vector<int>(extraCols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    return newMatrix;
}

// remove extra null rows and columns
vector<std::vector<int>> removePadding(const vector<std::vector<int>>& matrix, int origRows, int origCols) {
    vector<std::vector<int>> result(origRows, std::vector<int>(origCols, 0));

    for (int i = 0; i < origRows; i++) {
        for (int j = 0; j < origCols; j++) {
            result[i][j] = matrix[i][j];
        }
    }

    return result;
}

vector<vector<int>> multiStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    // new sub-matrices
    vector<vector<int>> A11(k, vector<int>(k, 0));
    vector<vector<int>> A12(k, vector<int>(k, 0));
    vector<vector<int>> A21(k, vector<int>(k, 0));
    vector<vector<int>> A22(k, vector<int>(k, 0));

    vector<vector<int>> B11(k, vector<int>(k, 0));
    vector<vector<int>> B12(k, vector<int>(k, 0));
    vector<vector<int>> B21(k, vector<int>(k, 0));
    vector<vector<int>> B22(k, vector<int>(k, 0));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    vector<vector<int>> P1 = multiStrassen(sumMatrix(A11, A22), sumMatrix(B11, B22));
    vector<vector<int>> P2 = multiStrassen(sumMatrix(A21, A22), B11);
    vector<vector<int>> P3 = multiStrassen(A11, subtractMatrix(B12, B22));
    vector<vector<int>> P4 = multiStrassen(A22, subtractMatrix(B21, B11));
    vector<vector<int>> P5 = multiStrassen(sumMatrix(A11, A12), B22);
    vector<vector<int>> P6 = multiStrassen(subtractMatrix(A21, A11), sumMatrix(B11, B12));
    vector<vector<int>> P7 = multiStrassen(subtractMatrix(A12, A22), sumMatrix(B21, B22));

    vector<vector<int>> C1 = subtractMatrix(sumMatrix(sumMatrix(P1, P4), P7), P5);
    vector<vector<int>> C2 = sumMatrix(P3, P5);
    vector<vector<int>> C3 = sumMatrix(P2, P4);
    vector<vector<int>> C4 = sumMatrix(subtractMatrix(sumMatrix(P1, P3), P2), P6);

    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];
            C[i + k][j] = C3[i][j];
            C[i + k][j + k] = C4[i][j];
        }
    }
    return C;

}

bool getMatrixFromFile(const string& fileName, vector<vector<int>>& matrix) {
    ifstream file;
    file.open(fileName);
    if (!file) {
        cerr << "File " << fileName << " was not opened" << endl;
        return false;
    }

    int rows;
    int cols;

    if (!(file >> rows >> cols)) {
        std::cerr << "Failed to read matrix size" << endl;
        return false;
    }

    matrix.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
//            cout << matrix[i][j-1];
            if (!(file >> matrix[i][j])) {
                std::cerr << "Failed to read element " << i << " " << j << endl;
                return false;
            }
        }
    }
    file.close();

    return true;
}

void printMatrix(vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

template <typename TimePoint>
std::chrono::microseconds to_mсs(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::microseconds>(tp);
}

int main() {
    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path());
    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    vector<vector<int>> matrix3;

    if (getMatrixFromFile("matice-1.txt", matrix1) && getMatrixFromFile("matice-2.txt", matrix2)) {

        // regular algoritmh
        auto start = chrono::high_resolution_clock::now();
        matrix3 = multiplyMatrix(matrix1, matrix2);
        auto end = chrono::high_resolution_clock::now();

//        printMatrix(matrix3);
        cout << "Needed " << to_mсs(end - start).count() << " mсs to finish.\n";

        cout << " ----------------------------------------- \n";

        // strassen algoritm
        vector<vector<int>> newMatrix1 = makeMatrixToPowerOfTwo(matrix1);
        vector<vector<int>> newMatrix2 = makeMatrixToPowerOfTwo(matrix2);

        start = chrono::high_resolution_clock::now();
        matrix3 = multiStrassen(newMatrix1, newMatrix2);
        end = chrono::high_resolution_clock::now();

        matrix3 = removePadding(matrix3, matrix1.size(), matrix2[0].size());
//        printMatrix(matrix3);
        cout << "Needed " << to_mсs(end - start).count() << " mсs to finish.\n";
    }

    return 0;
}
