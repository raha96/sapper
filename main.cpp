#include <fstream>
#include <iostream>
#include "sapper.h"

using namespace std;

sapper cprob;

int main (int argc, char* argv[])
{
	fstream fin, fout;
	if (argc > 1)
		fin.open(argv[1], fstream::in);
	else
		fin.open("input.txt", fstream::in);
	
	if (argc > 2)
		fout.open(argv[2], fstream::out);
	else
		fout.open("solutions.csv", fstream::out);

	string buf;
	while (!fin.eof())
	{
		getline(fin, buf);
		cprob.processline(buf);
	}
	
	cout << cprob.listclauses();

	cout << cprob.printexpression() << endl;

	fout << cprob.solutioncsv() << endl;

	fout.close();

	fin.close();

	cout << "Trivial algorithm ran in " << cprob.getruntime() << " seconds." << endl;
	return 0;
}
