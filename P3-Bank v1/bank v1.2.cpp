#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

std::string FileName = "Clients.txt";

enum enMenuChoices
{
	ShowClientList = 1,
	AddNewClient,
	DeleteClient,
	UpdateClientInfo,
	FindClient,
	Transactions, 
	Exit
};

enum enTransactionsChoice
{
	enDeposit = 1,
	enWithdraw,
	enTotalBalances,
	enMainMenu
};

struct stClient
{
	std::string AccountNo;
	std::string PINcode;
	std::string Name;
	std::string Phone;
	float Salary;
	bool MarkForDelete = 0;
};

void Start();

int ReadInt(std::string Msg)
{
	int Num;

	std::cout << Msg;
	std::cin >> Num;

	return Num;
}

float ReadFloat(std::string Msg)
{
	float Num;

	std::cout << Msg;
	std::cin >> Num;

	return Num;
}

std::string ReadString(std::string Msg)
{
	std::string Str;

	std::cout << Msg;
	getline(std::cin >> std::ws, Str);

	return Str;
}

/*
stClient AddNewClient()
{
	stClient Client;

	std::cout << "Adding New Client:\n\n";

	std::cout << "Enter account number? ";
	getline(std::cin >> std::ws, Client.AccountNo);

	std::cout << "Enter account PIN code? ";
	getline(std::cin, Client.PINcode);

	std::cout << "Enter account name? ";
	getline(std::cin, Client.Name);

	std::cout << "Enter account phone? ";
	getline(std::cin, Client.Phone);

	std::cout << "Enter account salary? ";
	std::cin >> Client.Salary;

	return Client;
}
*/

stClient AddNewClientWithOutAccountNo()
{
	stClient Client;

	std::cout << "Enter account PIN code? ";
	getline(std::cin >> std::ws, Client.PINcode);

	std::cout << "Enter account name? ";
	getline(std::cin, Client.Name);

	std::cout << "Enter account phone? ";
	getline(std::cin, Client.Phone);

	std::cout << "Enter account salary? ";
	std::cin >> Client.Salary;

	return Client;
}

std::vector <std::string> SplitWordsToVector(std::string Str, std::string Separator = "#//#")
{
	std::vector <std::string> vWords;
	std::string Word = "";
	short Pos = 0;

	while ((Pos = Str.find(Separator)) != std::string::npos)
	{
		Word = Str.substr(0, Pos);

		if (Word != "")
		{
			vWords.push_back(Word);
		}

		Str.erase(0, Pos + Separator.length());
	}

	if (Str != "")
	{
		vWords.push_back(Str);
	}

	return vWords;
}

std::string ConvertRecordToLine(stClient Client, std::string Separator = "#//#")
{
	std::string Line = "";

	Line += Client.AccountNo + Separator;
	Line += Client.PINcode + Separator;
	Line += Client.Name + Separator;
	Line += Client.Phone + Separator;
	Line += std::to_string(Client.Salary);

	return Line;
}

stClient ConvertLineToRecord(std::string Line, std::string Separator = "#//#")
{
	std::vector <std::string> vWords = SplitWordsToVector(Line, Separator);
	stClient Client;

	Client.AccountNo = vWords[0];
	Client.PINcode = vWords[1];
	Client.Name = vWords[2];
	Client.Phone = vWords[3];
	Client.Salary = stof(vWords[4]);

	return Client;
}

void SaveDataFromVectorToFile(std::string FileName, std::vector <stClient> vClients)
{
	std::fstream File;
	File.open(FileName, std::ios::out);

	std::string DataLine = "";

	if (File.is_open())
	{
		for (stClient& Client : vClients)
		{
			DataLine = ConvertRecordToLine(Client);
			File << DataLine << "\n";
		}

		File.close();
	}
}

std::vector <stClient> LoadDataFromFileToVector(std::string FileName)
{
	std::vector <stClient> vClients;
	stClient Client;

	std::fstream MyFile;

	MyFile.open(FileName, std::ios::in);

	if (MyFile.is_open())
	{
		std::string Line;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

bool IsClientExistByAccountNo(std::vector <stClient> vClients, std::string AccountNo, stClient& Client)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNo == AccountNo)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

void AddingNewClients(std::vector <stClient>& vClients)
{
	std::cout << "------------------------------------------------\n";
	std::cout << "              Add New Clients Screen            \n";
	std::cout << "------------------------------------------------\n";

	char AddMore = 'Y';
	stClient Client;

	do
	{
		std::string AccountNo = ReadString("Enter Account Number? ");

		if (IsClientExistByAccountNo(vClients, AccountNo, Client))
		{
			std::cout << "\nClient with [" << AccountNo << "] already exits, ";
		}
		else
		{
			Client = AddNewClientWithOutAccountNo();
			Client.AccountNo = AccountNo;
			vClients.push_back(Client);
			SaveDataFromVectorToFile(FileName, vClients);

			vClients = LoadDataFromFileToVector(FileName);

			std::cout << "\nClient added successfully, do you want to add more clients? [Y/N]? ";
			std::cin >> AddMore;

			std::cout << "\n";
		}

	} while (AddMore == 'Y' || AddMore == 'y');
}

void ShowClient(stClient Client)
{
	std::cout << "| " << std::left << std::setw(16) << Client.AccountNo;
	std::cout << "| " << std::left << std::setw(14) << Client.PINcode;
	std::cout << "| " << std::left << std::setw(40) << Client.Name;
	std::cout << "| " << std::left << std::setw(14) << Client.Phone;
	std::cout << "| " << std::left << std::setw(10) << Client.Salary;

}

void ShowAllClients(std::vector <stClient> vClients)
{
	std::cout << "\n\t\t\t\t\tClient list (" << vClients.size() << ") Client(s).\n";
	std::cout << "_______________________________________________________________________________________________________\n\n";
	std::cout << "| " << std::left << std::setw(16) << "Account Number";
	std::cout << "| " << std::left << std::setw(14) << "Pin Code";
	std::cout << "| " << std::left << std::setw(40) << "Client Name";
	std::cout << "| " << std::left << std::setw(14) << "Phone";
	std::cout << "| " << std::left << std::setw(14) << "Balance" << "\n";
	std::cout << "_______________________________________________________________________________________________________\n\n";

	for (stClient& Client : vClients)
	{
		ShowClient(Client);
		std::cout << "\n";
	}

	std::cout << "\n";
	std::cout << "_______________________________________________________________________________________________________\n";
}

void PrintClient(stClient Client)
{
	std::cout << "\nThe followings are the client details:\n";
	std::cout << "______________________________________\n\n";
	std::cout << "Account number : " << Client.AccountNo << "\n";
	std::cout << "Pin code       : " << Client.PINcode << "\n";
	std::cout << "Name           : " << Client.Name << "\n";
	std::cout << "Phone          : " << Client.Phone << "\n";
	std::cout << "Account Balance: " << Client.Salary << "\n";
	std::cout << "______________________________________\n";
}

void SaveDataInFile(std::vector <stClient>& vClients)
{
	std::fstream File;
	File.open(FileName, std::ios::out);

	std::string DataLine = "";

	if (File.is_open())
	{
		for (stClient& Client : vClients)
		{
			if (Client.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(Client);
				File << DataLine << "\n";
			}
		}

		File.close();
	}

}

bool MarkClientForDelete(std::vector <stClient>& vClients, std::string AccountNo)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNo == AccountNo)
		{
			Client.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

bool DeleteClientByAccountNumber(std::vector <stClient>& vClients)
{
	std::cout << "------------------------------------------------\n";
	std::cout << "              Delete Client Screen            \n";
	std::cout << "------------------------------------------------\n";

	stClient Client;
	char DeleteClient = 'Y';

	std::string AccountNo = ReadString("Please enter account number? ");

	if (IsClientExistByAccountNo(vClients, AccountNo, Client))
	{
		PrintClient(Client);

		std::cout << "\n\nAre you sure you want to delete this client? [Y/N]? ";
		std::cin >> DeleteClient;

		if (DeleteClient == 'Y' || DeleteClient == 'y')
		{
			MarkClientForDelete(vClients, AccountNo);
			SaveDataInFile(vClients);

			vClients = LoadDataFromFileToVector(FileName);
			std::cout << "\n\nClient Deleted Successfully.\n";

			return true;
		}
	}
	else
	{
		std::cout << "\nClient with account number (" << AccountNo << ") is not found!\n\n";
		return false;
	}
}

bool UpdateClientByAccountNumber(std::vector <stClient>& vClients)
{
	std::cout << "------------------------------------------------\n";
	std::cout << "              Update Client Screen            \n";
	std::cout << "------------------------------------------------\n";

	stClient Client;
	char UpdateClient = 'Y';

	std::string AccountNo = ReadString("Please enter account number? ");

	if (IsClientExistByAccountNo(vClients, AccountNo, Client))
	{
		PrintClient(Client);

		std::cout << "\n\nAre you sure you want to update this client? [Y/N]? ";
		std::cin >> UpdateClient;

		if (UpdateClient == 'Y' || UpdateClient == 'y')
		{
			//MarkClientForDelete(vClients, AccountNo);
			std::cout << "\n";

			for (stClient& C : vClients)
			{
				if (C.AccountNo == AccountNo)
				{
					C = AddNewClientWithOutAccountNo();
					C.AccountNo = AccountNo;
					break;
				}
			}

			SaveDataInFile(vClients);

			vClients = LoadDataFromFileToVector(FileName);
			std::cout << "\n\nClient Updated Successfully.\n";

			return true;
		}
	}
	else
	{
		std::cout << "\nClient with account number (" << AccountNo << ") is not found!\n\n";
		return false;
	}
}

bool FindClientClientByAccountNumber(std::vector <stClient>& vClients)
{
	std::cout << "------------------------------------------------\n";
	std::cout << "              Find Client Screen            \n";
	std::cout << "------------------------------------------------\n";

	stClient Client;
	char FindClient = 'Y';

	std::string AccountNo = ReadString("Please enter account number? ");

	if (IsClientExistByAccountNo(vClients, AccountNo, Client))
	{
		PrintClient(Client);
		return true;
	}
	else
	{
		std::cout << "\nClient with account number (" << AccountNo << ") is not found!\n\n";
		return false;
	}
}

void ExitScreen()
{
	std::cout << "---------------------------------------\n";
	std::cout << "          Program Ends :-)             \n";
	std::cout << "---------------------------------------\n";
}

void GoBackToMainMenu()
{
	std::cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
}

void GoBackToTransactionsMenu()
{
	std::cout << "\n\nPress any key to go back to transactions menu...";
	system("pause>0");
}

void MainMenuScreen()
{
	system("cls");

	std::cout << "==================================================\n";
	std::cout << "                    Main Menu Screen              \n";
	std::cout << "==================================================\n";
	std::cout << "         [1] Show Clients List\n";
	std::cout << "         [2] Add New Client\n";
	std::cout << "         [3] Delete Client\n";
	std::cout << "         [4] Update Client Info\n";
	std::cout << "         [5] Find Client\n";
	std::cout << "         [6] Transactions\n";
	std::cout << "         [7] Exit\n";
	std::cout << "==================================================\n";
}

void TransactionsMenuScreen()
{
	system("cls");
	std::cout << "==================================================\n";
	std::cout << "               Transactions Menu Screen           \n";
	std::cout << "==================================================\n";
	std::cout << "         [1] Deposit\n";
	std::cout << "         [2] Withdraw\n";
	std::cout << "         [3] Total Balances\n";
	std::cout << "         [4] Main Menu\n";
	std::cout << "==================================================\n";
}

void Deposit(std::vector <stClient> &vClients)
{
	std::cout << "------------------------------------------------\n";
	std::cout << "              Deposit Screen                    \n";
	std::cout << "------------------------------------------------\n";

	std::string AccountNo;
	stClient Client;
	char DepositChoice = 'Y';
	float DepositAmount = 0; 

	do
	{
		AccountNo = ReadString("Please enter account number? ");

		if (IsClientExistByAccountNo(vClients, AccountNo, Client))
		{
			PrintClient(Client);

			std::cout << "\nPlease enter deposit amount? ";
			std::cin >> DepositAmount; 

			std::cout << "\nAre you sure you want to perform this transaction? [Y/N]? ";
			std::cin >> DepositChoice;

			if (DepositChoice == 'Y' || DepositChoice == 'y')
			{

				for (stClient& C : vClients)
				{
					if (C.AccountNo == AccountNo)
					{
						C.Salary += DepositAmount;
						break; 
					}
				}

				SaveDataInFile(vClients);

				vClients = LoadDataFromFileToVector(FileName);
				std::cout << "\n\nDeposit transaction done successfully and the total balance is  " << Client.Salary + DepositAmount << "\n";
			}
		}
		else
		{
			std::cout << "\nClient with account number (" << AccountNo << ") is not found!\n\n";
		}
	} while (!(IsClientExistByAccountNo(vClients, AccountNo, Client)));
}

void Withdraw(std::vector <stClient>& vClients)
{
	std::cout << "------------------------------------------------\n";
	std::cout << "              Withdraw Screen                    \n";
	std::cout << "------------------------------------------------\n";

	std::string AccountNo;
	stClient Client;
	char WithdrawChoice = 'Y';
	float WithdrawAmount = 0;

	do
	{
		AccountNo = ReadString("Please enter account number? ");

		if (IsClientExistByAccountNo(vClients, AccountNo, Client))
		{
			PrintClient(Client);

			std::cout << "\nPlease enter withdraw amount? ";
			std::cin >> WithdrawAmount;

			while (WithdrawAmount > Client.Salary)
			{
				std::cout << "\nAmount exceeds the balance, you can withdraw up to " << Client.Salary << "\n";
				std::cout << "Please enter another amount: ";
				std::cin >> WithdrawAmount;
			}

			std::cout << "\nAre you sure you want to perform this transaction? [Y/N]? ";
			std::cin >> WithdrawChoice;

			if (WithdrawChoice == 'Y' || WithdrawChoice == 'y')
			{

				for (stClient& C : vClients)
				{
					if (C.AccountNo == AccountNo)
					{
						C.Salary -= WithdrawAmount;
						break;
					}
				}

				SaveDataInFile(vClients);

				vClients = LoadDataFromFileToVector(FileName);
				std::cout << "\n\nWithdraw transaction done successfully and the total balance is  " << Client.Salary - WithdrawAmount << "\n";
			}
		}
		else
		{
			std::cout << "\nClient with account number (" << AccountNo << ") is not found!\n\n";
		}
	} while (!(IsClientExistByAccountNo(vClients, AccountNo, Client)));
}

void ShowClientBalance(stClient Client)
{
	std::cout << "| " << std::left << std::setw(20) << Client.AccountNo;
	std::cout << "| " << std::left << std::setw(40) << Client.Name;
	std::cout << "| " << std::left << std::setw(30) << Client.Salary;
}

void ShowTotalBalances(std::vector <stClient>& vClients)
{
	std::cout << "\n\t\t\t\t\tClient list (" << vClients.size() << ") Client(s).\n";
	std::cout << "_______________________________________________________________________________________________________\n\n";
	std::cout << "| " << std::left << std::setw(20) << "Account Number";
	std::cout << "| " << std::left << std::setw(40) << "Client Name";
	std::cout << "| " << std::left << std::setw(30) << "Balance" << "\n";
	std::cout << "_______________________________________________________________________________________________________\n\n";

	float TotalBalances = 0; 

	for (stClient& Client : vClients)
	{
		TotalBalances += Client.Salary;
		ShowClientBalance(Client);
		std::cout << "\n";
	}

	std::cout << "\n";
	std::cout << "_______________________________________________________________________________________________________\n";

	std::cout << "\n                                         Total Balances = " << TotalBalances << "\n";
}

void StartTransactions()
{
	std::vector <stClient> vClients = LoadDataFromFileToVector(FileName);
	short Choice;

	enTransactionsChoice TransactionChoice;

	do
	{
		TransactionsMenuScreen();
		std::cout << "Choose what do you want to do? [1 to 4]? ";
		std::cin >> Choice;

		TransactionChoice = (enTransactionsChoice)Choice;

		switch (TransactionChoice)
		{
		case enDeposit:
			system("cls");
			Deposit(vClients);
			GoBackToTransactionsMenu();
			break;
		case enWithdraw:
			system("cls");
			Withdraw(vClients);
			GoBackToTransactionsMenu();
			break;
		case enTotalBalances:
			system("cls");
			ShowTotalBalances(vClients);
			GoBackToTransactionsMenu();
			break;
		case enMainMenu:
			Start();
			break;
		}
	} while (Choice > 0 && Choice < 4);
}


void Start()
{

	std::vector <stClient> vClients = LoadDataFromFileToVector(FileName);
	short Choice;

	enMenuChoices enChoice;

	do
	{
		MainMenuScreen();
		std::cout << "Choose what do you want to do? [1 to 7]? ";
		std::cin >> Choice;
		enChoice = (enMenuChoices)Choice;

		switch (enChoice)
		{
		case ShowClientList:
			system("cls");
			ShowAllClients(vClients);
			GoBackToMainMenu();
			break;

		case AddNewClient:
			system("cls");
			AddingNewClients(vClients);
			GoBackToMainMenu();
			break;

		case DeleteClient:
			system("cls");
			DeleteClientByAccountNumber(vClients);
			GoBackToMainMenu();
			break;

		case UpdateClientInfo:
			system("cls");
			UpdateClientByAccountNumber(vClients);
			GoBackToMainMenu();
			break;

		case FindClient:
			system("cls");
			FindClientClientByAccountNumber(vClients);
			GoBackToMainMenu();
			break;

		case Transactions:
			system("cls");
			StartTransactions();
			break; 

		case Exit:
			system("cls");
			ExitScreen();
			break;

		default:
			system("cls");
			std::cout << "\nWrong choice, Please try again with the right one )-:\n";
		}

	} while (Choice < 7 && Choice > 0);
}


int main()
{
	Start();
}