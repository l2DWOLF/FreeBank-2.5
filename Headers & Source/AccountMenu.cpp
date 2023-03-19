#include <iostream>
#include <vector>
#include "BankClass.h"
#include "BankAccountsClass.h"
#include "InputTools.h"
//This CPP file Header// 
#include "AccountMenu.h"



double accountmenu(bankAccounts& act, std::vector<bankAccounts>& BAVec)
{
	int actbtn{ 0 };

	while (actbtn != 25)
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
		getInput(actbtn);

		if (actbtn == 1)
		{
			act.deposit();
			actbtn = 0;
		}
		else if (actbtn == 2)
		{
			act.withdrawal();
			actbtn = 0;
		}
		else if (actbtn == 3)
		{
			act.transfer();
			actbtn = 0;

		}
		else if (actbtn == 4)
		{
			act.info();
			actbtn = 0;
		}
		else if (actbtn == 5)
		{
			act.changePass();
			actbtn = 0;
		}
		else if (actbtn == 6)
		{
			act.wire(BAVec);
			actbtn = 0;
		}
		else if (actbtn == 25)
		{
			std::cout << "Good Bye " << act.namecheck() << "! :)\n";
		}
	}

	double dfee = act.movefees(); //return total fees from transaction to main
	act.clearfees(); //clear occured fees from current session
	return dfee; //end session, return fees to be assigned to FreeBank
}
