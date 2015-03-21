/*
 * toolKit.cpp
 *
 *  Created on: 14 ���� 2015
 *      Author: Lior
 */

#include <Tcl/tcl.h>
#include "toolKit.h"

#define SIZE_OF_BITSET 8
#define DECISION_BIT 7
#define ARR_SIZE 6

//TODO i looked at everything as if it can receive values 0-5. we must check this is the case


//sets everything to 0, decision bit to 1
PartialSolution::PartialSolution()
{
	for (int row=0;row<ARR_SIZE;row++)
	{
		for (int col=0;col<ARR_SIZE;col++)
		{
			solArr[row][col].set();
			solArr[row][col].set(DECISION_BIT,false);
		}
	}
}

//copy constructor-if we need one
PartialSolution::PartialSolution(PartialSolution* part)
{
	for (int row=0;row<ARR_SIZE;row++)
	{
		for (int col=0;col<ARR_SIZE;col++)
		{
			solArr[row][col]=part->solArr[row][col];
		}
	}
}


bool PartialSolution:: IsCellDecided(int row,int col)
{
	return solArr[row][col].test(DECISION_BIT);
}

void PartialSolution:: setDecisionBit(int row, int col,bool trueFalse)
{
	solArr[row][col].set(DECISION_BIT,trueFalse);
}


bool PartialSolution::checkAllDecided()
{
	for (int row=0;row<ARR_SIZE;row++)
			{
				for (int col=0;col<ARR_SIZE;col++)
				{
					if (!solArr[row][col].test(DECISION_BIT)) return false;
				}
			}
	return true;
}


bool PartialSolution::isOneOptionLeftForCell(int row,int col)
{
	return ( this->NumOFOptionsForCell(row,col)==1 );
}


int PartialSolution::NumOFOptionsForCell(int row,int col)
{
	int count = 0;
	for (int i=0;i<ARR_SIZE;i++)
	{
		if (solArr[row][col][i])
		{
			count++;
		}
	}
	return count;
}


bool PartialSolution::setOptionForCell(int row, int col, int option, bool trueFalse)
{
	if ((option>5) || (option <0)) return false;
	solArr[row][col].set(option,trueFalse);
	return true;
}

bool PartialSolution::getOptionForCell(int row, int col, int option)
{
	//if ((option>5) || (option <0)) return false;
	//TODO throw exception? im lazy. lets not call this with a bad option ok? ok
	return solArr[row][col].test(option);
}



Constraint::Constraint(Rule *rule)
{
	std::vector<int> param= rule->parameterList();
	std::string className=rule->className();

	if (className=="NearRule")
	{
		int thing1[2];
		int thing2[2];

		thing1[0]=param[0];
		thing1[1]=param[1];
		thing2[0]=param[2];
		thing2[1]=param[3];

		//TODO check this is the correct order of input
		rows.push_back(thing1[0]);
		rows.push_back(thing2[0]);
		things.push_back(thing1[1]);
		things.push_back(thing2[1]);

		std::vector<int> temp;
		for (int i=0;i<ARR_SIZE-1;++i)
		{
			temp.push_back(i);
			temp.push_back(i+1);
			permutations.push_back(temp);
			temp.clear();

			temp.push_back(i+1);
			temp.push_back(i);
			permutations.push_back(temp);
			temp.clear();
		}

	}
	else if (className=="DirectionRule")
	{
		int row1 = param[0];
		int thing1 = param[1];
		int row2 = param[2];
		int thing2 = param [3];

		rows.push_back(row1);
		rows.push_back(row2);
		things.push_back(thing1);
		things.push_back(thing2);

		std::vector<int> temp;
		for (int first=0; first<ARR_SIZE;first++)
		{
			for (int second=first+1; second<ARR_SIZE;second++)
			{
				temp.push_back(first);
				temp.push_back(second);
				permutations.push_back(temp);
				temp.clear();

			}
		 }


	}
	else if (className=="OpenRule")
	{
		int col = param[0];
		int row = param[1];
		int thing = param[2];

		rows.push_back(row);
		things.push_back(thing);
		//only one option
		permutations.push_back( std::vector<int> (col));

	}

	else if (className=="UnderRule")
	{
		int row1= param[0];
		int thing1 = param[1];
		int row2 = param[2];
		int thing2 = param[3];

		rows.push_back(row1);
		rows.push_back(row2);
		things.push_back(thing1);
		things.push_back(thing2);


		for (int i=0;i<ARR_SIZE;i++)
		{
			// (i,i)
			permutations.push_back(std::vector<int>(2,i));
		}
	}

	else if (className=="BetweenRule")
	{
		int row1 = param[0];
		int thing1 = param[1];
		int row2 = param[2];
		int thing2 =param[3];
		int centerRow=param[4];
		int centerThing=param[5];

		rows.push_back(row1);
		rows.push_back(centerRow);
		rows.push_back(row2);


		things.push_back(thing1);
		things.push_back(centerThing);
		things.push_back(thing2);


		std::vector<int> temp;
		for (int middle=1;middle<ARR_SIZE-1;++middle)
		{
			temp.push_back(middle-1);
			temp.push_back(middle);
			temp.push_back(middle+1);

			permutations.push_back(temp);
			temp.clear();

			temp.push_back(middle+1);
			temp.push_back(middle);
			temp.push_back(middle-1);

			permutations.push_back(temp);
			temp.clear();
		}

	}

}

//for testing
void Constraint::print()
{
	std::cout<<"rows:";
	for (int i=0;i<rows.size();i++)
	{
		std::cout<< rows[i]<<" | ";
	}

	std::cout<<"\n"<<"things:";
	for (int i=0;i<things.size();i++)
	{
		std::cout<< things[i]<<" | ";
	}

	std::cout<<"\n"<<"possible permutations";
	for (int i=0; i<permutations.size();i++)
	   {
		std::cout<<"<";
		for (int j=0; j<permutations[i].size();j++)
		{
			std::cout<<permutations[i][j]<<",";
		}
		std::cout<<">\n";
	   }
}

//checks if a certain variable is relevant for a constraint
bool Constraint::isVarPresent(int row,int thing)
{
	for (int i=0;i<rows.size();i++)
	{
		if (rows[i]==row && things[i]==thing)
		{
			return true;
		}
	}
	return false;
}

//number of variables in this constraint
int Constraint::checkNumOfVars()
{
	return (int)this->rows.size();

}

//checks if the given solution upholds the constraint
//it isn't too late to change the function name. just wanted it to be clear
bool Constraint::checkConstraintHoldsForSol(PartialSolution* sol)
{
	bool temp;
	for (int con=0;con<permutations.size();con++)
	{
		temp = true;
		for (int var=0; var<things.size();var++ )
		{
			temp=sol->getOptionForCell(rows[var],permutations[con][var],things[var]);
			if (!temp) break;
		}
		if (temp) return true;
	}
	return false;
}

//constructor-given all the rules, a set of constraints is created
AllConstraints::AllConstraints(Rules rules)
{
	for (Rules::iterator it=rules.begin(); it != rules.end(); ++it)
	{
		all.push_back(Constraint(*it));
	}

}

//TODO think if we need to use pointers here? would it be more space and time saving
std::vector<Constraint> AllConstraints::returnReleventConstraints(int row,int thing)
{
	std::vector <Constraint> releventConstraints;
	for (int i =0;i<this->all.size();i++)
			{
				if (all[i].isVarPresent(row,thing))
				{
					releventConstraints.push_back(all[i]);
				}
			}
	return releventConstraints;
}


//loops over all constraints and checks if solArr is a good solution
bool AllConstraints::checkSolKeepsAllConstraints(PartialSolution* sol)
{
	for (int i =0;i<this->all.size();i++)
	{
		if (!this->all[i].checkConstraintHoldsForSol(sol))
		{
			return false;
		}
	}
	return true;
}



