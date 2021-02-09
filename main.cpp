#include <fstream>
#include <iostream>
#include "satproblem.h"

using namespace std;

satproblem cprob;

int main()
{
	fstream fin("input.txt", fstream::in);
	string buf;
	while (!fin.eof())
	{
		getline(fin, buf);
		cprob.processline(buf);
	}
	
	cout << cprob.listclauses();

	cout << cprob.printexpression() << endl;

	fstream fout("solutions.csv", fstream::out);

	fout << cprob.solutioncsv() << endl;

	fout.close();

	fin.close();
	return 0;
}
