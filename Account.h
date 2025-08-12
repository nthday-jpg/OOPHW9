#pragma once
#include <iostream>

class Account
{
protected:
	std::string username;
	std::string password;
	std::string assetPath;

	friend class AccountManager;
public:
	virtual ~Account() = default;
};

class VIPAccount : public Account
{
public:
	virtual ~VIPAccount() = default; 
};
