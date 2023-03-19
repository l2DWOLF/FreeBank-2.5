#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "BankClass.h"
//This CPP file Header// 
#include "BankAccountsClass.h"




	//constructor
	bankAccounts::bankAccounts(std::string newName)
	{
		name = newName;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Hello " << name << "! \nPlease enter a new password" << std::endl;
		std::cin >> password;
		std::cout << "Your password is: " << password << "\n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

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
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "enter password: " << std::endl;
		std::cin >> tempass;

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

		std::cout << "enter current password: " << std::endl;
		std::cin >> tempass;
		std::string filepass;
		std::ifstream read("./ObjectsData/" + name + " login" + ".txt");
		getline(read, filepass);
		getline(read, filepass);

		if (tempass == filepass)
		{
			std::cout << "Enter New Password: " << std::endl;
			std::cin >> password;

			std::ofstream file;
			file.open("./ObjectsData/" + name + " login" + ".txt");
			file << name << std::endl << password;
			file.close();
		}
		else
			std::cout << "Wrong Password.." << std::endl;
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
		std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "  Bank Account: " << name << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Checking Account: $" << std::fixed << std::setprecision(2) << checking << std::endl;
		std::cout << "Savings Account: $" << std::fixed << std::setprecision(2) << savings << std::endl;
		std::cout << "Investment Account: $" << std::fixed << std::setprecision(2) << investment << std::endl;
		std::cout << "Credit Card: $" << std::fixed << std::setprecision(2) << credit << std::endl;
		std::cout << "Fees Total: $" << std::fixed << std::setprecision(2) << fees << std::endl;
		std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}

	void bankAccounts::deposit() // Deposit
	{
		std::string btn;
	jumpDeposit:
		std::cout << "[1] - Deposit to Checking Account [0.001% Fee]" << std::endl;
		std::cout << "[2] - Deposit to Savings Account [0.005% Fee]" << std::endl;
		std::cin >> btn;

		if (btn == "1")
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::cout << "Enter Amount to Deposit to your Checking Account" << std::endl;
			std::cin >> amt;
			fee = amt * cdfee;
			std::cout << "Please confirm" << std::endl;
			std::cout << "Checking Account Deposit in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
			std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
			std::cout << "Enter [Y] to continue or [N] to cancel" << std::endl;
			std::cin >> cnf;

			if (cnf == "Y" || cnf == "y")
			{
				amt -= fee;
				fees += fee;
				checking += amt;

			}
			else
			{
				goto jumpDeposit;
			}
		}
		else if (btn == "2")
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::cout << "Enter Amount to Deposit to your Savings Account" << std::endl;
			std::cin >> amt;
			fee = amt * sdfee;
			std::cout << "Please confirm" << std::endl;
			std::cout << "Savings Account Deposit in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
			std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
			std::cout << "Enter [Y] to continue or [N] to cancel" << std::endl;
			std::cin >> cnf;

			if (cnf == "Y" || cnf == "y")
			{
				amt -= fee;
				fees += fee;
				savings += amt;
			}
			else
			{
				goto jumpDeposit;
			}
		}
	}
	// End Deposit //

	void bankAccounts::withdrawal() // Withdrawal
	{
		std::string btn;
	jumpwith:
		std::cout << "[1] - Withdrawal from Checking Account [0.002% Fee]" << std::endl;
		std::cout << "[2] - withdrawal from Savings Account [0.010% Fee]" << std::endl;
		std::cin >> btn;

		if (btn == "1")
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::cout << "Enter Amount to withdrawal from your Checking Account" << std::endl;
			std::cin >> amt;
			fee = amt * cwfee;

			if (fee + amt <= checking)
			{
				std::cout << "Please confirm" << std::endl;
				std::cout << "Checking Account withdrawal in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
				std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
				std::cout << "Enter [Y] to continue or [N] to cancel" << std::endl;
				std::cin >> cnf;

				if (cnf == "Y" || cnf == "y")
				{
					amt += fee;
					fees += fee;
					checking -= amt;

				}
				else
				{
					goto jumpwith;
				}
			}
			else
			{
				std::cout << "Insufficient Funds.." << std::endl;
			}
		}
		else if (btn == "2")
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;
			std::cout << "Enter Amount to Withdrawal from your Savings Account" << std::endl;
			std::cin >> amt;
			fee = amt * swfee;

			if (fee + amt <= savings)
			{
				std::cout << "Please confirm" << std::endl;
				std::cout << "Savings Account Withdrawal in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
				std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
				std::cout << "Enter [Y] to continue or [N] to cancel" << std::endl;
				std::cin >> cnf;

				if (cnf == "Y" || cnf == "y")
				{
					amt += fee;
					fees += fee;
					savings -= amt;
				}
				else
				{
					goto jumpwith;
				}
			}
			else
			{
				std::cout << "Insufficient Funds.." << std::endl;
			}
		}
	}
	// End Withdrawal //

	void bankAccounts::transfer() // Transfer
	{

		std::string btn;
	jumptransfer:
		std::cout << "Select Tranfer type [fee is 0.001%] " << std::endl;
		std::cout << "[1] - Checking to Savings" << std::endl;
		std::cout << "[2] - Savings to Checking" << std::endl;
		std::cin >> btn;

		if (btn == "1")
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;

			std::cout << "Enter Amount to Transfer from your Checking Account" << std::endl;
			std::cin >> amt;
			fee = amt * transferfee;

			if (amt + fee <= checking)
			{
				std::cout << "Please confirm" << std::endl;
				std::cout << "Checking Account Transfer in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
				std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
				std::cout << "This Amount will be Transferred to your Savings Account" << std::endl;
				std::cout << "Enter [Y] to continue or [N] to cancel" << std::endl;
				std::cin >> cnf;

				if (cnf == "Y" || cnf == "y")
				{
					checking -= amt + fee;
					fees += fee;
					savings += amt;
				}
				else
				{
					goto jumptransfer;
				}
			}
			else
			{
				std::cout << "Insufficient Funds.." << std::endl;
			}
		}
		else if (btn == "2")
		{
			double amt{ 0 }, fee{ 0 };
			std::string cnf;

			std::cout << "Enter Amount to Transfer from your Savings Account" << std::endl;
			std::cin >> amt;
			fee = amt * transferfee;

			if (amt + fee <= savings)
			{
				std::cout << "Please confirm" << std::endl;
				std::cout << "Savings Account Transfer in the amount of: $" << std::fixed << std::setprecision(2) << amt << std::endl;
				std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << fee << std::endl;
				std::cout << "This Amount will be Transferred to your Checking Account" << std::endl;
				std::cout << "Enter [Y] to continue or [N] to cancel" << std::endl;
				std::cin >> cnf;

				if (cnf == "Y" || cnf == "y")
				{
					savings -= amt + fee;
					fees += fee;
					checking += amt;
				}
				else
				{
					goto jumptransfer;
				}
			}
			else
			{
				std::cout << "Insufficient Funds.." << std::endl;
			}
		}
	}
	// End Transfer //

	// Wire // 
	void bankAccounts::wire(std::vector<bankAccounts>& BAVec)
	{
		std::string wireName;
		bool namefound = 0;
		std::cout << "Enter the Account Name that you want to Wire to: " << std::endl;
		std::cin >> wireName;


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
		for (int l = 0; l < TA; l++)
		{
			getline(read, loadName);

			if (wireName == loadName && wireName != name)
			{
				double amt, fee;
				namefound = true;

				std::cout << "Please Enter amount to Transfer: " << std::endl;
				std::cin >> amt;
				fee = amt * wireFee;

				if (fee + amt <= checking)
				{
				jumpDeposit:
					std::cout << "Please confirm your wire details: \nTransfer Amount: " << amt << "\nTransfer Fee: -$" << fee
						<< "\n Account - " << wireName << " Will Receive: $" << amt - fee << "\n Confirm? (Y / N)\n";
					std::string CNFW;
					std::cin >> CNFW;
					CNFW[0] = toupper(CNFW[0]);

					if (CNFW[0] == 'Y')
					{
						this->checking -= amt + fee;
						BAVec[index2wire].checking += amt - fee;
						fees += fee;
						break;
					}
					else if (CNFW[0] == 'N')
					{
						std::cout << "Wire cancelled..Thank you..\n";
					}
					else
						goto jumpDeposit;
				}
				else
				{
					std::cout << "Insufficient Funds...";
					namefound = false;
					break;
				}
			}
			else if (wireName == name)
			{
				std::cout << "You can't make a wire to your own account, please enter a different account" << std::endl;
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
