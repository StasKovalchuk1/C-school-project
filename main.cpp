#include <filesystem>
#include <fstream>

#include "Matrix.hpp"
#include "Solver.h"
#include "BasicSolver.h"
#include "StrassenSolver.h"

using namespace std;

void printHelp() {
    std::cout << "Usage: ./nasobeni_matic {-h | --help |-f <file> <file2> | -r <x>} {-b|-s} {-short|-full}" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help Show this help message and exit" << std::endl;
    std::cout << "  -f <file1> <file2> Read matrices from files" << std::endl;
    std::cout << "  -r <size> Generate random matrices with size <size>" << std::endl;
    std::cout << "  -b Use basic solver" << std::endl;
    std::cout << "  -s Use strassen solver" << std::endl;
    std::cout << "  -short Print only time" << std::endl;
    std::cout << "  -full Print time and result matrix" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2 || argv[1] == std::string("-h") || argv[1] == std::string("--help")) {
        printHelp();
        return 0;
    }

    Matrix matrix1;
    Matrix matrix2;
    Matrix result;
    size_t elemIndex = 0;
    if (argv[1] == std::string("-f")) {
        if (argc < 4) {
            printHelp();
            return 0;
        }
        matrix1.read(argv[2]);
        matrix2.read(argv[3]);
        elemIndex = 4;
    } else if (argv[1] == std::string("-r")){
        if (argc < 3) {
            printHelp();
            return 0;
        }
        matrix1 = Matrix(std::stoi(argv[2]), std::stoi(argv[2]));
        matrix2 = Matrix(std::stoi(argv[2]), std::stoi(argv[2]));
        elemIndex = 3;
    }

    if (argc > elemIndex) {
        if (argv[elemIndex] == std::string("-b")) {
            elemIndex++;
            if (argc == elemIndex + 1) {
                if (argv[elemIndex] == std::string("-short")) {
                    result = BasicSolver(matrix1, matrix2).multiplyAndDisplayTime();
                } else if (argv[elemIndex] == std::string("-full")) {
                    result = BasicSolver(matrix1, matrix2).multiplyAndDisplayResultAndTime();
                }
            } else {
                printHelp();
                return 0;
            }
        } else if (argv[elemIndex] == std::string("-s")) {
            elemIndex++;
            if (argc == elemIndex + 1) {
                if (argv[elemIndex] == std::string("-short")) {
                    result = StrassenSolver(matrix1, matrix2).multiplyAndDisplayTime();
                } else if (argv[elemIndex] == std::string("-full")) {
                    result = StrassenSolver(matrix1, matrix2).multiplyAndDisplayResultAndTime();
                }
            } else {
                printHelp();
                return 0;
            }
        }
        elemIndex++;
    }

    if (argc > elemIndex) {
        printHelp();
        return 0;
    }
}

//int main() {
//    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path());
//
//    Matrix matrix1;
//    Matrix matrix2;
//
////    matrix1 = Matrix(64, 64);
////    matrix2 = Matrix(64, 64);
//
//    if (!matrix1.read("matice-1.txt")) {
//        return 0;
//    }
//    if (!matrix2.read("matice-1.txt")) {
//        return 0;
//    }
//
//    Matrix result;
//
//    result = BasicSolver(matrix1, matrix2).multiplyAndDisplayResultAndTime();
//
//    cout << " ----------------------------------------- \n";
//
//    result = StrassenSolver(matrix1, matrix2).multiplyAndDisplayResultAndTime();
//
//
//    return 0;
//}
