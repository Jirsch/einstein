//
// Created by Jonathan Hirsch on 3/21/15.
//

#ifndef _EINSTEIN_CSPSOLVER_H_
#define _EINSTEIN_CSPSOLVER_H_

#include "puzgen.h"
#include "toolKit.h"

class CspSolver {
private:
    AllConstraints constraints;
    bool rBacktrack(PartialSolution &curr, PartialSolution &result);
    void chooseVariable(PartialSolution &sol, int &row, int &option);
    std::vector<int> chooseCol(PartialSolution &sol, int row, int option);


public:
    CspSolver(Rules rules);
    PartialSolution * backtrack();
};


#endif //_EINSTEIN_CSPSOLVER_H_
