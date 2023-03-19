#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "BankClass.h"
#include "InputTools.h"
//This CPP file Header// 
#include "BankAccountsClass.h"




	//constructor
	bankAccounts::bankAccounts(std::string newName)
	{
		name = newName;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << "Hello " << name << "! \nPlease enter a new password\n";
		getInputPass(password);
		std::cout << "Your password is: " << password << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

		//Create Object file with name + pass//
		std::ofstream file;
		file.open("./ObjectsData/" + name + " login" + ".txt");
		file << name << std::endl << password;
		file.close();

		//Add name to ObjectsCollection file for loading existing accounts
		std::fstream Cfile;
		Cfile.open("./ObjectsData/ObjectsCollection.txt", std::ios::app);
		Cfile << name << std::endl;
		Cfile.close();
	}

	//copy constructor for loading objects from objectsCollection file
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
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << "enter password: \n";
		getInputPass(tempass);

		std::string filepass;
		std::ifstream read("./ObjectsData/" + name + " login" + ".txt");
		getline(read, filepass);
		getline(read, filepass);

		if (tempass == filepass)
			rslt = true;
		else
			rslt = false;

		return rslt; //return permission to rslt to main to continue login (accountmenu function).
	}

	void bankAccounts::changePass()
	{
		std::string tempass;

		std::cout << "enter current password: \n";
		std::string filepass;
		std::ifstream read("./ObjectsData/" + name + " login" + ".txt");
		getline(read, filepass);
		getline(read, filepass);

		if (tempass == filepass)
		{
			std::cout << "Enter New Password: \n";
			getInputPass(password);

			std::ofstream file;
			file.open("./ObjectsData/" + name + " login" + ".txt");
			file << name << std::endl << password;
			file.close();
		}
		else
			std::cout << "Wrong Password..\n";
	}


	double bankAccounts::movefees() //return occured fees from session to accountmenu upon exit.
	{
		return fees;
	}

	void bankAccounts::clearfees() //clear occured fees from current session.
	{
		fees = 0;
	}

	void bankAccounts::info() // print info
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
	}

	void bankAccounts::deposit() // Deposit
	{
		int btn{ 0 };
		while (btn != 25)
		{
			std::cout << "[1] - Deposit to Checking Account\n";
			std::cout << "[2] - Deposit to Savings Account\n";
			std::cout << "[3] - Return to Previous Menu\n";
			getInput(btn);

			if (btn == 1)
			{
				double amt{ 0 }, fee{ 0 };
				bool valid{ 0 };
				std::string cnf;

				std::cout << "Enter Amount to Deposit to your Checking Account\n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * cdfee;
					std::cout << "Please confirm\n";
					std::cout << "Checking Account Deposit in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
					std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
					std::cout << "Enter [Y] to continue or [N] to cancel\n";
					getInput(cnf);

					if (cnf == "Y" || cnf == "y")
					{
						amt -= fee;
						fees += fee;
						checking += amt;

					}
					else
					{
						std::cout << "Deposit Cancelled\n";
						btn = 0;
					}
				}
				else
				{
					btn = 1;
				}
			}
			else if (btn == 2)
			{
				double amt{ 0 }, fee{ 0 };
				bool valid{ 0 };
				std::string cnf;

				std::cout << "Enter Amount to Deposit to your Savings Account\n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * cdfee;
					std::cout << "Please confirm\n";
					std::cout << "Savings Account Deposit in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
					std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
					std::cout << "Enter [Y] to continue or [N] to cancel\n";
					getInput(cnf);

					if (cnf == "Y" || cnf == "y")
					{
						amt -= fee;
						fees += fee;
						savings += amt;

					}
					else
					{
						std::cout << "Deposit Cancelled\n";
						btn = 0;
					}
				}
				else
				{
					btn = 1;
				}
			}
			else if (btn == 3)
			{
				btn = 25;
			}
			
		}
}	
	// End Deposit //

	void bankAccounts::withdrawal() // Withdrawal
	{
		int btn{ 0 };
		while (btn != 25)
		{
			std::cout << "[1] - Withdrawal from Checking Account\n";
			std::cout << "[2] - withdrawal from Savings Account\n";
			std::cout << "[3] - Return to Previous Menu\n";
			getInput(btn);

			if (btn == 1)
			{
				double amt{ 0 }, fee{ 0 };
				std::string cnf;
				bool valid; 

				std::cout << "Enter Amount to withdrawal from your Checking Account\n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * cwfee;
					if (fee + amt <= checking)
					{
						std::cout << "Please confirm\n";
						std::cout << "Checking Account withdrawal in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
						std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
						std::cout << "Enter [Y] to continue or [N] to cancel\n";
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
				else
				{
					btn = 0;
				}
			}
			else if (btn == 2)
			{
				double amt{ 0 }, fee{ 0 };
				std::string cnf;
				bool valid;

				std::cout << "Enter Amount to withdrawal from your Savings Account\n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * cwfee;

					if (fee + amt <= savings)
					{
						std::cout << "Please confirm\n";
						std::cout << "Savings Account withdrawal in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
						std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
						std::cout << "Enter [Y] to continue or [N] to cancel\n";
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
			}
			else if (btn ==  3)
			{
				btn = 25;
			}
		}
	}
	// End Withdrawal //

	// Transfer // 
	void bankAccounts::transfer()
	{
		bool valid{ 0 };
		int btn{0};
		while (btn != 25)
		{
			std::cout << "Select Tranfer type:\n";
			std::cout << "[1] - Checking to Savings\n";
			std::cout << "[2] - Savings to Checking\n";
			std::cout << "[3] - Return to Previous Menu\n"; 
			getInput(btn);

			if (btn == 1)
			{
				double amt{ 0 }, fee{ 0 };
				std::string cnf;

				std::cout << "Enter Amount to Transfer from your Checking Account\n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * transferfee;
					if (amt + fee <= checking)
					{
						std::cout << "Please confirm\n";
						std::cout << "Checking Account Transfer in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
						std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
						std::cout << amt - fee << " Amount will be Transferred to your Savings Account\n";
						std::cout << "Enter [Y] to continue or [N] to cancel\n";
						getInput(cnf);

						if (cnf == "Y" || cnf == "y")
						{
							checking -= amt + fee;
							fees += fee;
							savings += amt;
						}
						else
						{
							std::cout << "Wire Cancelled\n";
							btn = 0;
						}
					}
					else
					{
						std::cout << "Insufficient Funds..\n";
						btn = 0;
					}
				}
			}
			else if (btn == 2)
			{
				double amt{ 0 }, fee{ 0 };
				std::string cnf;

				std::cout << "Enter Amount to Transfer from your Savings Account\n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * transferfee;
					if (amt + fee <= savings)
					{
						std::cout << "Please confirm\n";
						std::cout << "Savings Account Transfer in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
						std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
						std::cout << amt - fee << " will be Transferred to your Savings Account\n";
						std::cout << "Enter [Y] to continue or [N] to cancel\n";
						getInput(cnf);

						if (cnf == "Y" || cnf == "y")
						{
							savings -= amt + fee;
							fees += fee;
							checking += amt;
						}
						else
						{
							std::cout << "Wire Cancelled\n";
							btn = 0;
						}
					}
					else
					{
						std::cout << "Insufficient Funds..\n";
						btn = 0;
					}
				}
			}
			else if (btn == 3)
			{
				btn = 25;
			}
		}
	}
	// End Transfer //

	// Wire // 
	void bankAccounts::wire(std::vector<bankAccounts>& BAVec)
	{
		std::string wireName;
		bool namefound = 0;

		std::cout << "Enter the Account Name that you want to Wire to: \n";
		getInput(wireName);

		int TA;
		{
			std::string loadTA;
			std::ifstream read("./ObjectsData/totalAccounts.txt");
			getline(read, loadTA);
			TA = std::stoi(loadTA);
		}

		std::string loadName;
		int index2wire = 0;

		std::ifstream read("./ObjectsData/ObjectsCollection.txt");
		while (TA--)
		{
			getline(read, loadName);

			if (wireName == loadName && wireName != name)
			{
				double amt, fee;
				bool valid{ 0 };
				namefound = true;

				std::cout << "Please Enter amount to Transfer: \n";
				getInput(amt, valid);

				if (valid)
				{
					fee = amt * wireFee;
					if (fee + amt <= checking)
					{
						std::cout << "Please confirm your wire details: \nTransfer Amount: " << amt << "\nTransfer Fee: $" 
								  << fee << "\nAccount: " << wireName << " Will Receive: $" << amt << 
							   	  "\nYour Remaining Balance will be: " << checking - (fee + amt) << "\n Confirm? (Y / N)\n";

						std::string CNFW;
						getInput(CNFW);
						CNFW[0] = toupper(CNFW[0]);

						if (CNFW[0] == 'Y')
						{
							this->checking -= amt + fee;
							BAVec[index2wire].checking += amt - fee;
							fees += fee;
							std::cout << "Wire Completed Successfully!\n"; 
							break;
						}
						else if (CNFW[0] == 'N')
						{
							std::cout << "Wire cancelled..Thank you..\n";
							break;
						}
					}
					else
					{
						std::cout << "Insufficient Funds...\n";
						namefound = false;
						break;
					}
				}
			}
			else if (wireName == name && wireName == loadName)
			{
				std::cout << "You can't make a wire to your own account, please enter a different account\n";
				break;
			}
			else
			{
				index2wire++;
			}
		}
	}
	// End Wire // 

	//Destructor ;) // 
	bankAccounts::~bankAccounts()
	{
		//Save Object's Data// 
		std::ofstream file;
		file.open("./ObjectsData/" + name + " login" + ".txt");
		file << std::setprecision(2) << std::fixed << name << "\n" << password << "\n" << checking << "\n" << savings << "\n" << investment << "\n" << credit;
		file.close();
	}
