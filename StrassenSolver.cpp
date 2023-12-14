#include "StrassenSolver.h"

using namespace std;

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

void add(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void Strassen_algorithmA(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int size)
{
    //base case
    if (size == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else
    {
        int new_size = size / 2;

        std::vector<std::vector<int>> a11(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> a12(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> a21(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> a22(new_size, std::vector<int>(new_size, 0));

        std::vector<std::vector<int>> b11(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> b12(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> b21(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> b22(new_size, std::vector<int>(new_size, 0));

        std::vector<std::vector<int>> c11(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> c12(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> c21(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> c22(new_size, std::vector<int>(new_size, 0));

        std::vector<std::vector<int>> p1(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> p2(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> p3(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> p4(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> p5(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> p6(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> p7(new_size, std::vector<int>(new_size, 0));

        std::vector<std::vector<int>> aResult(new_size, std::vector<int>(new_size, 0));
        std::vector<std::vector<int>> bResult(new_size, std::vector<int>(new_size, 0));

        //dividing matrices into sub-matrices:
        for (int i = 0; i < new_size; i++)
        {
            for (int j = 0; j < new_size; j++)
            {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + new_size];
                a21[i][j] = A[i + new_size][j];
                a22[i][j] = A[i + new_size][j + new_size];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + new_size];
                b21[i][j] = B[i + new_size][j];
                b22[i][j] = B[i + new_size][j + new_size];
            }
        }

        // p1 = (a11+a22) * (b11+b22)
        add(a11, a22, aResult, new_size);
        add(b11, b22, bResult, new_size);
        Strassen_algorithmA(aResult, bResult, p1, new_size);

        // p2 = (a21+a22) * (b11)
        add(a21, a22, aResult, new_size);
        Strassen_algorithmA(aResult, b11, p2, new_size);

        // p3 = (a11) * (b12 - b22)
        subtract(b12, b22, bResult, new_size);
        Strassen_algorithmA(a11, bResult, p3, new_size);

        // p4 = (a22) * (b21 - b11)
        subtract(b21, b11, bResult, new_size);
        Strassen_algorithmA(a22, bResult, p4, new_size);

        // p5 = (a11+a12) * (b22)
        add(a11, a12, aResult, new_size);
        Strassen_algorithmA(aResult, b22, p5, new_size);

        // p6 = (a21-a11) * (b11+b12)
        subtract(a21, a11, aResult, new_size);
        add(b11, b12, bResult, new_size);
        Strassen_algorithmA(aResult, bResult, p6, new_size);

        // p7 = (a12-a22) * (b21+b22)
        subtract(a12, a22, aResult, new_size);
        add(b21, b22, bResult, new_size);
        Strassen_algorithmA(aResult, bResult, p7, new_size);

        // calculating c21, c21, c11 e c22:

        add(p3, p5, c12, new_size); // c12 = p3 + p5
        add(p2, p4, c21, new_size); // c21 = p2 + p4

        add(p1, p4, aResult, new_size);
        add(aResult, p7, bResult, new_size);
        subtract(bResult, p5, c11, new_size); // c11 = p1 + p4 - p5 + p7

        add(p1, p3, aResult, new_size);
        add(aResult, p6, bResult, new_size);
        subtract(bResult, p2, c22, new_size); // c22 = p1 + p3 - p2 + p6

        // grouping results in a single matrix:
        for (int i = 0; i < new_size; i++)
        {
            for (int j = 0; j < new_size; j++)
            {
                C[i][j] = c11[i][j];
                C[i][j + new_size] = c12[i][j];
                C[i + new_size][j] = c21[i][j];
                C[i + new_size][j + new_size] = c22[i][j];
            }
        }
    }
}


Matrix StrassenSolver::multiply() {
    std::vector<std::vector<int>> result(matrix1.elements.size(), vector<int>(matrix1.elements.size(), 0));
    Strassen_algorithmA(matrix1.elements, matrix2.elements, result, result.size());
    return Matrix(result);
}

template <typename TimePoint>
std::chrono::duration<double> to_seconds(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(tp);
}

Matrix StrassenSolver::multiplyAndDisplayTime() {
    int originRows = matrix1.elements.size();
    int originCols = matrix1.elements[0].size();
    matrix1.elements = makeMatrixToPowerOfTwo(matrix1.elements);
    matrix2.elements = makeMatrixToPowerOfTwo(matrix2.elements);
    auto start = std::chrono::high_resolution_clock::now();
    Matrix matrix = multiply();
    auto end = std::chrono::high_resolution_clock::now();
    matrix.elements = removePadding(matrix.elements, originRows, originCols);
    std::cout << "Needed " << std::fixed <<std::setprecision(6) << to_seconds(end - start).count() << " mсs to finish.\n";
    return matrix;
}

Matrix StrassenSolver::multiplyAndDisplayResultAndTime() {
    int originRows = matrix1.elements.size();
    int originCols = matrix1.elements[0].size();
    matrix1.elements = makeMatrixToPowerOfTwo(matrix1.elements);
    matrix2.elements = makeMatrixToPowerOfTwo(matrix2.elements);
    auto start = std::chrono::high_resolution_clock::now();
    Matrix matrix = multiply();
    auto end = std::chrono::high_resolution_clock::now();
    matrix.elements = removePadding(matrix.elements, originRows, originCols);
    printMatrix(matrix);
    std::cout << "Needed " << std::fixed <<std::setprecision(6) << to_seconds(end - start).count() << " mсs to finish.\n";
    return matrix;
}