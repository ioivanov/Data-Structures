#include "stdafx.h"
#include <iostream>
#include "CppUnitTest.h"
#include "../BancAccount/BancAccount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_MODULE_INITIALIZE(ModuleInitialize)
{

	Logger::WriteMessage("Entered ModuleInitialize");

}

TEST_MODULE_CLEANUP(ModuleCleanup)
{

	Logger::WriteMessage("Entering ModuleCleanup");

}

namespace BancAccountUT
{		

	TEST_CLASS(TestConstructors)
	{
	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("Entering ClassInitialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("Entering ClassCleanup");
		}

		TestConstructors()
		{
			Logger::WriteMessage("Entering TestConstructors::TestConstructors()");
		}

		~TestConstructors()
		{
			Logger::WriteMessage("Entering TestConstructors::~TestConstructors()");
		}

		TEST_METHOD(CreateBankAccountArray)
		{
			BankAccount* p = new BankAccount[1000000];

			delete[] p;
		}

		TEST_METHOD(TestDefault)
		{
			BankAccount b;
		}

		TEST_METHOD(TestWithParameters)
		{
			BankAccount b("Ivaylo", 100);
		}
	};

	TEST_CLASS(TestOperations)
	{
	public:
		
		TEST_METHOD(TestDeposit)
		{
			BankAccount acc(100);
			acc.deposit(100);
			Assert::AreEqual(acc.balance, 200);
		}
		TEST_METHOD(TestWithdrow)
		{
			BankAccount acc(100);
			acc.withdraw(50);
			Assert::AreEqual(acc.balance, 50);
		}
		TEST_METHOD(TestIsEmpty)
		{
			BankAccount acc;
			Assert::IsTrue(acc.empty());
		}
		TEST_METHOD(TestIsNotEmpty)
		{
			BankAccount acc(100);
			Assert::IsFalse(acc.empty());
		}
	};

	TEST_CLASS(TestExtremeCases)
	{
	public:

		TEST_METHOD(BigWithdrow)
		{
			BankAccount b("Ivaylo", 100);
			b.withdraw(200);
			Assert::AreEqual(b.balance, 0);
		}

		TEST_METHOD(DepositNegative)
		{
			BankAccount b;
			try
			{
				b.deposit(-50);
				Assert::Fail(L"Exception not thrown.");
			}
			catch (std::out_of_range &exc)
			{
				std::cerr << exc.what() << std::endl;
			}
			catch (...)
			{
				Assert::Fail(L"Wrong exception type thrown");
			}
		}

		TEST_METHOD(WithdrowNegative)
		{
			BankAccount b;
			Assert::ExpectException<std::out_of_range>(
				[&b]()
				{
					b.withdraw(-50);
				}
			);
		}
	};
}
