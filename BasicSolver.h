#ifndef NASOBENI_MATIC_BASICSOLVER_H
#define NASOBENI_MATIC_BASICSOLVER_H
#include "Solver.h"

class BasicSolver : public Solver{
public:
    BasicSolver(Matrix matrix1, Matrix matrix2) : Solver(matrix1, matrix2) {}

    Matrix multiply() override;
};


#endif //NASOBENI_MATIC_BASICSOLVER_H
