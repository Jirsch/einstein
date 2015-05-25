//
// Created by Jonathan Hirsch on 3/21/15.
//

#include "CspSolver.h"

CspSolver::CspSolver(Rules rules) : constraints(rules)
{
}

PartialSolution *CspSolver::backtrack()
{
    PartialSolution blankSol = PartialSolution();
    PartialSolution result;


    clock_t begin_time;
    clock_t end_time;


    begin_time = clock();
    useVariableHeuristic = false;
    useForwardChecking = false;
    bool f = rBacktrack(blankSol, result);
    end_time = clock();
    //std::cout << ((float) end_time - begin_time) << "," << ((float) end_time - begin_time) / CLOCKS_PER_SEC;
    std::cout << "Solution not using variable heuristic " << ((float) end_time - begin_time) << " ticks" << std::endl;
    std::cout << "Solution not using variable heuristic " << ((float) end_time - begin_time) / CLOCKS_PER_SEC << " seconds" << std::endl;


    begin_time = clock();
    useVariableHeuristic = true;
    useForwardChecking = false;
    f = rBacktrack(blankSol, result);
    end_time = clock();
//    std::cout << "," << ((float) end_time - begin_time) << "," << ((float) end_time - begin_time) / CLOCKS_PER_SEC;
    std::cout << "Solution using variable heuristic " << ((float) end_time - begin_time) << " ticks" << std::endl;
    std::cout << "Solution using variable heuristic " << ((float) end_time - begin_time) / CLOCKS_PER_SEC << " seconds" << std::endl;

    begin_time = clock();
    useVariableHeuristic = false;
    useForwardChecking = true;
    f = rBacktrack(blankSol, result);
    end_time = clock();
//    std::cout << "," << ((float) end_time - begin_time) << "," << ((float) end_time - begin_time) / CLOCKS_PER_SEC;
    std::cout << "Solution not using variable heuristic but using forward checking " << ((float) end_time - begin_time) << " ticks" << std::endl;
    std::cout << "Solution not using variable heuristic but using forward checking " << ((float) end_time - begin_time) / CLOCKS_PER_SEC << " seconds" << std::endl;


    begin_time = clock();
    useVariableHeuristic = true;
    useForwardChecking = true;
    f = rBacktrack(blankSol, result);
    end_time = clock();
//    std::cout << "," << ((float) end_time - begin_time) << "," << ((float) end_time - begin_time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "Solution using variable heuristic and using forward checking " << ((float) end_time - begin_time) << " ticks" << std::endl;
    std::cout << "Solution using variable heuristic and using forward checking " << ((float) end_time - begin_time) / CLOCKS_PER_SEC << " seconds" << std::endl;


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
        result.chooseOptionForCell(row, col, option, useForwardChecking);
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
                    result = PartialSolution(childResult);
                    return true;
                }
            }
        }
    }


    return false;
}

bool compareRemainingValues(const std::vector<int> &first, const std::vector<int> &second)
{
    if (first.at(2) == second.at(2))
    {
        // the one with more constraints
        return first.at(3) >= second.at(3);
    }
    // the one with less options
    return first.at(2) < second.at(2);
}

void CspSolver::chooseVariable(PartialSolution &sol, int &row, int &option)
{
    if (!useVariableHeuristic)
    {
        // Naive implementation
        for (row = 0; row < ARR_SIZE; ++row)
        {
            for (option = 0; option < ARR_SIZE; ++option)
            {
                if (!sol.isOptionDecided(row, option)) return;
            }
        }

    }
    else
    {
        std::list<std::vector<int> > variableRemainingOptions;
        std::vector<int> temp;

        for (int row = 0; row < ARR_SIZE; ++row)
        {
            for (int option = 0; option < ARR_SIZE; ++option)
            {
                if (!sol.isOptionDecided(row, option))
                {
                    temp.push_back(row);
                    temp.push_back(option);
                    temp.push_back(sol.numOfCellsForOption(row, option));
                    temp.push_back(this->constraints.returnReleventConstraints(row, option).size());
                    variableRemainingOptions.push_back(temp);
                    temp.clear();
                }
            }
        }

        variableRemainingOptions.sort(compareRemainingValues);
        temp = variableRemainingOptions.front();
        row = temp.at(0);
        option = temp.at(1);
    }
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
