#pragma once



class bankAccounts : protected Bank
{
private:
	double checking{ 0 }, savings{ 0 }, investment{ 0 }, credit{ 0 }, fees{ 0 };
	std::string name, password;

public:

	//constructor
	bankAccounts(std::string newName)
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
	bankAccounts(std::string& maname, std::string& mapass, std::string& machecking,
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

	std::string namecheck()
	{
		return name;
	}

	bool passcheck()
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

	void changePass()
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


	double movefees() //return occured fees from session to accountmenu upon exit.
	{
		return fees;
	}

	void clearfees() //clear occured fees from current session.
	{
		fees = 0;
	}

	void info() // print info
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

	void deposit() // Deposit
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

	void withdrawal() // Withdrawal
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


	void transfer() // Transfer
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

	//Destructor ;) // 
	~bankAccounts()
	{
		std::ofstream file;
		file.open("./ObjectsData/" + name + " login" + ".txt");
		file << std::setprecision(2) << std::fixed << name << "\n" << password << "\n" << checking << "\n" << savings << "\n" << investment << "\n" << credit;
		file.close();
	}

};