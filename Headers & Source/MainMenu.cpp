#include <iostream>
#include <vector>
#include "BankClass.h"
#include "BankAccountsClass.h"
#include "LoadSavedObjects.h"
#include "AccountMenu.h"
//This CPP file Header// 
#include "MainMenu.h"



void Launch(int& totalAccounts, double& transactionFees, std::vector<bankAccounts>& BAVec, Bank& FreeBank)
{
	std::string menubtn{ "0" };

	while (menubtn != "4")
	{
		std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "  Welcome to FreeBank! " << "\n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Please select from the following options: " << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "[1] - Login to your Account" << std::endl;
		std::cout << "[2] - Open a new bank account" << std::endl;
		std::cout << "[3] - To View Bank Profit" << std::endl;
		std::cout << "[4] - To Close" << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cin >> menubtn;

		//Login//
		if (menubtn == "1")
		{
			std::string nameinput;  //name from user
			std::string namecollect; // name from objects
			int actIndex{ 0 };  // index to correct obj name if found

			std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cout << "Enter Username" << std::endl;
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cin >> nameinput;

			for (int l = 0; l < totalAccounts; l++)
			{
				namecollect = BAVec[l].namecheck();				//get name from object to test against input name
				if (nameinput == namecollect)					//test if input name == object name
				{
					actIndex = l;								//assign index to found account
					break;
				}
			}

			if (nameinput == namecollect)
			{
				bool verify{ 0 };
				verify = BAVec[actIndex].passcheck();		//run password check via object method

				if (verify == true)
				{
					std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
					std::cout << "Login Successful..! Welcome " << namecollect << "! " << std::endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
					transactionFees = accountmenu(BAVec[actIndex], BAVec);		//run account menu with existing object logged in
					FreeBank.Fee(transactionFees);								//move occured fees to FreeBank Bank obj

				}
				else
				{
					std::cout << "Wrong Password.." << std::endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
				}
			}
			else
			{
				std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
				std::cout << "Account doesn't exist.." << std::endl;
				std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			}
			menubtn = "0";
		}

		//Create New Account
		else if (menubtn == "2")
		{
			std::string nameTest;
			bool nameisfree = false;

			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cout << "Please Enter Account Name" << std::endl;
			std::cin >> nameTest;
			nameisfree = FreeBank.namecheckAll(nameTest);

			if (nameisfree == true)
			{
				BAVec.emplace_back(nameTest);		//Add new bank account object to accounts Vector
				++totalAccounts;					//Update count of Accounts total.
				saveTotalAccounts(totalAccounts);
				menubtn = "0";
			}
			else
			{
				std::cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
				std::cout << "An Account with the name: " << nameTest << " Already exists, please enter a different name" << std::endl;
				std::cout << "\nName Suggestions: \n" << nameTest << "123\n" << nameTest << "2023\n" << nameTest << "LastName" << std::endl;
				menubtn = "0";
			}
		}

		//Check profit of FreeBank obj
		else if (menubtn == "3")
		{
			FreeBank.profit();
			menubtn = "0";
		}

		//Exit
		else if (menubtn == "4")
		{
			std::cout << "Thank you..!! Good Bye..!! " << std::endl;
		}
	}
}