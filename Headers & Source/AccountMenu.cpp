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
		actbtn = 0; 
		PAccountMenu(); 
		MenuInt(actbtn);

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
	return dfee; //end session, return fees to be assigned to FreeBank.
}
