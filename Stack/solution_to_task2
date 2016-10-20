#include "stdafx.h"
#include <fstream>
#include "stack.hpp"

void readNumberFromFile(std::ifstream &fi, Stack<int> &number)
{
	char digit;
	while (fi>>digit)
	{
		number.push(digit - '0');
	}
}

void sum(char* firstNumberFileName, char* secondNumberFileName, char* resultFileName)
{
	std::ifstream fiFirst(firstNumberFileName);
	std::ifstream fiSecond(secondNumberFileName);

	std::ofstream fo(resultFileName, std::ios::trunc);

	Stack<int> larg;
	readNumberFromFile(fiFirst, larg);
	fiFirst.close();

	Stack<int> rarg;
	readNumberFromFile(fiSecond, rarg);
	fiSecond.close();

	Stack<int> result;

	int remainder = 0;
	while (!larg.empty() && !rarg.empty())
	{
		remainder += larg.top() + rarg.top();
		result.push(remainder % 10);
		remainder /= 10;

		larg.pop();
		rarg.pop();
	}
	if (larg.empty())
	{
		while (!rarg.empty())
		{
			remainder += rarg.top();
			result.push(remainder % 10);
			remainder /= 10;

			rarg.pop();
		}
	}
	else if (rarg.empty())
	{
		while (!larg.empty())
		{
			remainder += larg.top();
			result.push(remainder % 10);
			remainder /= 10;

			larg.pop();
		}
	}

	if (remainder != 0)
		result.push(remainder);

	while (!result.empty())
	{
		fo << result.top();
		result.pop();
	}
		
	fo.close();
}

int main()
{
	sum("larg.txt", "rarg.txt", "results.txt");

	return 0;
}
