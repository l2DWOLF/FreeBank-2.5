#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
//This CPP file Header// 
#include "BankClass.h"



	void Bank::Fee(double amount)
	{
		income += amount;
	}

	void Bank::profit()
	{
		std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Bank's Profits: $" << std::fixed << std::setprecision(2) << income << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}

	bool Bank::namecheckAll(std::string nameTest)
	{
		std::string ObjNames;
		std::ifstream read("./ObjectsData/" + nameTest + " login" + ".txt");
		getline(read, ObjNames);

		if (nameTest == ObjNames)
			return false;
		else
			return true;
	}

