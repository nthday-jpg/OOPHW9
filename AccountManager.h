#pragma once
#include <string>
#include "Account.h"

class AccountManager
{
	std::string path_to_accounts;
	Account* currentAccount;
	friend class App; 
public:
	AccountManager(const std::string& path);
	~AccountManager();

	bool isLoggedIn() const { return currentAccount != nullptr; }
	void login(const std::string& username, const std::string& password);
	void logout();
	void registerAccount(const std::string& username, const std::string& password, bool VIP);
private:
	std::string getAssetPath() const;
};