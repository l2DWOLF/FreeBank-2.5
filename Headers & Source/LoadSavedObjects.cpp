#include <fstream>
#include <string>
#include <vector>
#include "BankClass.h"
#include "BankAccountsClass.h"
//This CPP file Header// 
#include "LoadSavedObjects.h"


void saveTotalAccounts(int& totalAccounts)
{
	if (totalAccounts > 0)
	{
		std::ofstream file;
		file.open("./ObjectsData/totalAccounts.txt");
		file << totalAccounts;
		file.close();
	}
}

void LoadExistingAccounts(int& totalAccounts, std::vector<bankAccounts>& BAVec)
{
	{
		std::string loadTA;
		std::ifstream read("./ObjectsData/totalAccounts.txt");
		getline(read, loadTA);

		bool cstring = loadTA.empty();
		if (!cstring)
		{
			totalAccounts = std::stoi(loadTA);
		}
	}

	std::string loadName;
	std::string maname, mapass, machecking, masavings, mainvestment, macredit;
	int TA = totalAccounts;

	std::ifstream read("./ObjectsData/ObjectsCollection.txt", std::ios::app);
	while (TA--)
	{
		getline(read, loadName);

		std::ifstream read("./ObjectsData/" + loadName + " login" + ".txt");
		getline(read, maname);
		getline(read, mapass);
		getline(read, machecking);
		getline(read, masavings);
		getline(read, mainvestment);
		getline(read, macredit);

		BAVec.emplace_back(maname, mapass, machecking, masavings, mainvestment, macredit);
	}
}