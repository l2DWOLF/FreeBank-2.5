#pragma once



class bankAccounts : protected Bank
{
private:
	double checking{ 0 }, savings{ 0 }, investment{ 0 }, credit{ 0 }, fees{ 0 };
	std::string name, password;

public:

	//constructor
	bankAccounts(std::string newName);

	//copy constructor for loading objects from objectsCollection file
	bankAccounts(std::string& maname, std::string& mapass, std::string& machecking,
		std::string& masavings, std::string& mainvestment, std::string& macredit);

	//Return Name
	std::string namecheck() const;

	//Password Check
	bool passcheck() const;

	//Change Password
	void changePass();

	//Move Fees -> return occured fees from session to accountmenu upon exit.
	double movefees() const;
	
	//Clear Fees
	void clearfees();

	//Print Account Info
	void info(); 

	// Deposit
	void deposit();

	// Withdrawal 
	void withdrawal();
	
	// Transfer
	void transfer(); 

	// Wire
	void wire(std::vector<bankAccounts>& BAVec);

	// Save Object's Data 
	void SaveData();

	// Destructor ;)
	~bankAccounts();

};