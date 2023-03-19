#include <iostream>
#include <string>
//This CPP file Header// 
#include "InputTools.h"

//text input // Overload Base // 
void getInput(std::string& input) 
{
	getline(std::cin, input); 
}

//int input // Overload 1 // 
void getInput(int& input)
{
	int test{};
	bool valid = false; 

	while (!(valid))
	{
		if (std::cin >> test)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			input = test;
			valid = true;
		
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid Entry\n";
			valid = true;
		}
	} 
}

//int for menus// Overload 2 //
void getInput(int& input, bool& rslt)
{
	int test{};
	bool valid = false;

	while (!(valid))
	{
		if (std::cin >> test)
		{
			rslt = true; 
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			input = test;
			valid = true;

		}
		else
		{
			rslt = false; 
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid Entry\n";
			valid = true; 
		}
	}
}

//double input// Overload 3 // 
void getInput(double& input)
{
	double test{};
	bool valid = false;

	while (!(valid))
	{
		if (std::cin >> test)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			input = test;
			valid = true;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid Entry\n";
			valid = true;
		}
	}
}

//double input for menus// Overload 4 //
void getInput(double& input, bool& rslt)
{
	double test{};
	bool valid = false;

	while (!(valid))
	{
		if (std::cin >> test)
		{
			rslt = true;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			input = test;
			valid = true;

		}
		else
		{
			rslt = false;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid Entry\n";
			valid = true;
		}
	}
}


//input validation for passwords//
void getInputPass(std::string& input)
{
	std::string test{};
	bool valid = false;

	while (!(valid))
	{
		getInput(test); 

		if (test.size() > 25 || test.size() < 4)
		{
			std::cout << "Invalid Password!\n -Password must contain at least 4 Characters.\n -Password must be under 25 Characters\n";
			valid = false; 
		}
		else
		{
			input = test; 
			valid = true; 
		}
	}
}