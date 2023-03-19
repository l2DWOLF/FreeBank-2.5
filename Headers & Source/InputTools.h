#pragma once


//Overloaded getInput Function//
void getInput(std::string& input);
void getInput(int& input);
void getInput(double& input);
void getInput(int& input, bool& rslt);
void getInput(double& input, bool& rslt);

//Standalone getInput for password restrictions// 
void getInputPass(std::string&);
