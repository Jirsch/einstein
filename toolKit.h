/*
 * toolKit.h
 *
 *  Created on: 16 במרס 2015
 *      Author: Lior
 */

#ifndef TOOLKIT_H_
#define TOOLKIT_H_

#include <bitset>
#include "puzgen.h"

#define SIZE_OF_BITSET 8
#define DECISION_BIT 7
#define ARR_SIZE 6

class PartialSolution
{
	private:
		std::bitset<SIZE_OF_BITSET> solArr[ARR_SIZE][ARR_SIZE];
	public:
		PartialSolution:: PartialSolution();
		PartialSolution::PartialSolution(PartialSolution* part);
		bool PartialSolution:: IsCellDecided(int row,int col);
		void PartialSolution:: setDecisionBit(int row, int col,bool trueFalse);
		bool PartialSolution::checkAllDecided();
		bool PartialSolution::isOneOptionLeftForCell(int row,int col);
		int PartialSolution::NumOFOptionsForCell(int row,int col);
		bool PartialSolution::setOptionForCell(int row, int col, int option, bool trueFalse);
		bool PartialSolution::getOptionForCell(int row, int col, int option);


};

class Constraint
{
	private:
		std::vector<int> rows;
		std::vector<int> things;
		std::vector<std::vector<int> > permutations;
	public:
		Constraint::Constraint(Rule *rule);
		void Constraint::print();
		bool Constraint::isVarPresent(int row,int thing);
		int Constraint::checkNumOfVars();
		bool Constraint::checkConstraintHoldsForSol(PartialSolution* sol);

};

class AllConstraints
{
	private:
	std::vector<Constraint> all;
	public:
	AllConstraints::AllConstraints(Rules rules);
	std::vector<Constraint> AllConstraints::returnReleventConstraints(int row,int thing);
	bool AllConstraints::checkSolKeepsAllConstraints(PartialSolution* sol);

};









#endif /* TOOLKIT_H_ */
