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

	while(1){
		//We would also have a check here to see if the user is null to make sure a user with permissions is logged in
		//If not we would call the login function
		string input; //user's input
		cin >> input;
		
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
				
					std:: string line = "";
					bool accountFound = false;
					// read each line of account file
					while(std::getline(iAccFile, line)){
						std::string info[4];
						int infoIndex = 0;
						
						char *linechar = new char[line.length() + 1];
						strcpy(linechar, line.c_str());
						
						char* tokens = strtok(linechar, " \n\r");
						
						// store each account information
						while(tokens != NULL){
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
				//Call bid function
			}
			else if(input == "create"){
				if(current->accountType_ == "Admin"){
				//Calls create function
				cout << "Enter username for new user:\n";
				string newUsername;
				cin >> newUsername;
				
				cout << "Enter password for new user:\n";
				string newPassword;
				cin >> newPassword;
				
				cout << "Enter credit for new user:\n";
				double newCredit;
				cin >> newCredit;
				// somehow create new user
				} else {
					cout << "ERROR: Cannot create user with a non-admin account\n";
				}
			}
			else if(input == "logout"){
				//Calls logout function
				delete current;
				isLoggedIn = false;
				cout << "successfully logged out\n";
				// need to create daily transaction file
			}
			else if(input == "addcredit"){
				//Calls addcredit function
			}
			else if(input == "advertise"){
				//Calls advertise function
			}
			else if(input == "delete"){
				if (current->accountType_ == "Admin"){
					cout << "Enter user to be deleted:\n";
					string userToDelete;
					cin >> userToDelete;
					current->deleteUser(userToDelete);
				}
				else{
					cout << "ERROR: Cannot delete user with a non-admin account\n";
				}
			}
			else if(input == "refund"){
				//Calls refund function
			}
			else {
				cout << "ERROR: Not a command\n";
			}
		}
		else{
			if(input == "exit"){
				exit(0);
			}
			if (input != "login"){
				cout << "ERROR: User is not logged in\n";
			}
		}
	}	
}