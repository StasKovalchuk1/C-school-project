#include "StrassenSolver.h"

std::vector<std::vector<int>> sumMatrix(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
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
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

std::vector<std::vector<int>> subtractMatrix(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int rowsA = A.size();
    int rowsB = B.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsA, 0));

    if (rowsA != rowsB || colsA != colsB) {
        std::cerr << "Failed. Matrices are not the same size! " << std::endl;
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
std::vector<std::vector<int>> makeMatrixToPowerOfTwo(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int extraRows = nearestPowerOfTwo(rows);
    int extraCols = nearestPowerOfTwo(cols);

    std::vector<std::vector<int>> newMatrix(extraRows, std::vector<int>(extraCols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    return newMatrix;
}

// remove extra null rows and columns
std::vector<std::vector<int>> removePadding(const std::vector<std::vector<int>>& matrix, int origRows, int origCols) {
    std::vector<std::vector<int>> result(origRows, std::vector<int>(origCols, 0));

    for (int i = 0; i < origRows; i++) {
        for (int j = 0; j < origCols; j++) {
            result[i][j] = matrix[i][j];
        }
    }

    return result;
}

std::vector<std::vector<int>> multiplyRec(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();

    if (n == 1) {
        std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    // new sub-matrices
    std::vector<std::vector<int>> A11(k, std::vector<int>(k, 0));
    std::vector<std::vector<int>> A12(k, std::vector<int>(k, 0));
    std::vector<std::vector<int>> A21(k, std::vector<int>(k, 0));
    std::vector<std::vector<int>> A22(k, std::vector<int>(k, 0));

    std::vector<std::vector<int>> B11(k, std::vector<int>(k, 0));
    std::vector<std::vector<int>> B12(k, std::vector<int>(k, 0));
    std::vector<std::vector<int>> B21(k, std::vector<int>(k, 0));
    std::vector<std::vector<int>> B22(k, std::vector<int>(k, 0));

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

    std::vector<std::vector<int>> P1 = multiplyRec(sumMatrix(A11, A22), sumMatrix(B11, B22));
    std::vector<std::vector<int>> P2 = multiplyRec(sumMatrix(A21, A22), B11);
    std::vector<std::vector<int>> P3 = multiplyRec(A11, subtractMatrix(B12, B22));
    std::vector<std::vector<int>> P4 = multiplyRec(A22, subtractMatrix(B21, B11));
    std::vector<std::vector<int>> P5 = multiplyRec(sumMatrix(A11, A12), B22);
    std::vector<std::vector<int>> P6 = multiplyRec(subtractMatrix(A21, A11), sumMatrix(B11, B12));
    std::vector<std::vector<int>> P7 = multiplyRec(subtractMatrix(A12, A22), sumMatrix(B21, B22));

    std::vector<std::vector<int>> C1 = subtractMatrix(sumMatrix(sumMatrix(P1, P4), P7), P5);
    std::vector<std::vector<int>> C2 = sumMatrix(P3, P5);
    std::vector<std::vector<int>> C3 = sumMatrix(P2, P4);
    std::vector<std::vector<int>> C4 = sumMatrix(subtractMatrix(sumMatrix(P1, P3), P2), P6);

    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

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

Matrix StrassenSolver::multiply() {
    std::vector<std::vector<int>> result = multiplyRec(matrix1.elements, matrix2.elements);
    return Matrix(result);
}