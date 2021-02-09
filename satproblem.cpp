#include "satproblem.h"

void satproblem::processline (std::string line)
{
	if (line != "")
	{
		if (line[0] != 'c')			// check for comments
		{
			if (line[0] == 'p')		// format line
			{
				std::stringstream cline(line);
				std::string buf, buf2;
				cline >> buf;	// p
				cline >> buf;
				if (buf == "cnf")			// check format
				{
					this->issolved = false;
					cline >> this->numvars;
					cline >> this->numclause;
				}
			}
			else							// clause
			{
				std::stringstream cline(line);
				int buf;
				clause cclause;
				while (cline >> buf)
				{
					if (buf == 0)
						break;
					cclause.push_back(buf);
				}
				if (cclause.size() > 0)
				{
					this->issolved = false;
					this->clauses.push_back(cclause);
				}
			}
		}
		else
		{
			std::stringstream cline(line);
			std::string buf;
			cline >> buf;		// discard c
			cline >> buf;
			if (buf == "varnames")		// custom comment
			{
				while (cline >> buf)
				{
					this->varnames.push_back(buf);
				}
			}
		}
	}
}

bool satproblem::issat()
{
	if (!issolved)
		this->solve();
	return (solutions.size() > 0);
}

std::string satproblem::resolve_varname (int varnum)
{
	std::string output;
	if (varnum < this->varnames.size())
		output = this->varnames[varnum];
	else
	{
		std::stringstream buf;
		buf << "x" << varnum + 1;
		output = buf.str();
	}
	return output;
}

std::string satproblem::listclauses()
{
	std::stringstream cstr;
	cstr << "variables: ";
	for (int i = 0; i < this->numvars; i++)
		cstr << this->resolve_varname(i) << " ";
	cstr << std::endl << "clauses:" << std::endl;
	for (int i = 0; i < this->clauses.size(); i++)
	{
		for (int j = 0; j < this->clauses[i].size(); j++)
			cstr << this->clauses[i][j] << " ";
		cstr << std::endl;
	}
	return cstr.str();
}

std::string satproblem::listsolutions()
{
	if (!issolved)
		this->solve();
	std::stringstream cstr;
	for (int i = 0; i < this->solutions.size(); i++)
	{
		for (int j = 0; j < this->solutions[i].size(); j++)
		{
			cstr << this->resolve_varname(j) << "=" << this->solutions[i][j] << ";";
		}
		cstr << std::endl;
	}
	return cstr.str();
}

std::string satproblem::printexpression()
{
	std::stringstream buf;
	for (int i = 0; i < this->numclause; i++)
	{
		int clause_size = this->clauses[i].size();
		for (int j = 0; j < clause_size; j++)
		{
			buf << this->resolve_varname(abs(this->clauses[i][j]) - 1);
			if (this->clauses[i][j] < 0)
				buf << "'";
			if (j < clause_size - 1)
				buf << ".";
		}
		if (i < this->numclause - 1)
			buf << " + ";
	}
	return buf.str();
}

std::string satproblem::solutioncsv()
{
	std::stringstream buf;
	for (int i = 0; i < this->numvars; i++)
		buf << "	" << this->resolve_varname(i);
	buf << std::endl;
	if (!this->issolved)
		this->solve();
	for (int i = 0; i < this->solutions.size(); i++)
	{
		int solsize = this->solutions[i].size();
		long long int solnum = 0;
		for (int j = 0; j < solsize; j++)
			solnum = (solnum << 1) | this->solutions[i][j];
		buf << solnum;
		for (int j = 0; j < solsize; j++)
		{
			buf << "	" << this->solutions[i][j];
		}
		buf << std::endl;
	}
	return buf.str();
}

bool satproblem::evaluate(solution sol)
{
	bool satisfied = false;
	for (int i = 0; i < this->clauses.size(); i++)
	{
		clause cclause = this->clauses[i];
		bool csat = true;
		for (int j = 0; j < cclause.size(); j++)
		{
			int index = abs(cclause[j]) - 1;
			bool value = (cclause[j] > 0);
			if (sol[index] != value)
			{
				csat = false;
				break;
			}
		}
		if (csat)
		{
			satisfied = true;
			break;
		}
	}
	return satisfied;
}

void satproblem::solve()
{
	solution csol;
	long long int binary_code = 0, bincopy;
	for (int i = 0; i < this->numvars; i++)
		csol.push_back(0);
	
	this->solutions.clear();
	for (binary_code = 0; binary_code < pow(2, this->numvars); binary_code++)
	{
		bincopy = binary_code;
		for (int i = 0; i < this->numvars; i++)
		{
			csol[i] = bincopy & 1;
			bincopy >>= 1;
		}
		if (this->evaluate(csol))
		{
			this->solutions.push_back(csol);
		}
	}
	this->issolved = true;
}

