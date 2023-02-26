#include <iostream>

enum enPlayers {Player = 1, Computer = 2};
enum enChoices {Paper = 1, Stone = 2, Scissor = 3};
enum enWinner {wPlayer = 1, wComputer = 2, Draw = 3};


struct stRound
{
	int RoundNumber;
	enChoices PlayerChoice;
	enChoices ComputerChoice; 
	enWinner RoundWinner;
};

struct stGameResults
{
	int GameRounds = 0;
	int PlayerWinTimes = 0;
	int ComputerWinTimes = 0;
	int DrawTimes = 0;
	enWinner FinalWinner;
};


int ReadRoundsNumber()
{
	int RoundsNumber;

	std::cout << "Please enter the number of rounds: ";
	std::cin >> RoundsNumber;

	return RoundsNumber;
}
int GenerateRandomNumberInRange(int From, int To)
{
	return rand() % (To - From + 1) + From; 
}

std::string GetWinnerName(enWinner Winner)
{
	if (Winner == enWinner::wPlayer)
	{
		return "[Player]"; 
	}
	else if (Winner == enWinner::wComputer)
	{
		return "[Computer]";
	}
	else
	{
		return "[No Winner]"; 
	}
}
std::string GetChoiceName(enChoices Choice)
{
	if (Choice == enChoices::Paper)
	{
		return "Paper";
	}
	else if (Choice == enChoices::Stone)
	{
		return "Stone";
	}
	else
	{
		return "Scissor"; 
	}
}

enWinner WhoIsRoundWinner(enChoices PlayerChoice, enChoices ComputerChoice)
{
	if (PlayerChoice == enChoices::Paper && ComputerChoice == enChoices::Stone)
	{
		return enWinner::wPlayer;
	}
	else if (PlayerChoice == enChoices::Stone && ComputerChoice == enChoices::Scissor)
	{
		return enWinner::wPlayer;
	}
	else if (PlayerChoice == enChoices::Scissor && ComputerChoice == enChoices::Paper)
	{
		return enWinner::wPlayer;
	}
	else if (PlayerChoice == ComputerChoice)
	{
		return enWinner::Draw;
	}
	else
	{
		return enWinner::wComputer; 
	}
}

enWinner WhoIsGameWinner(int PlayerWinTimes, int ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
	{
		return enWinner::wPlayer;
	}
	else if (ComputerWinTimes > PlayerWinTimes)
	{
		return enWinner::wComputer; 
	}
	else
	{
		return enWinner::Draw; 
	}
}

void StartRound(stRound &RoundResults, int RoundNumber, stGameResults &GameResults)
{
	int PlayerChoice;
	int ComputerChoice; 
	std::cout << "\nRound [" << RoundNumber << "] begins:\n"; 

	std::cout << "\nPlease enter your choice: [1]:Paper, [2]:Stone, [3]:Scissors? ";
	std::cin >> PlayerChoice; 

	ComputerChoice = GenerateRandomNumberInRange(1, 3); 

	enWinner RoundWinner = WhoIsRoundWinner((enChoices)PlayerChoice, (enChoices)ComputerChoice);

	RoundResults.RoundNumber = RoundNumber;
	RoundResults.PlayerChoice = (enChoices)PlayerChoice; 
	RoundResults.ComputerChoice = (enChoices)ComputerChoice;
	RoundResults.RoundWinner = RoundWinner; 

	if (RoundWinner == enWinner::wPlayer)
	{
		GameResults.PlayerWinTimes++;
	}
	else if (RoundWinner == enWinner::wComputer)
	{
		GameResults.ComputerWinTimes++;
	}
	else
	{
		GameResults.DrawTimes++; 
	}
}

void ScreenColor(enWinner Winner)
{
	if (Winner == enWinner::wPlayer)
	{
		system("color 2F");
	}
	else if (Winner == enWinner::wComputer)
	{
		std::cout << "\a";
		system("color 4F");
	}
	else
	{
		system("color 6F");
	}
}

void ShowRoundResults(stRound RoundResults, int RoundNumber)
{
	ScreenColor(RoundResults.RoundWinner);
	std::cout << "\n__________Round [" << RoundNumber << "]__________\n\n";
	std::cout << "Player choice  : " << GetChoiceName(RoundResults.PlayerChoice) << "\n";
	std::cout << "Computer choice: " << GetChoiceName(RoundResults.ComputerChoice) << "\n";
	std::cout << "Round winner   : " << GetWinnerName(RoundResults.RoundWinner); 
	std::cout << "\n______________________________\n";
}

void ShowGameResults(stGameResults GameResults)
{
	ScreenColor(GameResults.FinalWinner);
	std::cout << "\t\t____________________________________________________________\n\n";
	std::cout << "\t\t                    +++ G a m e  O v e r +++                \n";
	std::cout << "\t\t____________________________________________________________\n\n";

	std::cout << "\t\t______________________ [Game Results] ______________________\n\n";
	std::cout << "\t\tGame rounds       : " << GameResults.GameRounds << "\n";
	std::cout << "\t\tPlayer won times  : " << GameResults.PlayerWinTimes << "\n"; 
	std::cout << "\t\tComputer won times: " << GameResults.ComputerWinTimes << "\n";
	std::cout << "\t\tDraw times        : " << GameResults.DrawTimes << "\n";
	std::cout << "\t\tFinal Winner      : " << GetWinnerName(GameResults.FinalWinner) << "\n";
	std::cout << "\t\t____________________________________________________________\n\n";
}

void PlayGame(int RoundsNumber)
{
	stRound RoundResults;
	stGameResults GameResults; 

	for (int i = 1; i <= RoundsNumber; i++)
	{
		StartRound(RoundResults, i, GameResults);
		ShowRoundResults(RoundResults, i);
		std::cout << "\n\n"; 
	}

	GameResults.GameRounds = RoundsNumber;
	GameResults.FinalWinner = WhoIsGameWinner(GameResults.PlayerWinTimes, GameResults.ComputerWinTimes);

	ShowGameResults(GameResults);
}

void ResetScreen()
{
	system("color 0F");
	system("cls");
}

void StartGame()
{
	char PlayAgain = 'Y';
	int RoundsNumber; 

	do
	{
		ResetScreen();
		
		RoundsNumber = ReadRoundsNumber(); 
		
		PlayGame(RoundsNumber);

		std::cout << "Do you want to play again? [Y/N]? ";
		std::cin >> PlayAgain; 
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}