#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
//This CPP file Header// 
#include "InputTools.h"


// text input - Overload Base // 
void getInput(std::string& input) 
{
	getline(std::cin, input); 
}

// int input - Overload 1 // 
void getInput(int& input)
{
	std::string testinput{};
	int numsct{ 0 };
	bool valid = false;

	while (valid == false)
	{
		std::cin >> testinput;

		for (size_t l = 0; l < testinput.size(); l++)
		{
			if (testinput[l] < '9' && testinput[l] > '0')
			{
			numsct++;
			}
		}
		if ((numsct) == (testinput.size()))
		{
		input = stoi(testinput);
		valid = true; 
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
		}
		else
		{
		std::cout << "Invalid Input, Try Again \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		numsct = 0; 
	}
}

//double input - Overload 2 // 
void getInput(double& input)
{
	std::string testinput{};
	int numsct{ 0 }, decimal{0};
	bool valid = false;

	while (valid == false)
	{
		std::cin >> testinput;
		size_t inputsize; 
		inputsize = testinput.size();

		for (size_t l = 0; l < testinput.size(); l++)
		{
			if (testinput[l] <= '9' && testinput[l] >= '0')
			{
			numsct++;
			}
			if (testinput[l] == '.')
			{
			decimal++;
			}
		}
		if (decimal == 1)
		{
		inputsize--; 
		}
		if ((numsct == inputsize) && (decimal < 2))
		{
		input = stod(testinput);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		valid = true;
		break;
		}
		else
		{
		std::cout << "Invalid Input, Try Again \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		numsct = 0;
		decimal = 0; 
	}
}


//input validation for passwords//
//char limit + begin with space
void getInputPass(std::string& input)
{
	std::string test{};
	bool valid = false;
	int symbolsct{ 0 };
	char symbols[8] = {'!', '@', '#', '$', '%' , '^' , '&', '*'};

	while (!(valid))
	{
		getInput(test); 

		//check for symbols// 
		for (int l = 0; l < test.size(); l++)
		{
			for (int l1 = 0; l1 < 8; l1++)
				if (test[l] == symbols[l1])
				{
				symbolsct++;
				}
		}

		if (test.size() > 25 || test.size() < 4 || test[0] == ' ' || symbolsct < 2)
		{
			std::cout << "\n\n\nInvalid Password!\n-Password must contain at least 4 Characters.\n";
			std::cout << "-Password must be under 25 Characters\n-Password may not begin with a space character\n";
			std::cout << "-Password must contain at least 2 of the following Special Charactars: !, @, #, $, %, ^, &, *\n";
			valid = false; 
		}
		else
		{
		input = test; 
		valid = true; 
		}
	}
}

//MenuBtn int Reduction to 2 digits only// 
void MenuInt(int& input)
{
		std::string testinput{};
		int numsct{ 0 };
		bool valid = false;

		while (valid == false)
		{
			std::cin >> testinput;

			for (size_t l = 0; l < testinput.size(); l++)
			{
				if (testinput[l] < '9' && testinput[l] > '0')
				{
					numsct++;
				}
			}
			if ((numsct) == (testinput.size()))
			{
				std::string a; 
				a += testinput[0];
				a += testinput[1];

				input = stoi(a);
				valid = true;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			else
			{
				std::cout << "Invalid Input, Try Again \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			numsct = 0;
		}
}


//Print Confirmation for BankAccountsClass Transactions//
void pconfirm(double amt, double fee, std::string acctype, std::string transtype)
{
	std::cout << "Please confirm\n";
	std::cout << acctype << " Account " <<transtype<< "in the amount of : $" << std::fixed << std::setprecision(2) << amt << std::endl;
	std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
	std::cout << "Enter [Y] to continue or [N] to cancel\n";
}

//Print MainMenu Menu//
void PMainMenu()
{
	std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "     FreeBank 2.5 " << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Please select from the following options: \n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "[1] - Login to your Account\n";
	std::cout << "[2] - Open a new bank account\n";
	std::cout << "[3] - To View Bank Profit\n";
	std::cout << "[4] - To Close\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

//Print AccountMenu Menu//
void PAccountMenu()
{
std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
std::cout << "Please Select from the following\n";
std::cout << "[1] - To Make a Deposit\n";
std::cout << "[2] - To Make a Withdrawal\n";
std::cout << "[3] - To Make a Transfer\n";
std::cout << "[4] - To View your Balance ($1 Fee)\n";
std::cout << "[5] - To Change your Password\n";
std::cout << "[6] - To Make a Wire\n";
std::cout << "[25] - To Logout\n";
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}


void Pborder(std::string message)
{
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << message << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}