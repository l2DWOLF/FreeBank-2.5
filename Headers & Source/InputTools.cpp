#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <exception>
//This CPP file Header// 
#include "InputTools.h"


// Text Input - Overload Base [0] // 
void getInput(std::string& input) 
{
	getline(std::cin, input); 
}

// Int Input - Overload [1] // 
void getInput(int& input)
{
	std::string testinput{};
	int numsct{ 0 };
	bool valid = false;

	while (valid == false)
	{
		std::cin >> testinput;
		checkCin();
		for (size_t l = 0; l < testinput.size(); l++)
		{
			if (testinput[l] < '9' && testinput[l] > '0')
				numsct++;
		}
		if ((numsct) == (testinput.size()))
		{
		input = stoi(testinput);
		valid = true; 
		break;
		}
		else
		{
		std::cout << "Invalid Input, Try Again \n";
		}
		numsct = 0; 
	}
}

// Double Input - Overload [2] // 
void getInput(double& input) throw (...)
{
	std::string testinput{};
	size_t inputsize{ 0 };
	int numsct{ 0 }, decimal{0};
	bool valid = false;

	while (valid == false)
	try{
		std::cin >> testinput;
		if (testinput.size() > 100)
		{
			throw "Char Limit 100 Exceeded! - Returning to the Previous Menu";
		}
		inputsize = testinput.size();
		//Run Tests Loop//
		for (size_t l = 0; l < testinput.size(); l++)
		{
			if (testinput[l] <= '9' && testinput[l] >= '0')
				numsct++;
			if (testinput[l] == '.')
				decimal++;
		}
		if (decimal == 1)
			inputsize--;
		//Conclusion//
		if ((numsct == inputsize) && (decimal < 2))
		{
		input = stod(testinput);
		clearCin();
		valid = true;
		break;
		}
		else
		{
		std::cout << "Invalid Input, Try Again \n";
		clearCin();
		}
		numsct = 0;
		decimal = 0; 
		inputsize = 0;
	}
	catch (const char* e)
	{
		throw e;
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
		size_t Tsize{ 0 };
		Tsize = test.size();
		//Run Tests Loop// 
		for (int l = 0; l < Tsize; l++)
		{
			//check for symbols//
			for (int l1 = 0; l1 < 8; l1++)
			{
				if (test[l] == symbols[l1])
					symbolsct++;
			}
			//check for digits// 
			if (test[l] >= '0' && test[l] <= '9')
				numsct++;
		}
		// Conclusion // 
		if ( Tsize > 25 || Tsize < 4 || test[0] == ' ' || symbolsct < 1 || numsct < 2)
		{ 
			PPErrors(Tsize, symbolsct, numsct);
			valid = false;
		}
		else
		{
			input = test;
			valid = true;
		}
		numsct = 0; symbolsct = 0;
	}
}

// input validation for passwords - Override [0] //
void getInputPass(std::string& input)
{
	std::string test{};
	bool valid = false;
	int symbolsct{ 0 }, numsct{ 0 }, upperct{ 0 };

	char symbols[8] = {'!', '@', '#', '$', '%' , '^' , '&', '*'};

	while (!(valid))
	{	
		PWRules();
		getInput(test); 
		size_t Tsize{ 0 };
		Tsize = test.size();
		//Run Tests Loop//
		for (int l = 0; l < Tsize; l++)
		{
		//Check for UpperCase//
			if (test[l] >= 'A' && test[l] <= 'Z')
				upperct++;
		//Check for Symbols// 
			for (int l1 = 0; l1 < 8; l1++)
			{
				if (test[l] == symbols[l1])
					symbolsct++;
			}
		//Check for Digits// 
			if (test[l] >= '0' && test[l] <= '9')
				numsct++;
		}
		// Conclusion //
		if (Tsize > 25 || Tsize < 4 || test[0] == ' ' || symbolsct < 2 || numsct < 2 || upperct < 1)
		{	
			PPErrors(Tsize, symbolsct, numsct, upperct, 0);
			valid = false; 
		}
		else
		{
		input = test; 
		valid = true; 
		}
		numsct = 0; symbolsct = 0; upperct = 0;
	}
}
// input validation for New Passwords - Override [1] //
void getInputPass(std::string& input, const std::string name)
{
	std::string test{};
	bool valid = false, namecheck = false; 
	int symbolsct{ 0 }, numsct{ 0 }, namect{ 0 }, upperct{ 0 };
	char symbols[8] = { '!', '@', '#', '$', '%' , '^' , '&', '*' };

	while (!(valid))
	{	
		PWRules();
		size_t Tsize{ 0 }, Nsize{0};
		getInput(test);
		Tsize = test.size();
		Nsize = name.size();
		
		//Run Tests Loop//
		for (int l = 0; l < Tsize; l++)
		{
			//Check for UpperCase//
			if (test[l] >= 'A' && test[l] <= 'Z')
				upperct++;
			//Check for Digits// 
			if (test[l] >= '0' && test[l] <= '9')
				numsct++;
			//check for symbols// 
			for (int l1 = 0; l1 < 8; l1++)
			{
				if (test[l] == symbols[l1])
					symbolsct++;
			}
			//Check for UserName//
			if (namecheck == false)
			{
				size_t loopsize{ 0 }, CharIT{ 0 }, ITSize{ 0 }, txts{ 0 };
				//Check if Pass is < || > User//
				if (Tsize >= Nsize)
				{
					txts = Nsize;
					ITSize = Nsize;
					loopsize = (Tsize - Nsize) + 2;
				}
				else if (Tsize < Nsize)
				{
					txts = Tsize;
					ITSize = Tsize;
					loopsize = Nsize - Tsize;
					loopsize++;
				}
				for (int l = 0; l < loopsize; l++)
				{	
					std::string test4pass;
					for (int t = 0; t < txts; t++)
					{
						if (Tsize >= Nsize)
							test4pass += test[CharIT];
						else if (Tsize < Nsize)
							test4pass += name[CharIT];
						CharIT++;
					}
					CharIT -= ITSize - 1;
					if (Tsize >= Nsize)
					{
						if (test4pass == name)
							namect++;
					}
					else if (Tsize < Nsize)
					{
						if (test4pass == test)
							namect++;
					}
				}
				namecheck = true; 
			}
		}
		//Conclusion//
		if (Tsize > 25 || Tsize < 4 || test[0] == ' ' || symbolsct < 2 || numsct < 2 || namect > 0 || upperct < 1)
		{
			PPErrors(Tsize, symbolsct, numsct, upperct, namect);
			valid = false;
		}
		else
		{
			input = test;
			valid = true;
		} 
	numsct = 0; symbolsct = 0; namect = 0; upperct = 0; namecheck = false; 
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
			clearCin();
			for (size_t l = 0; l < testinput.size(); l++)
			{
				if (testinput[l] < '9' && testinput[l] > '0')
				{
					numsct++;
				}
			}
			if ((numsct) == (testinput.size()) && testinput.size() <= 25)
			{
				std::string a; 
				a += testinput[0];
				a += testinput[1];
				input = stoi(a);
				valid = true;
				break;
			}
			else
			{
				std::cout << "Invalid Input, Try Again \n";
			}
			numsct = 0;
		}
}

//Print Confirmation for BankAccountsClass Transactions//
void pconfirm(double amt, double fee, std::string acctype, std::string transtype)
{
	std::cout << "\n-------------------------\n";
	std::cout << "Please Confirm: \n";
	std::cout << "-------------------------\n";
	std::cout << acctype << " Account " <<transtype<< " in the Amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
	std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
	std::cout << "Enter [Y] to Continue || Enter [N] to Cancel\n";
	std::cout << "-------------------------\n";
}
//Print MainMenu Menu//
void PMainMenu()
{
	std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "	     || FreeBank - 2.5 ||     " << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Please Select From the Following Options: \n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "[1] - Login to Your Account\n";
	std::cout << "[2] - Open a New bank Account\n";
	std::cout << "[3] - To View Bank Profit\n";
	std::cout << "[4] - To Close the Program\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
//Print AccountMenu Menu//
void PAccountMenu()
{
	std::cout << "\n==========================================\n";
	std::cout << "	    [Account Menu]\n";
	std::cout << "==========================================\n"; 
	std::cout << "Please Select From the Following Options : \n";
	std::cout << "==========================================\n";
	std::cout << "[1] - To Make a Deposit\n";
	std::cout << "[2] - To Make a Withdrawal\n";
	std::cout << "[3] - To Make a Transfer\n";
	std::cout << "[4] - To View your Balance ($1 Fee)\n";
	std::cout << "[5] - To Change your Password\n";
	std::cout << "[6] - To Make a Wire\n";
	std::cout << "[25] - To Logout and return to the Main Menu\n";
	std::cout << "==========================================\n";
}

//Print Acc. Deposit Menu//
void PDMenu()
{
	std::cout << "\n-------------------------\n";
	std::cout << "Select Deposit Type:\n";
	std::cout << "-------------------------\n";
	std::cout << "[1] - Deposit to Checking Account\n";
	std::cout << "[2] - Deposit to Savings Account\n";
	std::cout << "[3] - Return to Previous Menu\n";
	std::cout << "-------------------------\n";
}
//Print Acc. Withdrawal Menu//
void PWMenu()
{
	std::cout << "\n-------------------------\n";
	std::cout << "Select Withdrawl Type:\n";
	std::cout << "-------------------------\n";
	std::cout << "[1] - Withdrawal from Checking Account\n";
	std::cout << "[2] - Withdrawal from Savings Account\n";
	std::cout << "[3] - Return to Previous Menu\n";
	std::cout << "-------------------------\n";
}
//Print Acc. Transfer Menu//
void PTMenu()
{
	std::cout << "\n-------------------------\n";
	std::cout << "Select Tranfer type:\n";
	std::cout << "-------------------------\n";
	std::cout << "[1] - Checking to Savings\n";
	std::cout << "[2] - Savings to Checking\n";
	std::cout << "[3] - Return to Previous Menu\n";
	std::cout << "-------------------------\n";
}
// Print UserName Entry Rules // 
void UNRules()
{
	std::cout << "\n--------------------------------------\n";
	std::cout << "Username Restrictions: ";
	std::cout << "\n--------------------------------------\n";
	std::cout << "-UserName Must Contain Between 4 - 25 Characters. [1b3$].\n";
	std::cout << "-UserName Must Contain at least 2 Digits. [123#].\n";
	std::cout << "-UserName Must Contain at least 1 Special Charactar:    | !, @, #, $, %, ^, &, * | [a23!]\n";
	std::cout << "-UserName Nay NOT begin with a Space Character.[ user].\n";
	std::cout << "--------------------------------------\n";
}
// Print PassWord Entry Rules // 
void PWRules()
{
	std::cout << "\n--------------------------------------\n";
	std::cout << "Password Restrictions: ";
	std::cout << "\n--------------------------------------\n";
	std::cout << "-Password Must Contain Between 4 - 25 Characters. [ABCD] \n";
	std::cout << "-Password Must Contain at least 1 Upper Case Letter. [Dude12!@].\n";
	std::cout << "-Password Must Contain at least 2 Digits. [dude12!@].\n";
	std::cout << "-Password Must Contain at least 2 Symbol Charactars.    | !, @, #, $, %, ^, &, * |\n";
	std::cout << "-Password May NOT Containt your UserName.  [UserName: Dude123!@, Password: 123!@Dude] \n";
	std::cout << "-Password May NOT begin with a Space Character [ Dude123!@#].\n";
	std::cout << "--------------------------------------\n";
}
// Print UserName Entry Errors - Base [0] // 
void PPErrors(size_t Tsize, int symbolsct, int numsct)
{
	std::cout << "\n--------------------------------\n";
	std::cout << "Invalid Username! ";
	std::cout << "\n--------------------------------\n";
	if (Tsize > 25 || Tsize < 4)
		std::cout << "-You've Entered Less than 4 or More than 25 Charactars!" << std::endl;
	if (numsct < 2)
		std::cout << "-You've Entered Less than 2 Number Digits!" << std::endl;
	if (symbolsct < 2)
		std::cout << "-You've Entered Less than 1 Symbols!" << std::endl;
	std::cout << "\n--------------------------------\n";
}
// Print Password Entry Errors - Override [1] // 
void PPErrors(size_t Tsize, int symbolsct, int numsct, int upperct, int namect)
{
	std::cout << "\n--------------------------------\n";
	std::cout << "Invalid Password! ";
	std::cout << "\n--------------------------------\n";
	if (Tsize > 25 || Tsize < 4)
		std::cout << "-You've Entered Less than 4 or More than 25 Charactars!" << std::endl;
	if (upperct < 1)
		std::cout << "-You've Entered Less than 1 Upper Case Letter!" << std::endl;
	if (numsct < 2)
		std::cout << "-You've Entered Less than 2 Number Digits!" << std::endl;
	if (symbolsct < 2)
		std::cout << "-You've Entered Less than 2 Symbols!" << std::endl;
	if (namect > 0)
		std::cout << "-Your Password Containts your Username!" << std::endl;
	std::cout << "\n--------------------------------\n";
}
// Print Name Exists//
void nameExists(std::string& nameTest)
{
	std::cout << "\n\n--------------------------------------------------\n";
	std::cout << "An Account with the Name: " << nameTest << " Already exists!\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "\n-Please Enter a Different Name!\n\nName Suggestions: \n";
	std::cout << "-------------------------\n";
	std::cout << nameTest << "123\n" << nameTest << "2023\n" << nameTest << "LastName\n";
	std::cout << "-------------------------\n";
	std::cout << "\n--------------------------------------------------\n";
}
// Print Border Lines // 
void Pborder(std::string message)
{
	std::cout << "\n==========================================\n";
	std::cout << message << std::endl;
	std::cout << "==========================================\n";
}

// Check CIN // 
void checkCin()
{
	if (!std::cin)
		clearCin();
}
void clearCin()
{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Loop PW Size - Test for new passwords != userName // 
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