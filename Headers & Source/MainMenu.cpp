#include <iostream>
#include <vector>
#include "BankClass.h"
#include "BankAccountsClass.h"
#include "LoadSavedObjects.h"
#include "AccountMenu.h"
#include "InputTools.h"
//This CPP file Header// 
#include "MainMenu.h"


void Launch(int& totalAccounts, double& transactionFees, std::vector<bankAccounts>& BAVec, Bank& FreeBank)
{
	int menubtn{0};

	while (menubtn != 25)
	{
		PMainMenu(); 
		MenuInt(menubtn);

		//1. Login//
		if (menubtn == 1)
		{
		std::string nameinput, namecollect;  //name from user, name from objects//
		int actIndex{ 0 };  // index to correct obj name if found

		Pborder("Enter Username");
		getInputUserName(nameinput);

		int TA = BAVec.size(); 
		while (TA--)
		{
			namecollect = BAVec[TA].namecheck();				//get name from object to test against input name
			if (nameinput == namecollect)					//test if input name == object name
			{
				actIndex = TA;								//assign index to found account
				break;
			}
		}
		if (nameinput == namecollect)
		{
		bool verify{ 0 };
		verify = BAVec[actIndex].passcheck();		//run password check via object method

			if (verify == true)
			{
				std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				std::cout << "Login Successful..! Welcome " << namecollect << "! \n";
				std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				transactionFees = accountmenu(BAVec[actIndex], BAVec);		//run account menu with existing object logged in
				FreeBank.Fee(transactionFees);								//move occured fees to FreeBank Bank obj
			}
			else
			{
				Pborder("Wrong Password...");
			}
		}
		else
		{
			Pborder("Account doesn't exist..!");	
		}
		menubtn = 0;
		}
		//2. Create New Account//
		else if (menubtn == 2)
		{
		std::string nameTest;
		bool nameisfree = false;

		Pborder("Please Enter Account Name ");
		getInputUserName(nameTest);

		nameisfree = FreeBank.namecheckAll(nameTest);
			if (nameisfree == true)
			{
				BAVec.emplace_back(nameTest);		//Add new bank account object to accounts Vector
				++totalAccounts;					//Update count of Accounts total.
				saveTotalAccounts(totalAccounts);
				menubtn = 0;
			}
			else
			{
				std::cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				std::cout << "An Account with the name: " << nameTest << " Already exists, please enter a different name\n";
				std::cout << "\nName Suggestions: \n" << nameTest << "123\n" << nameTest << "2023\n" << nameTest << "LastName\n";
				menubtn = 0;
			}
		}
		//3. Check profit of FreeBank//
		else if (menubtn == 3)
		{
			FreeBank.profit();
			menubtn = 0;
		}
		//4. Exit//
		else if (menubtn == 4)
		{
			std::cout << "Thank you for visiting FreeBank ~ Good Bye..!!\n";
			menubtn = 25; 
		}
	}
}