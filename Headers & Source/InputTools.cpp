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
				numsct++;
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

// double input - Overload 2 // 
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
				numsct++;
			if (testinput[l] == '.')
				decimal++;
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


// UserName Validation // 
void getInputUserName(std::string& input)
{
	std::string test{};
	bool valid = false;
	int symbolsct{ 0 }, numsct{ 0 };
	char symbols[8] = { '!', '@', '#', '$', '%' , '^' , '&', '*' };

	while (!(valid))
	{
		UNRules();
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
		//check for digits// 
		for (int l = 0; l < test.size(); l++)
		{
			if (test[l] >= '0' && test[l] <= '9')
			{
				numsct++;
			}
		}
		// Conclusion // 
		if (test.size() > 25 || test.size() < 4 || test[0] == ' ' || symbolsct < 1 || numsct < 2)
		{
			std::cout << "Invalid Input! \n"; 
			valid = false;
		}
		else
		{
			input = test;
			valid = true;
		}
		numsct = 0;
		symbolsct = 0;
	}
}

// input validation for passwords - Override [0] //
void getInputPass(std::string& input)
{
	std::string test{};
	bool valid = false;
	int symbolsct{ 0 }, numsct{ 0 };
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
		//check for digits// 
		for (int l = 0; l < test.size(); l++)
		{
			if (test[l] >= '0' && test[l] <= '9')
			{
				numsct++;
			}
		}
		// Conclusion //
		if (test.size() > 25 || test.size() < 4 || test[0] == ' ' || symbolsct < 2 || numsct < 2)
		{
			valid = false; 
		}
		else
		{
		input = test; 
		valid = true; 
		}
		numsct = 0; 
		symbolsct = 0; 
	}
}
// input validation for New Passwords - Override [1] //
void getInputPass(std::string& input, const std::string name)
{
	std::string test{};
	bool valid = false;
	int symbolsct{ 0 }, numsct{ 0 }, namect{ 0 };
	char symbols[8] = { '!', '@', '#', '$', '%' , '^' , '&', '*' };

	while (!(valid))
	{	
		PWRules();
		size_t Tsize{ 0 };
		getInput(test);
		Tsize = test.size();

		//check for symbols// 
		for (int l = 0; l < Tsize; l++)
		{
			for (int l1 = 0; l1 < 8; l1++)
				if (test[l] == symbols[l1])
				{
					symbolsct++;
				}
		}
		//check for digits// 
		for (int l = 0; l < Tsize; l++)
		{
			if (test[l] >= '0' && test[l] <= '9')
			{
				numsct++;
			}
		}
		//check for UserName//
		for (int l7 = 0; l7 < 1; l7++)
		{
			int l = 0, l1 = 1, l2 = 2, l3 = 3, i = 0, i1 = 1, i2 = 2, i3 = 3;
			size_t loopsize{ 0 };
			IFSIze(loopsize, Tsize); 

			for (int ll = 0; ll <= loopsize; ll++)
			{
				std::string test4pass;
				test4pass += test[l]; test4pass += test[l1]; test4pass += test[l2]; test4pass += test[l3];
				std::string test4name;
				test4name += name[i]; test4name += name[i1]; test4name += name[i2]; test4name += name[i3];
				//std::cout << test[l] << test[l1] << test[l2] << test[l3] << " ==? " << name[i] << name[i1] << name[i2] << name[i3] << "\n";
				if (test4pass == test4name)
				{
					namect++;
				}
				l++; l1++; l2++; l3++;
				//	i++; i1++; i2++; i3++; --> Enum to make the password test items of dynamic size to match against test4pass // 
			}
		}
		//Conclusion//
		if (Tsize > 25 || Tsize < 4 || test[0] == ' ' || symbolsct < 2 || numsct < 2 || namect > 0)
		{
			std::cout << "Invalid Password!\n"; 
			valid = false;
			numsct = 0; symbolsct = 0; namect = 0;
		}
		else
		{
			input = test;
			valid = true;
		}
	numsct = 0;
	symbolsct = 0;
	namect = 0;
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
	std::cout << "     FreeBank - 2.5 " << "\n";
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
// Print UserName Entry Rules // 
void UNRules()
{
	std::cout << "\n-UserName must contain at least 4 Characters. [1b3$].\n";
	std::cout << "-UserName must be under 25 Characters\n-UserName may not begin with a space character.[ user].\n";
	std::cout << "-UserName must contain at least 2 digits. [123#].\n";
	std::cout << "-UserName must contain at least 1 of the following Special Charactars: !, @, #, $, %, ^, &, * | [a23!]\n";
}
// Print PassWord Entry Rules // 
void PWRules()
{
	std::cout << "\n-Password must contain between 4 - 25 Characters. [ABCD] \n";
	std::cout << "-Password must be under 25 Characters\n-Password may not begin with a space character [ Dude123!@#].\n";
	std::cout << "-Password must contain at least 1 of the following Special Charactars: !, @, #, $, %, ^, &, *\n";
	std::cout << "-Password must contain at least 2 digits [Dude12!@].\n";
	std::cout << "-Password cannot contain the first 4 characters of your UserName [UserName: Dude123!@#, Password: anotherDude834#@] \n";
}
// Print Border Lines // 
void Pborder(std::string message)
{
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << message << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
// Loop PW Size // 
void IFSIze(size_t& loopsize, const size_t& Tsize)
{
	loopsize = (Tsize / 2);
	if (Tsize >= 9)
		loopsize++;
	if (Tsize >= 11)
		loopsize++;
	if (Tsize >= 13)
		loopsize++;
	if (Tsize >= 15)
		loopsize++;
	if (Tsize >= 17)
		loopsize++;
	if (Tsize >= 19)
		loopsize++;
	if (Tsize >= 21)
		loopsize++;
	if (Tsize >= 23)
		loopsize++;
	if (Tsize >= 25)
		loopsize++;
}