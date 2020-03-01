#include <fstream>
//#include <iostream>
#include <cstdlib>
//#include <cstdio>
//#include <iostream>
#include <string.h>
const char* accountFile = "accounts.txt";
const char* tempFile = "temp.txt";

// Copies information from temporary file to the main file
void updateFile(std::string fileToUpdate, std::string temporaryFile){
	std::ifstream iFile;
	std::ofstream oFile;
	
	// open input file
	iFile.open(temporaryFile);
	if(iFile.is_open()){
		
		oFile.open(fileToUpdate);
		if(oFile.is_open()){
			std::string line;
			
			while(std::getline(iFile, line)){
				oFile << line << "\n";
			}
			
			oFile.close();
		} else {
			printf("ERROR: Input file not opened\n");
		}
		
		iFile.close();
	} else {
		printf("ERROR: Input file not opened\n");
	}
}
float round2Places(float var) 
{ 
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 

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
	}
	
	virtual ~User() = default;
	
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
	
	void createUser(std::string username, std::string type, double credit, std::string password){ printf("ERROR: No permission to use createUser");}
	
};

struct FullStandard : User{
	
	FullStandard(std::string username, std::string password, double credit)
	: User(username, password, "full-standard", credit)
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
	: User(username, password, "buy-standard", credit)
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
	: User(username, password, "sell-standard", credit)
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
	: User(username, password, "admin", credit)
	{
		// intentionally left blank
	}
	
	void deleteUser(std::string userToDelete){
		// remove the user on account file
		
		//check if input is valid
		if (userToDelete == username_){
			std::cout << "ERROR: Cannot delete the current user\n";
			return;
		}
		
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
					printf("User deleted\n");
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
			else{
				std::cout << "ERROR: That user does not exist\n";
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
	
	void createUser(std::string username, std::string type, float credit, std::string password){
		
		//check if input is valid
		if (username.length() > 15){
			std::cout << "ERROR: Username must be less than or equal to 15 characters\n";
			return;
		}
		if (credit <= 999999 && credit >= 0){
			std::cout << "ERROR: Credit must be between 0 and 999,999\n";
			return;
		}
		
		std::ifstream iAccFile;
		std::ofstream oTempFile;
		
		iAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std::string line;
			bool isUsernameTaken = false;
			
			// Checks to see if username is taken
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
				
				if(info[0] == username){
					isUsernameTaken = true;
				}
			}
			iAccFile.close();
			// if username isnt taken, then add it to account file
			if(!isUsernameTaken){
				iAccFile.open(accountFile);
				if(iAccFile.is_open()){
					
					oTempFile.open(tempFile);
					if(oTempFile.is_open()){
						// copying original account info
						while(std::getline(iAccFile, line)){
							oTempFile << line << "\n";
						}
						
						if(type == "admin"){
							oTempFile << username << " AA " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else if(type == "full-standard"){
							oTempFile << username << " FS " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else if(type == "buy-standard"){
							oTempFile << username << " BS " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else if(type == "sell-standard"){
							oTempFile << username << " SS " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else {
							printf("ERROR: Account type must be admin, buy-standard, or sell-standard\n");
						}
					} else {
						printf("ERROR: Temp file not opened \n");
					}
				}
			} else {
				printf("ERROR: Username already taken");
			}
		} else {
			printf("ERROR: Account file not opened\n");
		}
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
		
		//check if action is valid
		if (amount >= 1000){
			std::cout << "ERROR: amount entered is greater than the maximum allowed\n";
			return;
		}
		if (amount <= 0){
			std::cout << "ERROR: amount entered is not greater than 0\n";
			return;
		}
		
		// open files
		std::ifstream iAccFile;
		std::ofstream oTempFile;
		
		iAccFile.close();
		iAccFile.open(accountFile);
		oTempFile.open(tempFile);
		bool accFound = false;
		
		if(iAccFile.is_open()){
			std::string line;

			// read each line of account file
			while(getline(iAccFile, line)){
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
				
				// if it finds the user, change their credits accordingly
				if(info[0] == username){
					float newCredit = (std::stof(info[2]) + amount);
					oTempFile << info[0] << " " << info[1] << " " << round2Places(newCredit) << " " << info[3] << "\n";
					accFound = true;
					std::cout << "Amount Added\nUser Balance Readjusted\n";
				} 
				else {
					oTempFile << line << "\n";
				}
			}
			
			if (!accFound){
				std::cout << "ERROR: that user does not exist\n";
			}
			
			// close files
			oTempFile.close();
			iAccFile.close();
			
			updateFile(accountFile, tempFile);
			
		} else {
			printf("cannot find file");
		}
	}
};