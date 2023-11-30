#include "Matrix.hpp"


void Matrix::read(const std::string &fileName) {
    std::ifstream file;
    file.open(fileName);
    if (!file) {
        std::cerr << "File " << fileName << " was not opened" << std::endl;
        return;
    }

    int rows;
    int cols;

    if (!(file >> rows >> cols)) {
        std::cerr << "Failed to read matrix size" << std::endl;
        return;
    }

    elements.resize(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> elements[i][j])) {
                std::cerr << "Failed to read element " << i << " " << j << std::endl;
                return;
            }
        }
    }
    file.close();
}

Matrix::Matrix() {
    elements = std::vector<std::vector<int>>();
}

Matrix::Matrix(std::vector<std::vector<int>> &elements) {
    this->elements = elements;
}
