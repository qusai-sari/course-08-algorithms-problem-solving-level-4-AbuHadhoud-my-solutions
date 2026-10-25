#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

// ----------------------------------------------------------------------------General Helping Funcions----------------------------------------------------------------------------

// Display in Spicific Format
void displayTitle(const string& title)
{
	system("cls");
	cout << "\n\n=======================================================\n";
	cout << setw(28 + title.length() / 2) << title;
	cout << "\n=======================================================\n";
}

// Read funcions
string readTxt(const string& message) {
	string in;
	cout << "\n" << message;
	getline(cin >> ws, in);
	return in;
}

int readInt(const string& message, int low, int high)
{
	int num;
	cout << "\n" << message;

	do
	{
		cin >> num;
		if (num < low)
		{
			cout << "\nIt has to be more than or equals " << low << " : ";
		}
		else if (num > high)
		{
			cout << "\nIt has to be less than or equals " << high << " : ";
		}
		else if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid value: ";
		}
		else
			break;

	} while (true);

	return num;
}

double readDouble(const string& message)
{
	double num;
	cout << "\n" << message;

	do
	{
		cin >> num;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid value: ";
		}
		else
			break;

	} while (true);

	return num;
}

bool readYesNo(const string& message)
{
	bool answer;
	cout << "\n" << message;

	while (true)
	{
		cin >> answer;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid value (avaliable values -> (yes->1, no->0)): ";
		}
		else
			break;
	}
	return answer;
}

void pause(const string& message)
{
	cout << "\n\n" << message;
	system("pause>0");
}

const string clientsFile = "clients.txt";

// ---------------------------------------------------------------------------------Client Segment---------------------------------------------------------------------------------

enum menuChoices { QuikW = 1, NormalC, Deposit, CheckPalance, Logout };

// Client Info.
struct stClient
{
	string AccountId, pin, name, phone;
	double accountBalance;
};

// Line and Record Convertions
string clientRecordToLine(const stClient& client, const string& sepa)
{
	return client.AccountId + sepa + client.pin + sepa + client.name + sepa + client.phone + sepa + to_string(client.accountBalance);
}

stClient clientLineToRecord(string line, const string& sepa)
{
	stClient client;

	client.AccountId = line.substr(0, line.find(sepa));
	line = line.substr(line.find(sepa) + sepa.length());

	client.pin = line.substr(0, line.find(sepa));
	line = line.substr(line.find(sepa) + sepa.length());

	client.name = line.substr(0, line.find(sepa));
	line = line.substr(line.find(sepa) + sepa.length());

	client.phone = line.substr(0, line.find(sepa));
	line = line.substr(line.find(sepa) + sepa.length());

	client.accountBalance = stod(line);

	return client;
}

// Save and Load to/from "Clients" File Operations
void saveClientsFromVecToFile(const vector<stClient>& clients, const string& fileName)
{
	fstream file;

	file.open(fileName, ios::out);

	if (file.is_open())
	{
		for (const stClient& client : clients)
			file << clientRecordToLine(client, "//") << "\n";
	}
	else
	{
		cout << "\n\nFile opening failed\n\n";
	}
	file.close();
}

vector<stClient> loadClientsToVec(const string& fileName)
{

	fstream in;
	string clientInLine;
	stClient client;
	vector<stClient> clients;

	in.open(fileName, ios::in);

	if (in.is_open())
	{
		while (getline(in, clientInLine))
		{
			client = clientLineToRecord(clientInLine, "//");
			clients.push_back(client);
		}
	}

	in.close();

	return clients;
}

// Search for a Client
int findClientInVecIndexById(const vector<stClient>& clients, const string& id)
{
	for (int i = 0; i < clients.size(); ++i)
	{
		if (clients[i].AccountId == id)
			return i;
	}
	return -1;
}

// Withdraw and Deposit
void confirmWithdrawTrans(double& accountBalance, unsigned short withdrawAmounts, bool& isSave)
{
	bool isSure = readYesNo("\nAre you sure you want perform this transaction (yes=1, no=0): ");

	if (isSure)
	{
		accountBalance -= withdrawAmounts;
		isSave = true;
		cout << "\n\nDone Successfully. New balance is: " << accountBalance;
	}

	
	pause("Press any key to go back to main menu...");
}

void displayQuickWithdraw(const double accountBalance)
{
	displayTitle("Quick Withdraw");

	cout << "\t" << left << setw(8) << "[1] 20" << "\t" << "[2] 50";
	cout << "\n\t" << left << setw(8) << "[3] 100" << "\t" << "[4] 200";
	cout << "\n\t" << left << setw(8) << "[5] 400" << "\t" << "[6] 600";
	cout << "\n\t" << left << setw(8) << "[7] 800" << "\t" << "[8] 1000";
	cout << "\n\t" << left << setw(8) << "[9] Exit";

	cout << "\n=======================================================\n";
	cout << "Your balance is " << accountBalance;
}

void quickWithdraw(double& accountBalance, bool& isSave)
{
	unsigned short withdrawAmounts[9] = { 0, 20, 50, 100, 200, 400, 600, 800, 1000 };
	unsigned short choice;

	do
	{
		displayQuickWithdraw(accountBalance);
		choice = readInt("Choose the amount you want to withdraw (1 , 9): ", 1, 9);

		if (choice == 9) return;

		if (withdrawAmounts[choice] > accountBalance)
		{
			cout << "\n\nThe amount exceeds your balance, make another choice.";
			pause("Press any key continue...");
		}

	} while (withdrawAmounts[choice] > accountBalance);

	confirmWithdrawTrans(accountBalance, withdrawAmounts[choice], isSave);
}

void normalWithdraw(double& accountBalance, bool& isSave)
{

	int amount;
	do
	{
		displayTitle("Normal Withdraw Screen");

		amount = readInt("Enter an amount multiple of 5's: ", 0, 2000000000);
		if (amount > accountBalance)
		{
			cout << "\n\nThe amount exceeds your balance, make another choice.";
			pause("Press any key continue...");
		}

	} while (amount % 5 != 0 || amount > accountBalance);

	confirmWithdrawTrans(accountBalance, amount, isSave);
}

void deposit(double& accountBalance, bool& isSave)
{
	displayTitle("Deposit Screen");

	int amount = readInt("Enter a deposit amount: ", 1, 2000000000);

	bool isSure = readYesNo("Are you sure you want perform this transaction (yes=1, no=0):");

	if (isSure)
	{
		accountBalance += amount;
		isSave = true;
		cout << "\n\nDone successfully. New balance is: " << accountBalance;
	}

	pause("Press any key to go back to main menu...");
}

void checkBalance(const double accountBalance)
{
	displayTitle("Normal Balance Screen");
	cout << "Your balance is " << accountBalance;

	pause("Press any key to go back to main menu...");
}

// ---------------------------------------------------------------------------------Control Segment---------------------------------------------------------------------------------

// Storage Control
void storageSaveManager(const vector<stClient>& clients, bool isSave)
{
	if (isSave)
		saveClientsFromVecToFile(clients, clientsFile);
}

// Main Menu
void displayMenu()
{
	displayTitle("ATM Main Menu Screen");

	cout << "\t" << "[1] Quick Withdraw.";
	cout << "\n\t" << "[2] Normal Withdraw.";
	cout << "\n\t" << "[3] Deposit.";
	cout << "\n\t" << "[4] Check Balance.";
	cout << "\n\t" << "[5] Logout.";

	cout << "\n=======================================================";
}

void menu(vector<stClient>& clients, stClient& currentClient)
{
	while (true)
	{
		displayMenu();

		unsigned short choice = readInt("Choose what do you want to do (1 , 5): ", 1, 5);
		bool isSave = false;
		switch (choice)
		{
		case menuChoices::QuikW:
			quickWithdraw(currentClient.accountBalance, isSave);
			break;

		case menuChoices::NormalC:
			normalWithdraw(currentClient.accountBalance, isSave);
			break;

		case menuChoices::Deposit:
			deposit(currentClient.accountBalance, isSave);
			break;

		case menuChoices::CheckPalance:
			checkBalance(currentClient.accountBalance);
			break;

		case menuChoices::Logout:
			return;
		}
		storageSaveManager(clients, isSave);
	}
}

// Login
void login()
{
	vector<stClient> clients = loadClientsToVec(clientsFile);
	string accountId, pin;

	do
	{
		displayTitle("Login Screen");

		accountId = readTxt("Enter account number: ");
		pin = readTxt("Enter pin: ");

		short clientIndex = findClientInVecIndexById(clients, accountId);
		if ((clientIndex == -1) || (clients[clientIndex].pin != pin))
		{
			cout << "\nInvalaid account number/pincode!";
			pause("");
		}
		else
		{
			menu(clients, clients[clientIndex]);
		}

	} while (true);
}

int main()
{
	login();
	return 0;
}