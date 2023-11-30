#include "BasicSolver.h"

Matrix BasicSolver::multiply() {
    std::vector<std::vector<int>> A = matrix1.elements;
    std::vector<std::vector<int>> B = matrix2.elements;
    size_t rowsA = A.size();
    size_t colsA = A[0].size();
    size_t colsB = B[0].size();

    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return Matrix(C);
}