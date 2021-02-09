#ifndef __SATSOLVER__

#define __SATSVOLER__

#include <string>
#include <sstream>
#include <vector>
#include <cmath>

typedef std::vector<int> clause;
typedef std::vector<bool> solution;

class satproblem {
	public:
		void processline (std::string line);
		std::string listclauses();
		std::string listsolutions();
		void solve();
		bool issat();
		bool evaluate(solution sol);
		std::string printexpression();
		std::string solutioncsv();
	private:
		int numvars, numclause;
		std::vector<clause> clauses;
		std::vector<solution> solutions;
		std::vector<std::string> varnames;
		bool issolved;
		std::string resolve_varname (int varnum);
};

#endif

