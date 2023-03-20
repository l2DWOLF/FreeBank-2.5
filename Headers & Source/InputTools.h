#pragma once


//Overloaded getInput Validation Function//
void getInput(std::string& input); //String Input
void getInput(int& input); //INT Input 
void getInput(double& input);//Double Input

//Standalone getInput for password restrictions// 
void getInputPass(std::string&);

//Menu Int//
void MenuInt(int& input);

// Menus Printing Items //
void pconfirm(double amt, double fee, std::string acctype, std::string transtype); //Print confirm menu for acc transactions 
void PMainMenu(); //Print Main Menu
void PAccountMenu(); //Print Account Menu
void Pborder(std::string message); //Print message inside border