#include "AccountManager.h"
#include <fstream>
#include <sstream>
#include <string>

AccountManager::~AccountManager()
{
	if (currentAccount)
	{
		delete currentAccount;
		currentAccount = nullptr;
	}
}

AccountManager::AccountManager(const std::string& path) : path_to_accounts(path), currentAccount(nullptr)
{
	if (path_to_accounts.empty())
	{
		std::cerr << "Path to accounts file cannot be empty." << std::endl;
		throw std::invalid_argument("Path to accounts file cannot be empty.");
	}
}

void AccountManager::login(const std::string& username, const std::string& password)
{
	// File format: username,password,VIP,assetPath
	// VIP is 0 for non-VIP and 1 for VIP accounts
	std::ifstream file(path_to_accounts);
	if (!file.is_open())
	{
		std::cerr << "Could not open accounts file: " << path_to_accounts << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string fileUsername, filePassword, vipStatus, assetPath;
		std::getline(iss, fileUsername, ',');
		std::getline(iss, filePassword, ',');
		std::getline(iss, vipStatus, ',');
		std::getline(iss, assetPath);
		if (fileUsername == username)
		{
			if (filePassword == password)
			{
				// Login successful
				if (currentAccount)
				{
					delete currentAccount; // Clean up previous account if exists
				}
				currentAccount = (vipStatus == "1" ? new VIPAccount : new Account);
				currentAccount->username = fileUsername;
				currentAccount->password = filePassword;
				currentAccount->assetPath = assetPath;
				std::cout << "Login successful for user: " << username << std::endl;
			}
			else
			{
				std::cout << "Incorrect password for user: " << username << std::endl;
			}
		}
		
	}
}

void AccountManager::logout()
{
	if (currentAccount)
	{
		delete currentAccount;
		currentAccount = nullptr;
		std::cout << "Logged out successfully." << std::endl;
	}
	else
	{
		std::cout << "No user is currently logged in." << std::endl;
	}
}

void AccountManager::registerAccount(const std::string& username, const std::string& password, bool VIP)
{
	if (username.empty() || password.empty())
	{
		std::cout << "Username and password cannot be empty." << std::endl;
		return;
	}
	if (password.length() < 8 || password.find(' ') != std::string::npos)
	{
		std::cout << "Password must be at least 8 characters long and cannot contain spaces." << std::endl;
		return;
	}
	
	// Check if username already exists
	std::ifstream readFile(path_to_accounts);
	if (readFile.is_open())
	{
		std::string line;
		while (std::getline(readFile, line))
		{
			std::istringstream iss(line);
			std::string existingUsername;
			std::getline(iss, existingUsername, ',');
			if (existingUsername == username)
			{
				std::cout << "Username already exists: " << username << std::endl;
				readFile.close();
				return;
			}
		}
		readFile.close();
	}
	
	std::ofstream file(path_to_accounts, std::ios::app);
	if (!file.is_open())
	{
		std::cerr << "Could not open accounts file for writing: " << path_to_accounts << std::endl;
		return;
	}
	std::string assetPath = "assets/" + username + ".txt"; // Default asset path
	file << "\n" << username << "," << password << "," << (VIP ? "1" : "0") << "," << assetPath;
	file.close();
	std::cout << "Account registered successfully for user: " << username << std::endl;
}

std::string AccountManager::getAssetPath() const
{
	return (currentAccount ? currentAccount->assetPath : std::string("assets/default.txt"));
}