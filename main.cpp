#include <filesystem>
#include <fstream>

#include "Matrix.hpp"
#include "Solver.h"
#include "BasicSolver.h"
#include "StrassenSolver.h"

using namespace std;

int main() {
    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path());

    Matrix matrix1;
    Matrix matrix2;

    matrix1.read("matice-1.txt");
    matrix2.read("matice-2.txt");

    Matrix result;

    result = BasicSolver(matrix1, matrix2).multiplyAndDisplayTime();

    cout << " ----------------------------------------- \n";

    result = StrassenSolver(matrix1, matrix2).multiplyAndDisplayTime();

    return 0;
}
