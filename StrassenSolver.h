//
// Created by Станислав Ковальчук on 30.11.2023.
//
#include "Solver.h"
#ifndef NASOBENI_MATIC_STRASSENSOLVER_H
#define NASOBENI_MATIC_STRASSENSOLVER_H


class StrassenSolver : public Solver{
public:
    StrassenSolver(Matrix matrix1, Matrix matrix2) : Solver(matrix1, matrix2) {}

    Matrix multiply() override;
};


#endif //NASOBENI_MATIC_STRASSENSOLVER_H
