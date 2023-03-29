#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "BankClass.h"
#include "InputTools.h"
//This CPP file Header// 
#include "BankAccountsClass.h"




// Constructor //
bankAccounts::bankAccounts(std::string newName)
{
	name = newName;
	std::cout << "\n\n--------------------------------------\n";
	std::cout << "Hello! " << name << "!  :)\nPlease Enter a New Password:\n";
	std::cout << "--------------------------------------\n";
	getInputPass(password, name);
	std::cout << "\n\n\n--------------------------------------\n";
	std::cout << name << ", Your Password is: " << password << std::endl;
	std::cout << "--------------------------------------\n";

	//Create Object file with name + pass//
	SaveData();

	//Add name to ObjectsCollection file for loading existing accounts
	std::fstream Cfile;
	Cfile.open("./ObjectsData/ObjectsCollection.txt", std::ios::app);
	Cfile << name << std::endl;
	Cfile.close();
}

// Copy Constructor for loading objects from objectsCollection file //
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

std::string bankAccounts::namecheck() const
{
	return name;
}

bool bankAccounts::passcheck() const
{
	std::string tempass;
	bool rslt{ 0 };
	Pborder("Enter Password: ");
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
		getInputPass(password, name);
		SaveData();
	}
	else
		std::cout << "Wrong Password..\n";
}

double bankAccounts::movefees() const
{
	return fees;
}

void bankAccounts::clearfees()
{
	fees = 0;
}

void bankAccounts::info()
{
	fees++;
	checking--;
	std::cout << "\n \n \n--------------------------------\n";
	std::cout << "    Bank Account: [" << name << "]\n";
	std::cout << "--------------------------------\n";
	std::cout << std::left << std::setfill(' ') << std::setw(30) << "Checking Account Balance:" << std::fixed << std::setprecision(2) <<"$"<< checking << std::endl;
	std::cout << std::left << std::setfill(' ') << std::setw(30) << "Savings Account Balance:" << std::fixed << std::setprecision(2) <<"$"<< savings << std::endl;
	std::cout << std::left << std::setfill(' ') << std::setw(30) << "Investment Account Balance:" << std::fixed << std::setprecision(2) <<"$"<< investment << std::endl;
	std::cout << std::left << std::setfill(' ') << std::setw(30) << "Credit Card Balance:" << std::fixed << std::setprecision(2) <<"$"<< credit << std::endl;
	std::cout << "\n\nTotal Fees Occured in Current Banking Session: $" << std::fixed << std::setprecision(2) << fees << std::endl;
	std::cout << "--------------------------------\n";
SaveData();
}

// Deposit //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 
void bankAccounts::deposit() 
{
	std::string transtype = "Deposit"; 
	int btn{ 0 };
	while (btn != 25)
	try{		
		PDMenu();
		MenuInt(btn);
		// Deposit //
		if (btn == 1 || btn == 2)
		{
			double amt{ 0 }, fee{ 0 }, feetype{ 0 };
			std::string cnf;
			std::string acctype;
			//Checking or Savings?//
			if (btn == 1)
			{acctype = "Checking"; feetype = cdfee;}
			else if (btn == 2)
			{acctype = "Savings"; feetype = sdfee;}
			//Get Amount & Confirm Transaction//
			Pborder("Enter Amount to Deposit to your " + acctype + " Account");
			getInput(amt);
			fee = amt * feetype;
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);
			if (cnf[0] == 'Y' || cnf[0] == 'y')
			{
				amt -= fee;
				fees += fee;
				if (acctype == "Checking")
					checking += amt;
				else if (acctype == "Savings")
					savings += amt; 
				std::cout << "Deposit Completed Successfully!\n"; 
			}
			else
				std::cout << "Deposit Cancelled\n";	
		}
		//3. Return to Previous Menu//
		else if (btn == 3)
		{
			btn = 25;
		}
	  }
	catch (const char* e)
	{
		std::cout << "Exception: " << e << std::endl;
	}
SaveData();
}	// End Deposit //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

// Withdrawal // 
void bankAccounts::withdrawal() 
{
	int btn{ 0 };
	std::string transtype = "Withdrawal";
	while (btn != 25)
	try {
		PWMenu();
		MenuInt(btn);
		// Withdrawal //
		if (btn == 1 || btn == 2)
		{
			double amt{ 0 }, fee{ 0 }, feetype{ 0 };
			std::string cnf;
			std::string acctype;
			//Checking or Savings?//
			if (btn == 1)
			{acctype = "Checking"; feetype = cwfee;}
			else if (btn == 2)
			{acctype = "Savings"; feetype = swfee;}
			//Get amount, confirm funds & Transac.//
			Pborder("Enter Amount to withdrawal from your " + acctype + " Account");
			getInput(amt);
			fee = amt * feetype;
			if ((acctype == "Checking" && fee+amt <= checking) || (acctype == "Savings" && fee+amt <= savings))
			{
				pconfirm(amt, fee, acctype, transtype);
				getInput(cnf);
				if (cnf == "Y" || cnf == "y")
				{
					amt += fee;
					fees += fee;
					if (acctype == "Checking")
						checking -= amt;
					else if (acctype == "Savings")
						savings -= amt; 
					std::cout << "Withdrawal Completed Successfully!\n";
				}
				else
					std::cout << "Withdrawal Cancelled\n";
			}
			else
				std::cout << "Insufficient Funds..\n";
		}
		// 3. Return to Previous Menu //
		else if (btn == 3)
			btn = 25;
		}
		catch (const char* e)
		{
		std::cout << "Exception: " << e << std::endl;
		}
SaveData();
}	// End Withdrawal //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

// Transfer // 
void bankAccounts::transfer()
{
	std::string transtype = "Transfer";
	int btn{0};
	while (btn != 25)
	try{
		PTMenu();
		MenuInt(btn);
		// Transfer //
		if (btn == 1 || btn == 2)
		{
			double amt{ 0 }, fee{ 0 };
			std::string acctype;
			std::string cnf;
			//Checking or Savings?//
			if (btn == 1)
				acctype = "Checking";
			else if (btn == 2)
				acctype = "Savings"; 
			//Get Amount, Confirm Funds & Transaction//
			Pborder("Enter Amount to Transfer from your " + acctype + " Account");
			getInput(amt);
			fee = amt * transferfee;
			if ((acctype == "Checking" && fee + amt <= checking) || (acctype == "Savings" && fee + amt <= savings))
			{
			pconfirm(amt, fee, acctype, transtype);
			getInput(cnf);
				if (cnf[0] == 'Y' || cnf[0] == 'y')
				{
				fees += fee;
					if (acctype == "Checking")
					{checking -= amt + fee; savings += amt;}
					else if (acctype == "Savings")
					{savings -= amt + fee; checking += amt;}
				std::cout << "Transfer Completed Successfully!\n"; 
				}
				else
					std::cout << "Transfer Cancelled\n";
			}
			else
				std::cout << "Insufficient Funds..\n";
		}
		// 3. Return to Previous Menu // 
		else if (btn == 3)
			btn = 25;
	  }
	  catch (const char* e)
	  {
		  std::cout << "Exception: " << e << std::endl;
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
	getInputUserName(wireName);

	size_t TA = BAVec.size(); 
	std::ifstream read("./ObjectsData/ObjectsCollection.txt");
	while (TA--)
	try{
		getline(read, loadName);
		if (wireName == name && wireName == loadName)
		{
			std::cout << "You can't make a wire to your own account :) \n please enter a different account name!\n";
			break;
		}
		else if (wireName == loadName)
		{
			double amt, fee;
			namefound = true;

			Pborder("Please Enter the Amount to Transfer: ");
			getInput(amt);

			fee = amt * wireFee;
			if (fee + amt <= checking)
			{
			std::cout << "Please Confirm your Wire Details: \nTransfer Amount: $" << amt << "\nTransfer Fee: $" << fee << "\nAccount: " << 
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
				{std::cout << "Wire Cancelled..\n"; break;}
			}
			else
			{std::cout << "Insufficient Funds...\n"; break;}
		}
		else
		{
		index2wire++;
		}
	  }
	  catch (const char* e)
	  {
		  std::cout << "Exception: " << e << std::endl;
	  }
	if (namefound == false && wireName != name)
	{
	std::cout << "We couldn't find the account you entered, please try again..\n";
	}
SaveData();
}	// End Wire //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ || 

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