#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "BankClass.h"
#include "InputTools.h"
//This CPP file Header// 
#include "BankAccountsClass.h"




// constructor //
bankAccounts::bankAccounts(std::string newName)
{
	name = newName;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Hello " << name << "! \nPlease enter a new password\n";
	getInputPass(password);
	std::cout << "Your password is: " << password << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	//Create Object file with name + pass//
	SaveData();

	//Add name to ObjectsCollection file for loading existing accounts
	std::fstream Cfile;
	Cfile.open("./ObjectsData/ObjectsCollection.txt", std::ios::app);
	Cfile << name << std::endl;
	Cfile.close();
}

//copy constructor for loading objects from objectsCollection file //
bankAccounts::bankAccounts(std::string& maname, std::string& mapass, std::string& machecking,
	std::string& masavings, std::string& mainvestment, std::string& macredit)
{
	double conchecking = std::stod(machecking);
	double consavings = std::stod(masavings);
	double coninvestment = std::stod(mainvestment);
	double concredit = std::stod(macredit);

	name = maname;
	password = mapass;
	checking = conchecking;
	savings = consavings;
	investment = coninvestment;
	credit = concredit;
}

std::string bankAccounts::namecheck()
{
	return name;
}

bool bankAccounts::passcheck()
{
	std::string tempass;
	bool rslt{ 0 };
	Pborder("enter password: ");
	getInputPass(tempass);

	std::string filepass;
	std::ifstream read("./ObjectsData/" + name + " login" + ".txt");
	getline(read, filepass);
	getline(read, filepass);

	if (tempass == filepass)
		rslt = true;
	else
		rslt = false;

	return rslt;
}

void bankAccounts::changePass()
{
	std::string tempass;

	Pborder("Enter Current Password:");
	getInputPass(tempass);

	std::string filepass;
	std::ifstream read("./ObjectsData/" + name + " login" + ".txt");
	getline(read, filepass);
	getline(read, filepass);

	if (tempass == filepass)
	{
		std::cout << "Enter New Password: \n";
		getInputPass(password);
		SaveData();
	}
	else
		std::cout << "Wrong Password..\n";
}


double bankAccounts::movefees()
{
	return fees;
}

void bankAccounts::clearfees()
{
	fees = 0;
}

void bankAccounts::info()
{
	fees += 1;
	checking -= 1;
	std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "  Bank Account: " << name << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Checking Account: $" << std::fixed << std::setprecision(2) << checking << std::endl;
	std::cout << "Savings Account: $" << std::fixed << std::setprecision(2) << savings << std::endl;
	std::cout << "Investment Account: $" << std::fixed << std::setprecision(2) << investment << std::endl;
	std::cout << "Credit Card: $" << std::fixed << std::setprecision(2) << credit << std::endl;
	std::cout << "Fees Total: $" << std::fixed << std::setprecision(2) << fees << std::endl;
	std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
SaveData();
}

// Deposit //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 
void bankAccounts::deposit() 
{
	std::string transtype = "Deposit"; 
	int btn{ 0 };
	while (btn != 25)
{		
		std::cout << "[1] - Deposit to Checking Account\n";
		std::cout << "[2] - Deposit to Savings Account\n";
		std::cout << "[3] - Return to Previous Menu\n";
		MenuInt(btn);

		//1. Deposit to Checking//
		if (btn == 1)
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::string acctype = "Checking";

			Pborder("Enter Amount to Deposit to your Checking Account");
			getInput(amt);
			fee = amt * cdfee;
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);

			if (cnf[0] == 'Y' || cnf[0] == 'y')
			{
				amt -= fee;
				fees += fee;
				checking += amt;
				std::cout << "Deposit Completed Successfully!\n"; 
			}
			else
			{
				std::cout << "Deposit Cancelled\n";
				btn = 1;
			}		
		}
		//2. Deposit to Savings//
		else if (btn == 2)
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::string acctype = "Savings";

			Pborder("Enter Amount to Deposit to your Savings Account");
			getInput(amt);

			fee = amt * sdfee;
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);

			if (cnf[0] == 'Y' || cnf[0] == 'y')
			{
			amt -= fee;
			fees += fee;
			savings += amt;
			std::cout << "Deposit Completed Successfully!\n";
			}
			else
			{
			std::cout << "Deposit Cancelled\n";
			btn = 1;
			}
		}
		//3. Return to Previous Menu//
		else if (btn == 3)
		{
			btn = 25;
		}
	}
SaveData();
}	
// End Deposit //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

// Withdrawal // 
void bankAccounts::withdrawal() 
{
	int btn{ 0 };
	std::string transtype = "Withdrawal";
	while (btn != 25)
	{
		std::cout << "[1] - Withdrawal from Checking Account\n";
		std::cout << "[2] - withdrawal from Savings Account\n";
		std::cout << "[3] - Return to Previous Menu\n";
		MenuInt(btn);

		//1. Checking Withdrawal //
		if (btn == 1)
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::string acctype = "Checking";

			Pborder("Enter Amount to withdrawal from your Checking Account");
			getInput(amt);
				
			fee = amt * cwfee;
			if (fee + amt <= checking)
			{
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);
				if (cnf == "Y" || cnf == "y")
				{
				amt += fee;
				fees += fee;
				checking -= amt;
				std::cout << "Withdrawal Completed Successfully\n";
				}
				else
				{
				std::cout << "Withdrawal Cancelled\n"; 
				btn = 0;
				}
			}
			else
			{
			std::cout << "Insufficient Funds..\n";
			btn = 0;
			}
		}
		// 2. Savings Withdrawal // 
		else if (btn == 2)
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::string acctype = "Savings";

			Pborder("Enter Amount to withdrawal from your Savings Account\n");
			getInput(amt);

			fee = amt * cwfee;
			if (fee + amt <= savings)
			{
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);

				if (cnf == "Y" || cnf == "y")
				{
				amt += fee;
				fees += fee;
				savings -= amt;
				std::cout << "Withdrawal Completed Successfully\n";
				}
				else
				{
				std::cout << "Withdrawal Cancelled\n";
				btn = 0;
				}
			}
			else
			{
			std::cout << "Insufficient Funds..\n";
			btn = 0;
			}
		}
		// Return to Previous Menu //
		else if (btn ==  3)
		{
			btn = 25;
		}
	}
SaveData();
}
// End Withdrawal //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

// Transfer // 
void bankAccounts::transfer()
{
	std::string transtype = "Transfer";
	int btn{0};
	while (btn != 25)
	{
		std::cout << "Select Tranfer type:\n";
		std::cout << "[1] - Checking to Savings\n";
		std::cout << "[2] - Savings to Checking\n";
		std::cout << "[3] - Return to Previous Menu\n"; 
		MenuInt(btn);

		// 1. Checking -> Savings //
		if (btn == 1)
		{
			double amt{ 0 }, fee{ 0 };
			std::string acctype = "Checking";
			std::string cnf;

			Pborder("Enter Amount to Transfer from your Checking Account");
			getInput(amt);

			fee = amt * transferfee;
			if (amt + fee <= checking)
			{
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);

				if (cnf == "Y" || cnf == "y")
				{
				checking -= amt + fee;
				fees += fee;
				savings += amt;
				std::cout << "Transfer Completed Successfully\n"; 
				}
				else
				{
				std::cout << "Transfer Cancelled\n";
				btn = 0;
				}
			}
			else
			{
			std::cout << "Insufficient Funds..\n";
			btn = 0;
			}
		}
		// 2. Savings -> Checking //
		else if (btn == 2)
		{
			double amt{ 0 }, fee{ 0 };
			std::string acctype = "Savings";
			std::string cnf;

			Pborder("Enter Amount to Transfer from your Savings Account");
			getInput(amt);

			fee = amt * transferfee;
			if (amt + fee <= savings)
			{
				pconfirm(amt, fee, acctype, transtype);
				getInput(cnf);

				if (cnf == "Y" || cnf == "y")
				{
				savings -= amt + fee;
				fees += fee;
				checking += amt;
				std::cout << "Transfer Completed Successfully\n";
				}
				else
				{
				std::cout << "Transfer Cancelled\n";
				btn = 0;
				}
			}
			else
			{
				std::cout << "Insufficient Funds..\n";
				btn = 0;
			}
		}
		// Return to Previous Menu // 
		else if (btn == 3)
		{
			btn = 25;
		}
	}
SaveData();
}
// End Transfer //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

// Wire // 
void bankAccounts::wire(std::vector<bankAccounts>& BAVec)
{
	std::string wireName, loadName;
	int index2wire{ 0 };
	bool namefound = false;

	Pborder("Enter the name of the Account that you want to Wire to: ");
	getInput(wireName);

	size_t TA = BAVec.size(); 
	std::ifstream read("./ObjectsData/ObjectsCollection.txt");
	while (TA--)
	{
		getline(read, loadName);
		if (wireName == name && wireName == loadName)
		{
			std::cout << "You can't make a wire to your own account, please enter a different account\n";
			break;
		}
		else if (wireName == loadName)
		{
			double amt, fee;
			namefound = true;

			Pborder("Please Enter amount to Transfer: ");
			getInput(amt);

			fee = amt * wireFee;
			if (fee + amt <= checking)
			{
			std::cout << "Please confirm your wire details: \nTransfer Amount: " << amt << "\nTransfer Fee: $" << fee << "\nAccount: " << 
			wireName << " Will Receive: $" << amt << "\nYour Remaining Balance will be: $" << std::setprecision(2) << std::fixed << checking - (fee + amt) << "\n Confirm? (Y / N)\n";

			std::string CNFW;
			getInput(CNFW);
			CNFW[0] = toupper(CNFW[0]);

				if (CNFW[0] == 'Y')
				{
				this->checking -= amt + fee;
				fees += fee;
				BAVec[index2wire].checking += amt;
				std::cout << "Wire Completed Successfully!\n"; 
				break;
				}
				else
				{
				std::cout << "Wire cancelled..Thank you..\n";
				break;
				}
			}
			else
			{
			std::cout << "Insufficient Funds...\n";
			break;
			}
		}
		else
		{
		index2wire++;
		}
	}
	if (namefound == false && wireName != name)
	{
	std::cout << "We couldn't find the account you entered, please try again..\n";
	}
SaveData();
}
// End Wire //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

// Save Object's Data //
void bankAccounts::SaveData()
{
	std::ofstream file;
	file.open("./ObjectsData/" + name + " login" + ".txt");
	file << std::setprecision(2) << std::fixed << name << "\n" << password << "\n" << checking << "\n" << savings << "\n" << investment << "\n" << credit;
	file.close();
}

//Destructor ;) // 
bankAccounts::~bankAccounts()
{
	SaveData(); 
}