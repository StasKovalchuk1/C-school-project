#include "Solver.h"


template <typename TimePoint>
std::chrono::microseconds to_mсs(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::microseconds>(tp);
}

Matrix Solver::multiplyAndDisplayTime() {
    auto start = std::chrono::high_resolution_clock::now();
    Matrix matrix = multiply();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Needed " << to_mсs(end - start).count() << " mсs to finish.\n";
    return matrix;
}
