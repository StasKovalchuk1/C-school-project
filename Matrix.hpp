#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#ifndef NASOBENI_MATIC_MATRIX_H
#define NASOBENI_MATIC_MATRIX_H


class Matrix {

public:
    void read(const std::string& fileName);

    std::vector<std::vector<int>> elements;

    Matrix();

    explicit Matrix(std::vector<std::vector<int>> &elements);

};


#endif //NASOBENI_MATIC_MATRIX_H
