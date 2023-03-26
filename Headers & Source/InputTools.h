#pragma once


//Overloaded getInput Validation Function//
void getInput(std::string& input); //String Input
void getInput(int& input); //INT Input 
void getInput(double& input);//Double Input

//Standalone getInput for Password & UserName restrictions// 
void getInputPass(std::string& input);
void getInputPass(std::string&, std::string); // PW != UserName check 
void IFSIze(size_t& loopsize, const size_t& Tsize); //loopSize for != UserName check 
void getInputUserName(std::string& input);

//Menu Int//
void MenuInt(int& input);

// Menus Printing Items //
void pconfirm(double amt, double fee, std::string acctype, std::string transtype); //Print confirm menu for acc transactions 
void PMainMenu(); //Print Main Menu
void PAccountMenu(); //Print Account Menu
void Pborder(std::string message); //Print a message inside border
void UNRules(); //Print UserName Entry Rules.
void PWRules(); //Print PassWord Entry Rules.