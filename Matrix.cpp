#include "Matrix.hpp"


bool Matrix::read(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "File " << fileName << " was not opened" << std::endl;
        return false;
    }

    // Read the first line
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    int rows, cols;
    ss >> rows >> cols;

    // Check that rows and cols are valid
    if (rows <= 0 || cols <= 0 || rows != cols) {
        std::cerr << "Incorrect number of rows or columns" << std::endl;
        return false;
    }

    // Create the matrix
    elements.resize(rows);

    // Read the rest of the matrix
    for (int i = 0; i < rows; ++i) {
        std::getline(file, line);
        std::stringstream ss(line);
        // Check the number of elements in the row
        int count = 0;
        for (char c : line) {
            if (isdigit(c)) {
                ++count;
            }
        }
        if (count != cols) {
            std::cerr << "Incorrect number of elements in row " << i + 1 << std::endl;
            return false;
        }
        elements[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            ss >> elements[i][j];
        }
    }

    file.close();
    return true;
}

Matrix::Matrix() {
    elements = std::vector<std::vector<int>>();
}

Matrix::Matrix(std::vector<std::vector<int>> &elements) {
    this->elements = elements;
}

Matrix::Matrix(size_t rows, size_t cols) {
    elements = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < cols; ++j) {
            int randomNumber = std::rand() % 50 + 1;
            elements[i][j] = randomNumber;
        }
    }
}
