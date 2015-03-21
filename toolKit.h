/*
 * toolKit.h
 *
 *  Created on: 16 ���� 2015
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
		PartialSolution();
		PartialSolution(PartialSolution *part);
		bool IsCellDecided(int row,int col);
		void setDecisionBit(int row, int col,bool trueFalse);
		bool checkAllDecided();
		bool isOneOptionLeftForCell(int row,int col);
		int NumOFOptionsForCell(int row,int col);
		bool setOptionForCell(int row, int col, int option, bool trueFalse);
		bool getOptionForCell(int row, int col, int option);


};

class Constraint
{
	private:
		std::vector<int> rows;
		std::vector<int> things;
		std::vector<std::vector<int> > permutations;
	public:
		Constraint(Rule *rule);
		void print();
		bool isVarPresent(int row,int thing);
		int checkNumOfVars();
		bool checkConstraintHoldsForSol(PartialSolution* sol);

};

class AllConstraints
{
	private:
		std::vector<Constraint> all;
	public:
		AllConstraints(Rules rules);
		std::vector<Constraint> returnReleventConstraints(int row,int thing);
		bool checkSolKeepsAllConstraints(PartialSolution* sol);

};

#endif /* TOOLKIT_H_ */
