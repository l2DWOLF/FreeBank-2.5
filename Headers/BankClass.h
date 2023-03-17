#pragma once



class Bank
{
private:
	double income{ 0 };

protected:
	const double cdfee = 0.001, sdfee = 0.005, cwfee = 0.002, swfee = 0.010; // Fees (cd = checking deposit, cw = checking withdrwal)
	const double transferfee = 0.001, invTfee = 0.002;


public:
	void Fee(double amount)
	{
		income += amount;
	}

	void profit()
	{
		std::cout << "\n \n \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Bank's Profits: $" << std::fixed << std::setprecision(2) << income << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}

	bool namecheckAll(std::string nameTest)
	{
		std::string ObjNames;
		std::ifstream read("./ObjectsData/" + nameTest + " login" + ".txt");
		getline(read, ObjNames);

		if (nameTest == ObjNames)
			return false;
		else
			return true;
	}

};
