#pragma once



class Bank
{
private:
	double income{ 0 };

protected:
	const double cdfee = 0.001, sdfee = 0.005, cwfee = 0.002, swfee = 0.010; // Fees (cd = checking deposit, cw = checking withdrwal)
	const double transferfee = 0.001, invTfee = 0.002, wireFee = 0.0015;


public:
	//add occured fees from user session to FreeBank's income memeber
	void Fee(double amount);

	//Print total income
	void profit();

	//Confirm if an account name already exists upon opening a new account
	bool namecheckAll(std::string nameTest);

};
