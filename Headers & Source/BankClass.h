#pragma once



class Bank
{
private:
	double income{ 0 };

protected:
	const double cdfee = 0.005, sdfee = 0.010, cwfee = 0.015, swfee = 0.020; // Fees (cd = checking deposit, cw = checking withdrwal)
	const double transferfee = 0.030, invTfee = 0.075, wireFee = 0.025;


public:
	//add occured fees from user session to FreeBank's income memeber
	void Fee(double amount);

	//Print total income
	void profit();

	//Confirm if an account name already exists upon opening a new account
	bool namecheckAll(std::string nameTest);

};
