/*
main
Program call prompts the user for the actions that want to take
*/

#include <cstdio> //Printf scanf
#include <string>
#include <iostream>
//Import major file components
//#include "bid.h"
#include "advertisement.h"
#include "user.h"

using namespace std;

int main(){
	
	cout << "Please login to the system\n";
	bool isLoggedIn = false;
	//Calls login class
	User * current;
	string transactions = "";
	const char* dtf = "dailyTransactions.dt";
	
	while(1){
		//We would also have a check here to see if the user is null to make sure a user with permissions is logged in
		//If not we would call the login function
		string input; //user's input
		cin >> input;
		
		if(input == "exit"){
			exit(0);
		}
		
		if(input == "login"){
			
			if (isLoggedIn){
				cout << "ERROR: Already logged in\n";
			}
			else{
				//check if account exists
				std::ifstream iAccFile;
				iAccFile.open(accountFile);
				
				if(iAccFile.is_open()){
					string username;
					string password;
					cout << "Enter username:\n";
					cin >> username;
					cout << "Enter password:\n";
					cin >> password;
				
					string line = "";
					bool accountFound = false;
					// read each line of account file
					while(getline(iAccFile, line)){
						
						std::string info[4];
						int infoIndex = 0;
						
						char *linechar = new char[line.length() + 1];
						strcpy(linechar, line.c_str());
						
						char* tokens = strtok(linechar, " \n\r");
						
						// store each account information
						while(tokens != NULL){
							//cout << info[infoIndex] + "\n";
							info[infoIndex++] = tokens;
							tokens = strtok(NULL, " \n\r");
						}
						
						//cout << username + " " + password + "\n";
						//cout <<info[0] + " " + info[3] + "\n";
						
						if(username.compare(info[0]) == 0 && password.compare(info[3]) == 0){
							cout << "Login Successful\n";
							accountFound = true;
							isLoggedIn = true;
							
							if (info[1] == "AA"){
								Admin * adminUser = new Admin(info[0], info[3], std::stod(info[2]));
								current = adminUser;
							}else if (info[1] == "FS"){
								FullStandard * fullStandUser = new FullStandard(info[0], info[3], std::stod(info[2]));
								current = fullStandUser;
							}else if (info[1] == "SS"){
								SellStandard * sellStandUser = new SellStandard(info[0], info[3], std::stod(info[2]));
								current = sellStandUser;
							}else if (info[1] == "BS"){
								BuyStandard * buyStandUser = new BuyStandard(info[0], info[3], std::stod(info[2]));
								current = buyStandUser;
							}
							break;
						}
					}
					
					if (!accountFound){
						cout << "ERROR: Entered username and password combination does not exist\n";
					}
					
					// close files
					iAccFile.close();
					
				} else {
					cout << "ERROR: There are no registered users";
				}	
			}
		}
		
		if (isLoggedIn){
			if(input == "bid"){
				if(current->accountType_ == "admin"){
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					cout << "Enter item name:\n";
					string itemName;
					cin >> itemName;
					
					cout << "Enter seller's username:\n";
					string seller;
					cin >> seller;
					
					adminAccount->bid(seller, itemName);
				} else if(current->accountType_ == "full-standard"){
					FullStandard * fsAccount = dynamic_cast<FullStandard*>(current);
					cout << "Enter item name:\n";
					string itemName;
					cin >> itemName;
					
					cout << "Enter seller's username:\n";
					string seller;
					cin >> seller;
					
					fsAccount->bid(seller, itemName);
				} else if(current->accountType_ == "buy-standard"){
					BuyStandard * bsAccount = dynamic_cast<BuyStandard*>(current);
					cout << "Enter item name:\n";
					string itemName;
					cin >> itemName;
					
					cout << "Enter seller's username:\n";
					string seller;
					cin >> seller;
					
					bsAccount->bid(seller, itemName);
				} else if(current->accountType_ == "sell-standard"){
					printf("ERROR: standard sell accounts cannot bid\n");
				}
			}
			else if(input == "create"){
				if(current->accountType_ == "admin"){
					//Calls create function
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					cout << "Enter username for new user:\n";
					string newUsername;
					cin >> newUsername;
				
					cout << "Enter password for new user:\n";
					string newPassword;
					cin >> newPassword;
					
					cout << "Enter account type for new user:\n";
					string newType;
					cin >> newType;
				
					cout << "Enter credit for new user:\n";
					double newCredit;
					cin >> newCredit;
					
					//create new user
					adminAccount->createUser(newUsername, newType, newCredit, newPassword);
					
					//add transaction
					transactions += "01 " + current->username_ + " " + current->getType() + " " + to_string((int)current->credit_) + "\n";
					
				} else {
					cout << "ERROR: Cannot create user with a non-admin account\n";
				}
			}
			else if(input == "logout"){
				//Calls logout function
				//delete current;
				transactions += "00 " + current->username_ + " " + current->getType() + " " + to_string((int)current->credit_) + "\n";
				
				current = NULL;
				isLoggedIn = false;
				cout << "Logout Successful\n";
				
				//output daily transactions
				ofstream oDTF;
				oDTF.open(dtf);
				
				if (oDTF.is_open()){
					oDTF << transactions;
				}
				else{
					cout << "ERROR: Cannot list transactions\n";
				}
				
				oDTF.close();
				
				cout << "Transactions Listed\n";
			}
			else if(input == "addcredit"){
				//Calls addcredit function
				if (current->accountType_ != "admin"){
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					
					cout << "Enter Amount:\n";
					double amountToAdd;
					cin >> amountToAdd;
					
					adminAccount->addCredit(amountToAdd, current->username_);
				}
				else{
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					
					cout << "Enter amount:\n";
					float amountToAdd;
					cin >> amountToAdd;
					cout << "Enter user to add credit to:\n";
					string userToAdd;
					cin >> userToAdd;
					
					adminAccount->addCredit(amountToAdd, userToAdd);
				}
				
				transactions += "06 " + current->username_ + " " + current->getType() + " " + to_string((int)current->credit_) + "\n";
			}
			else if(input == "advertise"){
				//Calls advertise function
			}
			else if(input == "delete"){
				if (current->accountType_ == "admin"){
					
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					
					cout << "Enter user to be deleted:\n";
					string userToDelete;
					cin >> userToDelete;
					adminAccount->deleteUser(userToDelete);
					
					transactions += "02 " + current->username_ + " " + current->getType() + " " + to_string((int)current->credit_) + "\n";
				}
				else{
					cout << "ERROR: Cannot delete user with a non-admin account\n";
				}
			}
			else if(input == "refund"){
				if(current->accountType_ == "admin"){
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					cout << "Enter buyer:\n";
					string buyer;
					cin >> buyer;
					
					cout << "Enter seller:\n";
					string seller;
					cin >> seller;
					
					cout << "Enter Amount of Credit:\n";
					double credit;
					cin >> credit;
					
					transactions += "05 " + buyer + " " + seller + " " + to_string((int)credit) + "\n";
					
					adminAccount->refund(seller, buyer, credit);
				} else {
					cout << "ERROR: Must be an admin to refund\n";
				}
			}
			else if(input != "login"){
				cout << "ERROR: Not a command\n";
			}
		}
		else{
			if (input != "login"){
				cout << "ERROR: User is not logged in\n";
			}
		}
	}	
}