#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

// ----------------------------------------------------------------------------General Helping Funcions----------------------------------------------------------------------------

// Print in Spicific Format
void printTitle(const string& title)
{
	cout << "\n\n_______________________________________\n\n";

	cout << setw(20 + title.length() / 2) << title;

	cout << "\n_______________________________________\n\n";
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

// Save to file funcion
void saveDataLineInFile(const string& line, const string& fileName)
{
	fstream file;

	file.open(fileName, ios::app | ios::out);

	if (file.is_open())
	{
		file << line << "\n";
		file.close();
	}
	else
		cout << "\n\nFile opening failed\n\n";
}

// ---------------------------------------------------------------------------------Client Segment---------------------------------------------------------------------------------

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

// Add New Client(s) Funcions
void newClient(vector<stClient>& clients)
{
	stClient client;
	string clientInLine;
	cout << "\nNew client's field: \n\n";

	do
	{
		client.AccountId = readTxt("Enter your ID: ");
		if (findClientInVecIndexById(clients, client.AccountId) != -1)
		{
			cout << "\n\nSorry, this id is already used!\n";
		}
		else
			break;
	} while (true);

	client.pin = readTxt("Enter pin: ");
	client.name = readTxt("Enter your name: ");
	client.phone = readTxt("Enter your phone number: ");
	client.accountBalance = readDouble("Enter your balance: ");

	clientInLine = clientRecordToLine(client, "//");
	saveDataLineInFile(clientInLine, "clients.txt");
	clients.push_back(client);
}

void newClients(vector<stClient>& clients)
{
	bool isCon;
	do
	{
		cout << "\n";

		newClient(clients);

		isCon = readYesNo("Data saved successfully, Do you want to add another client(Yes = 1, No = 0): ");
	} while (isCon);
}

// Display Client(s) Funcions
void displayClient(const stClient& client)
{
	cout << "\nThe following are the clients details: \n";
	cout << "\nID             : " << client.AccountId << "\n";
	cout << "Pin            : " << client.pin << "\n";
	cout << "Name           : " << client.name << "\n";
	cout << "Phone number   : " << client.phone << "\n";
	cout << "Account Balance: " << client.accountBalance << "\n";
}

void displayAllClients(const vector<stClient>& clients)
{


	cout << "\n";
	cout << "                              ";
	cout << "" << "Client list (" << clients.size() << ") client(s)";
	cout << "\n_____________________________________________________________________________________\n\n";

	cout << "| " << left << setw(16) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(30) << "Client Name";
	cout << "| " << left << setw(10) << "Phone";
	cout << "| " << left << setw(6) << "Balance" << " |";

	cout << "\n_____________________________________________________________________________________\n\n";

	for (const stClient& client : clients)
	{
		cout << "| " << left << setw(16) << client.AccountId;
		cout << "| " << left << setw(10) << client.pin;
		cout << "| " << left << setw(30) << client.name;
		cout << "| " << left << setw(10) << client.phone;
		cout << "| " << left << setw(7) << client.accountBalance << " |";

		cout << "\n";

	}
	cout << "_____________________________________________________________________________________\n";
}

void displayClientById(const vector<stClient>& clients)
{
	string id = readTxt("Enter the id of the client you want to show: ");

	int index = findClientInVecIndexById(clients, id);

	if (index != -1)
		displayClient(clients[index]);
	else
		cout << "\n\nClient with account id (" << id << ") isn't found!\n\n";
}

// Delete Client(s) Funcion
void deleteClientById(vector<stClient>& clients)
{
	string id = readTxt("Enter the id of the client you want delete: ");

	int index = findClientInVecIndexById(clients, id);

	if (index != -1)
	{

		displayClient(clients[index]);

		bool isDelete = readYesNo("\nAre you sure you want to delete this client (Yes = 1, No = 0): ");

		if (isDelete)
		{
			clients.erase(clients.begin() + index);
			saveClientsFromVecToFile(clients, "clients.txt");
			cout << "\n\nDeleted successfully!\n\n";
		}
		else
			cout << "\n\nDeletion is ignored!\n\n";
	}
	else
		cout << "\n\nClient with account id (" << id << ") isn't found!\n\n";
}

// Update Client(s) Info. Funcions and helping Funcions
void updateClientInfo(vector<stClient>& clients, int index)
{
	clients[index].pin = readTxt("Enter pin: ");
	clients[index].name = readTxt("Enter your name: ");
	clients[index].phone = readTxt("Enter your phone number: ");
	clients[index].accountBalance = readDouble("Enter your balance: ");
}

void updateClientById(vector<stClient>& clients)
{
	string id = readTxt("Enter the id of the client you want update: ");

	int index = findClientInVecIndexById(clients, id);

	if (index != -1)
	{

		displayClient(clients[index]);

		bool isUpdate = readYesNo("\nAre you sure you want to update this client (Yes = 1, No = 0): ");

		if (isUpdate)
		{
			updateClientInfo(clients, index);
			saveClientsFromVecToFile(clients, "clients.txt");
			cout << "\n\nUpdated successfully!\n\n";
		}
		else
			cout << "\n\nUpdate is ignored!\n\n";
	}
	else
		cout << "\n\nClient with account id (" << id << ") isn't found!\n\n";
}

// Balance Functions
double totalBalances(const vector<stClient>& clients)
{
	double total = 0;
	for (const stClient& client : clients)
		total += client.accountBalance;
	return total;
}

void displayBalances(const vector<stClient>& clients)
{
	cout << "\n";
	cout << "                              ";
	cout << "" << "Client list (" << clients.size() << ") client(s)";
	cout << "\n_____________________________________________________________________________________\n\n";

	cout << "| " << left << setw(16) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(21) << "Balance" << " |";

	cout << "\n_____________________________________________________________________________________\n\n";

	for (const stClient& client : clients)
	{
		cout << "| " << left << setw(16) << client.AccountId;
		cout << "| " << left << setw(40) << client.name;
		cout << "| " << left << setw(21) << client.accountBalance << " |";

		cout << "\n";

	}
	cout << "_____________________________________________________________________________________\n";

	cout << "\n" << setw(43) << "Total balances = " << totalBalances(clients);
}

// Transactions Funcions
void deposit(vector<stClient>& clients)
{
	printTitle("Deposit Screen");

	string id = readTxt("Enter the id to diposit: ");

	int index = findClientInVecIndexById(clients, id);
	double depositN;

	if (index != -1)
	{

		displayClient(clients[index]);

		depositN = readDouble("\nPlease, enter the amount of deposit: ");
		bool isPerform = readYesNo("\nAre you sure you want to perform this transaction (Yes = 1, No = 0): ");

		if (isPerform)
		{
			clients[index].accountBalance += depositN;
			saveClientsFromVecToFile(clients, "clients.txt");
			cout << "\n\nTransaction is performed successfully!\n\n";
		}
		else
			cout << "\n\nTransaction is ignored!\n\n";
	}
	else
		cout << "\n\nClient with account id (" << id << ") isn't found!\n\n";
}

void withdraw(vector<stClient>& clients)
{
	printTitle("Withdraw Screen");

	string id = readTxt("Enter the id to withdraw: ");

	int index = findClientInVecIndexById(clients, id);
	double withdrawD;

	if (index != -1)
	{
		displayClient(clients[index]);

		do
		{
			withdrawD = readDouble("\nPlease, enter the amount of withdraw: ");

			if (withdrawD > clients[index].accountBalance || withdrawD < 0)
				cout << "\n\nAmount is negative or exceeds the balance, you can withdraw up to : " << clients[index].accountBalance;
			else
				break;
		} while (true);

		bool isPerform = readYesNo("\nAre you sure you want to perform this transaction (Yes = 1, No = 0): ");

		if (isPerform)
		{
			clients[index].accountBalance -= withdrawD;
			saveClientsFromVecToFile(clients, "clients.txt");
			cout << "\n\nTransaction is performed successfully!\n\n";
		}
		else
			cout << "\n\nTransaction is ignored!\n\n";
	}
	else
		cout << "\n\nClient with account id (" << id << ") isn't found!\n\n";
}

void printTransMenu()
{
	cout << "================================================\n";
	cout << setw(28) << "Transactions Menu Screen";
	cout << "\n================================================";
	cout << "\n\t" << "[1] Deposit.";
	cout << "\n\t" << "[2] Withdraw.";
	cout << "\n\t" << "[3] Total Balances.";
	cout << "\n\t" << "[4] Main Menu.";
	cout << "\n================================================";
	cout << "\nChoose what do you want to do (1 , 4): ";
}

void transControl(vector<stClient>& clients)
{
	while (true)
	{
		printTransMenu();
		unsigned short choice = readInt("Choice: ", 1, 4);
		system("cls");
		switch (choice)
		{
		case 1:
			deposit(clients);
			break;

		case 2:
			withdraw(clients);
			break;

		case 3:
			displayBalances(clients);
			break;

		case 4:
			return;
		}


		cout << "\n\nPress any key to go back to the transaction menu...";
		system("pause>0");
		system("cls");
	}
}

// ----------------------------------------------------------------------------------User Segment----------------------------------------------------------------------------------

// User Info.
struct stUser
{
	string userName, password;
	short permissions = 0;
};

// Authentication Functions
bool isCorrectPass(const stUser& user, const string& password)
{
	return user.password == password;
}

// Permissions Functions
void grantPermissionsToUser(short& permissions)
{
	bool isFull = readYesNo("Do you want to give full access? (yes=1, no=0): ");

	if (isFull) { permissions = -1; return; }

	permissions = 0;
	bool answer;

	cout << "\n\nDo you want to give access to (yes=1, no=0):";

	answer = readYesNo("\nShow Client List: ");
	permissions += answer * 1;

	answer = readYesNo("\nAdd New Client: ");
	permissions += answer * 2;

	answer = readYesNo("\nDelete Client: ");
	permissions += answer * 4;

	answer = readYesNo("\nUpdate Client: ");
	permissions += answer * 8;

	answer = readYesNo("\nFind Client: ");
	permissions += answer * 16;

	answer = readYesNo("\nTransactions: ");
	permissions += answer * 32;

	answer = readYesNo("\nManage Users: ");
	permissions += answer * 64;
}

bool isUserHasThisPermission(short permissions, short requirdPermissionNum)
{
	return (permissions == -1) || (permissions & (1 << (requirdPermissionNum - 1))) || (requirdPermissionNum == 8);
}

void displayAccessDenied()
{
	cout << "\n\n_______________________________________________\n\n";

	cout << "Access Denied,\n";
	cout << "you don't have permission to do this action,\n";
	cout << "Please, contact your admin.";

	cout << "\n_______________________________________________\n\n";

	cout << "\n\nPress any key to go back...";
	system("pause>0");
}

// Line and Record Convertions
string userRecordToLine(const stUser& user, const string& sepa)
{
	return user.userName + sepa + user.password + sepa + to_string(user.permissions);
}

stUser userLineToRecord(string line, const string& sepa)
{
	stUser user;

	user.userName = line.substr(0, line.find(sepa));
	line = line.substr(line.find(sepa) + sepa.length());

	user.password = line.substr(0, line.find(sepa));
	line = line.substr(line.find(sepa) + sepa.length());

	user.permissions = stoi(line.substr(0));

	return user;
}

// Save and Load to/from "Users" File Functions
void saveUsersFromVecToFile(const vector<stUser>& users, const string& fileName)
{
	fstream file;

	file.open(fileName, ios::out);

	if (file.is_open())
	{
		for (const stUser& user : users)
			file << userRecordToLine(user, "//") << "\n";
	}
	else
	{
		cout << "\n\nFile opening failed\n\n";
	}
	file.close();
}

vector<stUser> loadUsersToVec(const string& fileName)
{

	fstream in;
	string userInLine;
	stUser user;
	vector<stUser> users;

	in.open(fileName, ios::in);

	if (in.is_open())
	{
		while (getline(in, userInLine))
		{
			user = userLineToRecord(userInLine, "//");
			users.push_back(user);
		}
	}

	in.close();

	return users;
}

// Search for a User
int findUserInVecIndexByUsername(const vector<stUser>& users, const string& userName)
{
	for (int i = 0; i < users.size(); ++i)
	{
		if (users[i].userName == userName)
			return i;
	}
	return -1;
}

// Add New user(s) Funcions and helping Funcions
bool isUsernameUsed(const vector<stUser>& users, const string& userName)
{
	for (const stUser& user : users)
		if (userName == user.userName)
			return 1;
	return 0;
}

void newUser(vector<stUser>& users)
{
	stUser user;
	string userInLine;
	cout << "\nNew user's field: \n\n";

	do
	{
		user.userName = readTxt("Enter a username: ");
		if (findUserInVecIndexByUsername(users, user.userName) != -1)
		{
			cout << "\n\nSorry, this username is already used!\n";
		}
		else
			break;
	} while (true);

	user.password = readTxt("Enter a password: ");

	grantPermissionsToUser(user.permissions);

	userInLine = userRecordToLine(user, "//");
	saveDataLineInFile(userInLine, "Users.txt");
	users.push_back(user);
}

void newUsers(vector<stUser>& users)
{
	bool isCon;
	do
	{
		cout << "\n";
		newUser(users);

		isCon = readYesNo("\nData saved successfully, Do you want to add another user (Yes = 1, No = 0): ");
	} while (isCon);
}

// Display User(s) Funcions
void displayUser(const stUser& user)
{
	cout << "\nThe following are the user's details:\n\n";
	cout << "UserName             : " << user.userName << "\n";
	cout << "Password             : " << user.password << "\n";
	cout << "Permissions          : " << user.permissions << "\n";
}

void displayAllUsers(const vector<stUser>& users)
{


	cout << "\n";
	cout << "                              ";
	cout << "" << "Users list (" << users.size() << ") user(s)";
	cout << "\n_____________________________________________________________________________________\n\n";

	cout << "| " << left << setw(16) << "Username";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(30) << "Permissions";

	cout << "\n_____________________________________________________________________________________\n\n";

	for (const stUser& user : users)
	{
		cout << "| " << left << setw(16) << user.userName;
		cout << "| " << left << setw(10) << user.password;
		cout << "| " << left << setw(30) << user.permissions;

		cout << "\n";
	}
	cout << "_____________________________________________________________________________________\n";
}

void displayUserByUsername(const vector<stUser>& users)
{
	string username = readTxt("Enter the username of the user you want to show: ");

	int index = findUserInVecIndexByUsername(users, username);

	if (index != -1)
		displayUser(users[index]);
	else
		cout << "\n\nUser with username (" << username << ") isn't found!\n\n";
}

// Delete User(s) Funcion
void deleteUserByUsername(vector<stUser>& users, const stUser& currentUser, bool& backToLogin)
{
	string username = readTxt("Enter the username of the user you want delete: ");

	if (username == "admin")
	{
		cout << "\n===You can never delete the admin!===";
		return;
	}

	int index = findUserInVecIndexByUsername(users, username);

	if (index != -1)
	{

		displayUser(users[index]);

		bool isDelete = readYesNo("\nAre you sure you want to delete this user (Yes = 1, No = 0): ");

		if (isDelete)
		{
			if (users[index].userName == currentUser.userName)
				backToLogin = 1;
			users.erase(users.begin() + index);
			saveUsersFromVecToFile(users, "Users.txt");
			cout << "\n\nDeleted successfully!\n\n";
		}
		else
			cout << "\n\nDeletion is ignored!\n\n";
	}
	else
		cout << "\n\nUser with username (" << username << ") isn't found!\n\n";
}

// Update User(s) Info. Funcions and helping Funcions
void updateUserInfo(vector<stUser>& users, int index)
{
	users[index].password = readTxt("Enter a password: ");
	if (users[index].userName != "admin")
		grantPermissionsToUser(users[index].permissions);
}

void updateUserByUsername(vector<stUser>& users)
{
	string username = readTxt("Enter the username of the user you want update: ");

	int index = findUserInVecIndexByUsername(users, username);

	if (index != -1)
	{

		displayUser(users[index]);

		bool isUpdate = readYesNo("\nAre you sure you want to update this user (Yes = 1, No = 0): ");

		if (isUpdate)
		{
			updateUserInfo(users, index);
			saveUsersFromVecToFile(users, "Users.txt");
			cout << "\n\nUpdated successfully!\n\n";
		}
		else
			cout << "\n\nUpdate is ignored!\n\n";
	}
	else
		cout << "\n\nUser with account username (" << username << ") isn't found!\n\n";
}

// ---------------------------------------------------------------------------------Control Segment---------------------------------------------------------------------------------

// Manage Users Menu
void displayManageUsersMenu()
{
	cout << "================================================\n";
	cout << setw(38) << "Manage Users Menu Screen";
	cout << "\n================================================";
	cout << "\n\t" << "[1] List Users.";
	cout << "\n\t" << "[2] Add New User.";
	cout << "\n\t" << "[3] Delete User.";
	cout << "\n\t" << "[4] Update User.";
	cout << "\n\t" << "[5] Find User.";
	cout << "\n\t" << "[6] Main Menu.";
	cout << "\n================================================";
	cout << "\nChoose what do you want to do (1 , 6): ";
}

void manageUsersMenuControl(vector<stUser>& users, const stUser& currentUser, bool& backToLogin)
{
	while (true)
	{
		system("cls");
		displayManageUsersMenu();

		unsigned short choice = readInt("Choice: ", 1, 6);
		system("cls");

		switch (choice)
		{
		case 1:
			displayAllUsers(users);
			break;

		case 2:
			newUsers(users);
			break;

		case 3:
			deleteUserByUsername(users, currentUser, backToLogin);
			break;

		case 4:
			updateUserByUsername(users);
			break;

		case 5:
			displayUserByUsername(users);
			break;

		case 6:
			return;
		}
		if (backToLogin)
			return;
		
		cout << "\n\nPress any key to go back...";
		system("pause>0");
	}
}

// Main Menu
void displayMainMenu()
{
	cout << "================================================\n";
	cout << setw(32) << "Main Menu Screen";
	cout << "\n================================================";
	cout << "\n\t" << "[1] Show Clients List.";
	cout << "\n\t" << "[2] Add New Client.";
	cout << "\n\t" << "[3] Delete Client.";
	cout << "\n\t" << "[4] Update Client's Info.";
	cout << "\n\t" << "[5] Find Client.";
	cout << "\n\t" << "[6] Transactions.";
	cout << "\n\t" << "[7] Manage Users.";
	cout << "\n\t" << "[8] Logout.";
	cout << "\n================================================";
	cout << "\nChoose what do you want to do (1 , 8): ";
}

void menuControl(const stUser& currentUser, vector<stUser>& users)
{
	vector<stClient> clients = loadClientsToVec("clients.txt");
	bool backToLogin = false;
	while (true)
	{
		system("cls");
		displayMainMenu();
		unsigned short choice = readInt("Choice: ", 1, 8);
		system("cls");

		if (!isUserHasThisPermission(currentUser.permissions, choice))
		{
			displayAccessDenied();
			continue;
		}

		switch (choice)
		{
		case 1:
			displayAllClients(clients);
			break;

		case 2:
			newClients(clients);
			break;

		case 3:
			deleteClientById(clients);
			break;

		case 4:
			updateClientById(clients);
			break;

		case 5:
			displayClientById(clients);
			break;

		case 6:
			transControl(clients);
			break;

		case 7:
			manageUsersMenuControl(users, currentUser,backToLogin);
			break;

		case 8:
			return;
		}
		if (backToLogin)
			return;

		cout << "\n\nPress any key to go back...";
		system("pause>0");
		system("cls");
	}
}

// Login
void loginControl()
{
	vector<stUser> users = loadUsersToVec("Users.txt");
	string userName, password;

	while (true)
	{
		system("cls");
		printTitle("Login");

		userName = readTxt("Enter Username: ");
		password = readTxt("Enter Password: ");

		system("cls");
		printTitle("Login");

		int userIndex = findUserInVecIndexByUsername(users, userName);
		if (userIndex == -1 || !isCorrectPass(users[userIndex], password))
		{
			cout << "\nInvalid Username/Password.";
			cout << "\n\nPress any key to go back...";
			system("pause>0");
		}
		else
		{
			menuControl(users[userIndex], users);
		}
	}
}

int main()
{
	loginControl();
	return 0;
}