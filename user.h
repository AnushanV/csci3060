#include <fstream>
//#include <iostream>
#include <cstdlib>
//#include <cstdio>
//#include <iostream>
#include <string.h>
const char* accountFile = "accounts.txt";

struct User{
	std::string username_;
	std::string password_;
	std::string accountType_;
	float credit_;
	
	User(){
		
	}
	
	// constructor
	User(std::string username, std::string password, std::string accountType, float credit){
		username_ = username;
		password_ = password;
		accountType_ = accountType;
		credit_ = credit;
		
		//This whole part basically opens the accounts file, reads each line to see 
		//If the username is taken, and then write the new account information to the
		// end of the file if it isnt
		
		/*
		// write into accounts file
		std::ifstream iAccFile;
		std::ofstream oAccFile;
		
		// open files
		iAccFile.open(accountFile);
		oAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std::string line;
			bool isThatUsernameTaken = false;
			
			// read each line of account file
			while(getline(iAccFile, line)){
				std::string info[3];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				// see if username is taken
				if(info[0] == username){
					printf("Account already exists now do something about it");
					isThatUsernameTaken = true;
				}
				
				// idk how c++ file i/o works so im assuming it just writes over each line I read with the same thing
				// NOTE: if this duplicates the account info, then delete this
				oAccFile << line << "\n";
			}
			
			
			// add new user to file
			if(!isThatUsernameTaken){
				oAccFile << username_ << " ";
				if(accountType_ == "Admin"){
					oAccFile << "AA ";
				} else if (accountType == "Buy-Standard"){
					oAccFile << "BS ";
				} else if(accountType == "Sell-Standard"){
					oAccFile << "SS ";
				} else if (accountType == "Full-Standard"){
					oAccFile << "FS ";
				} else {
					oAccFile << "ER ";
				}
				
				oAccFile << credit << " " << password_ << "\n";
			}
			
			// close files
			oAccFile.close();
			iAccFile.close();
			
		} else {
			printf("cannot find file");
		}
		*/
	}
	
	void addCredit(float amount){
		credit_ += amount;
	}
	
	
	void deleteUser(std::string userToDelete){
		
		// remove the user on account file
		// open files
		std::ifstream iAccFile;
		std::ofstream oAccFile;
		
		iAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std:: string line;
			std:: string accounts = "";
			bool accountFound = false;
			// read each line of account file
			while(std::getline(iAccFile, line)){
				
				std::string info[4];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				// 
				if(info[0] == userToDelete){
					printf("Account Found");
					accountFound = true;
				} else {
					// idk how c++ file i/o works so im assuming it just writes over each line I read with the same thing
					// NOTE: if this duplicates the account info, then delete this
					accounts += line;
					accounts += "\n";
				}
			}
			if(accountFound){
				// removes the last account that should already be stored, lowering account count to 1
				//oAccFile << "\n";
			}
			oAccFile.open(accountFile);
			oAccFile << accounts;
			// close files
			oAccFile.close();
			iAccFile.close();
			
		} else {
			printf("cannot find file");
		}
	}
	
};

struct FullStandard : User{
	
	FullStandard(std::string username, std::string password, double credit)
	: User(username, password, "Full-Standard", credit)
	{
		// intentionally left blank
	}
	
	void bid(){
		std::string itemName;
		std::string seller;
		float bidAmount;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter seller's username: ");
		std::cin >> seller;
		
		printf("Enter amount you want to bid: ");
		std::cin >> bidAmount;
		
		// create a new bid
		Bid(username_, seller, itemName, bidAmount);
	}
	
	void advertise(){
		std::string itemName;
		int duration;
		float minimumBid;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter minimum bid: ");
		std::cin >> minimumBid;
		
		printf("Enter auction duration: ");
		std::cin >> duration;
		
		// create a new advertisement
		Advertisement(itemName, username_, duration, minimumBid);
	}
	
};

struct BuyStandard : User{
	
	BuyStandard(std::string username, std::string password, double credit)
	: User(username, password, "Buy-Standard", credit)
	{
		// intentionally left blank
	}
	
	void bid(){
		std::string itemName;
		std::string seller;
		float bidAmount;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter seller's username: ");
		std::cin >> seller;
		
		printf("Enter amount you want to bid: ");
		std::cin >> bidAmount;
		
		// create a new bid
		Bid(username_, seller, itemName, bidAmount);
	}
};

struct SellStandard : User{
	
	SellStandard(std::string username, std::string password, double credit)
	: User(username, password, "Sell-Standard", credit)
	{
		// intentionally left blank
	}
	
	void advertise(){
		std::string itemName;
		int duration;
		float minimumBid;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter minimum bid: ");
		std::cin >> minimumBid;
		
		printf("Enter auction duration: ");
		std::cin >> duration;
		
		// create a new advertisement
		Advertisement(itemName, username_, duration, minimumBid);
	}
};

struct Admin : User{
	
	Admin(std::string username, std::string password, double credit)
	: User(username, password, "Admin", credit)
	{
		// intentionally left blank
	}
	
	void deleteUser(std::string userToDelete){
		std::cout << "bruh\n";
		// remove the user on account file
		// open files
		std::ifstream iAccFile;
		std::ofstream oAccFile;
		
		iAccFile.open(accountFile);
		oAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std:: string line;
			bool accountFound = false;
			// read each line of account file
			while(std::getline(iAccFile, line)){
				
				std::string info[4];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				// 
				if(info[0] == userToDelete){
					printf("Account Found");
					accountFound = true;
				} else {
					// idk how c++ file i/o works so im assuming it just writes over each line I read with the same thing
					// NOTE: if this duplicates the account info, then delete this
					oAccFile << line << "\n";
				}
			}
			if(accountFound){
				// removes the last account that should already be stored, lowering account count to 1
				oAccFile << "\n";
			}
			
			// close files
			oAccFile.close();
			iAccFile.close();
			
		} else {
			printf("cannot find file");
		}
	}
	
	void bid(){
		std::string itemName;
		std::string seller;
		float bidAmount;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter seller's username: ");
		std::cin >> seller;
		
		printf("Enter amount you want to bid: ");
		std::cin >> bidAmount;
		
		// create a new bid
		Bid(username_, seller, itemName, bidAmount);
	}
	
	void advertise(){
		std::string itemName;
		int duration;
		float minimumBid;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter minimum bid: ");
		std::cin >> minimumBid;
		
		printf("Enter auction duration: ");
		std::cin >> duration;
		
		// create a new advertisement
		Advertisement(itemName, username_, duration, minimumBid);
	}
	
	void createUser(std::string username, std::string type, double credit, std::string password){
		/*if(type == "Admin"){
			Admin(username, password, 0.0);
		} else if (type == "Buy-Standard"){
			BuyStandard(username, password, 0.0);
		} else if (type == "Sell-Standard"){
			SellStandard(username, password, 0.0);
		} else if (type == "Full-Standard"){
			FullStandard(username, password, 0.0);
		} else {
			printf("incorrect type");
		}*/
	}
	
	void refund(std::string seller, std::string buyer, float amount){
		// open files
		std::ifstream iAccFile;
		std::ofstream oAccFile;
		
		iAccFile.open(accountFile);
		oAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std::string line;

			// read each line of account file
			while(getline(iAccFile, line)){
				std::string info[3];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				// if it finds the user and seller, change their credits accordingly
				if(info[0] == seller){
					info[2] == std::to_string(std::stof(info[2]) - amount);
					oAccFile << info[0] << " " << info[1] << " " << info[2] << "\n";
				} else if (info[0] == buyer){
					info[2] == std::to_string(std::stof(info[2]) + amount);
					oAccFile << info[0] << " " << info[1] << " " << info[2] << "\n";
				} else {
					oAccFile << line << "\n";
				}
			}
			
			// close files
			oAccFile.close();
			iAccFile.close();
			
		} else {
			printf("cannot find file");
		}
	}
	
	void addCredit(float amount, std::string username){
		// open files
		std::ifstream iAccFile;
		std::ofstream oAccFile;
		
		iAccFile.open(accountFile);
		oAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std::string line;

			// read each line of account file
			while(getline(iAccFile, line)){
				std::string info[3];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				// if it finds the user, change their credits accordingly
				if(info[0] == username){
					info[2] == std::to_string(std::stof(info[2]) + amount);
					oAccFile << info[0] << " " << info[1] << " " << info[2] << "\n";
				} else {
					oAccFile << line << "\n";
				}
			}
			
			// close files
			oAccFile.close();
			iAccFile.close();
			
		} else {
			printf("cannot find file");
		}
	}
};