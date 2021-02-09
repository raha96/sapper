#ifndef __SAPPER_H__

#define __SAPPER_H__

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime>

typedef std::vector<int> clause;
typedef std::vector<bool> solution;

class sapper {
	public:
		void processline (std::string line);
		std::string listclauses();
		std::string listsolutions();
		void solve();
		bool issat();
		bool evaluate(solution sol);
		std::string printexpression();
		std::string solutioncsv();
		double getruntime();
	private:
		int numvars, numclause;
		std::vector<clause> clauses;
		std::vector<solution> solutions;
		std::vector<std::string> varnames;
		bool issolved;
		double runtime;
		std::string resolve_varname (int varnum);
};

#endif

