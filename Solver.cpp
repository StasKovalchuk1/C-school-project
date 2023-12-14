#include "Solver.h"


template <typename TimePoint>
std::chrono::duration<double> to_seconds(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(tp);
}

Matrix Solver::multiplyAndDisplayTime() {
    auto start = std::chrono::high_resolution_clock::now();
    Matrix matrix = multiply();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Needed " << std::fixed << std::setprecision(6) << to_seconds(end - start).count() << " mсs to finish.\n";
    return matrix;
}

Matrix Solver::multiplyAndDisplayResultAndTime() {
    auto start = std::chrono::high_resolution_clock::now();
    Matrix matrix = multiply();
    auto end = std::chrono::high_resolution_clock::now();
    printMatrix(matrix);
    std::cout << "Needed " << std::fixed << std::setprecision(6) << to_seconds(end - start).count() << " mсs to finish.\n";
    return matrix;
}

void Solver::printMatrix(const Matrix& matrix) {
    std::vector<std::vector<int>> list = matrix.elements;
    std::cout << "Result: \n";
    for (int i = 0; i < list.size(); ++i) {
        for (int j = 0; j < list[0].size(); ++j) {
            std::cout << list[i][j] << " ";
        }
        std::cout << "\n";
    }
}
