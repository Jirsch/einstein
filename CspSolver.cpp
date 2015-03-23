//
// Created by Jonathan Hirsch on 3/21/15.
//

#include "CspSolver.h"

CspSolver::CspSolver(Rules rules) : constraints(rules)
{
}

PartialSolution * CspSolver::backtrack()
{
    PartialSolution blankSol = PartialSolution();
    PartialSolution result;

    bool f =rBacktrack(blankSol, result);
    return new PartialSolution(result);

}

bool CspSolver::rBacktrack(PartialSolution &sol, PartialSolution &result)
{
    int row, option;

    chooseVariable(sol, row, option);
    std::vector<int> cols = chooseCol(sol, row, option);

    if (cols.size() == 0)
    {
        return NULL;
    }

    for (std::vector<int>::iterator i = cols.begin(); i != cols.end(); ++i)
    {
        int col = *i;
        result = PartialSolution(sol);
        result.chooseOptionForCell(row, col, option);
        if (constraints.isSolValid(&result))
        {
            if (result.allDecided())
            {
                return true;
            }
            else
            {
                PartialSolution childResult;
                if (rBacktrack(result, childResult))
                {
                    result=PartialSolution(childResult);
                    return true;
                }
            }
        }
    }


    return false;
}

void CspSolver::chooseVariable(PartialSolution &sol, int &row, int &option)
{
    // Naive implementation
    for (row = 0; row < ARR_SIZE; ++row)
    {
        for (option = 0; option < ARR_SIZE; ++option)
        {
            if (!sol.isOptionDecided(row, option)) return;
        }
    }

    row = -1;
    option = -1;
}

std::vector<int> CspSolver::chooseCol(PartialSolution &sol, int row, int option)
{
    std::vector<int> result = std::vector<int>();

    for (int col = 0; col < ARR_SIZE; ++col)
    {
        if (sol.getOptionForCell(row, col, option))
        {
            result.push_back(col);
        }
    }

    return result;
}
