#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>
#include <vector>
#include "BankClass.h"
#include "BankAccountsClass.h"
#include "LoadSavedObjects.h"
#include "AccountMenu.h"
#include "MainMenu.h"



int main()
{
	//Create ObjectsData Directory// 
	int hmm = _mkdir("./ObjectsData");

	//Essential Variables 
	Bank FreeBank;
	int totalAccounts = 0;
	double transactionFees{};
	std::vector<bankAccounts> BAVec;

	//Load & instantiate Existings Objects(accounts) from Saved File//
	LoadExistingAccounts(totalAccounts, BAVec); 
	
	//Launch Program - MainMenu//
	Launch(totalAccounts, transactionFees, BAVec, FreeBank);

	return 0;
}