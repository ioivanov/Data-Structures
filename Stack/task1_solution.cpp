#include <iostream>
#include "stack.hpp"

int main()
{
	Stack<int> a;
	const char* string = "(a+(b-c)*((d+e)/f)) ";
	int i = 0;
	while (string[i])
	{
		if (string[i] == '(' && !a.full())
		{	
			a.push(i);
		}

		else if (string[i] == ')')
		{
			if (a.empty())
			{
				std::cout << "Closing brackets are more than opening ones";
				return 0;
			}
			std::cout << "Brackets on index: " << a.pop() << "  and " << i << " match.\n";			
		}
		i++;
	}
	if (a.empty())
		std::cout << "The expression is correct\n";
	else
		std::cout << "More opening brackets than closing ones\n";

	return 0;
}
