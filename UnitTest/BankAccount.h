#include "string"
#include <exception>

struct BankAccount
{
	int balance;
	char name[51];

	BankAccount(int _balance = 0)
		:balance(_balance)
	{
		strcpy_s(name, "");

	}

	BankAccount(char* _name, int _balance = 0)
		:balance(_balance)
	{
		strcpy_s(name, _name);
	}

	void deposit(int ammount)
	{
		if (ammount > 0)
			balance += ammount;
		else
			throw std::out_of_range("Negative ammount.");
	}

	void withdraw(int ammount)
	{
		if(ammount > 0)
			balance -= ammount;
		else
			throw std::out_of_range("Negative ammount.");
	}
};
