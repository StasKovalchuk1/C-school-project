#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#ifndef NASOBENI_MATIC_MATRIX_H
#define NASOBENI_MATIC_MATRIX_H


class Matrix {

public:
    bool read(const std::string& fileName);

    std::vector<std::vector<int> > elements;

    Matrix();

    explicit Matrix(std::vector<std::vector<int> > &elements);

    explicit Matrix(size_t rows, size_t cols);

};


#endif //NASOBENI_MATIC_MATRIX_H
