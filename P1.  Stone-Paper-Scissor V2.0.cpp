#include <iostream>

int GenerateRandomNumberInRange(int from, int to) {
	return rand() % (to - from + 1) + from; 
}

enum enGameChoice {
	Stone = 1,
	Paper = 2,
	Scissor = 3 
};

enum enWinner {
	Player = 1,
	Computer = 2,
	Draw = 3
};

struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice PlayerChoice; 
	enGameChoice ComputerChoice; 
	enWinner Winner;
	std::string WinnerName = "";
};

struct stGameResults {
	short GameRounds = 0;
	short PlayerWins = 0;
	short ComputerWins = 0;
	short Draw = 0;
	enWinner GameWinner; 
	std::string WinnerName = "";
};

short ReadRoundsNumber() {
	short RoundsNumber = 0; 

	do {
		std::cout << "Please enter how many rounds you wanna play between 1 to 10?\n";
		std::cin >> RoundsNumber;
	} while (RoundsNumber < 1 || RoundsNumber > 10);

	return RoundsNumber; 
}

enGameChoice ReadPlayerChoice() {
	short PlayerChoice = 1; 

	do {
		std::cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor?\n";
		std::cin >> PlayerChoice; 
	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameChoice)PlayerChoice; 

}

enGameChoice ReadComputerChoice() {
	short ComputerChoice = GenerateRandomNumberInRange(1, 3);
	
	return (enGameChoice)ComputerChoice; 
}

enWinner RoundWinner(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice) {
		return enWinner::Draw; 
	}

	switch (RoundInfo.PlayerChoice) {
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer; 
		}
		break; 

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor) {
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player; 
}

std::string WinnerName(enWinner Winner) {
	std::string arrWinnerName[3] = { "Player", "Computer", "No Winner" };

	return arrWinnerName[Winner - 1]; 
}

std::string ChoiceName(enGameChoice Choice) {
	std::string arrChoiceName[3] = { "Stone", "Paper", "Scissor" };

	return arrChoiceName[Choice - 1]; 
}

void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		break;
	default:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo) {
	std::cout << "\n____________Round [" << RoundInfo.RoundNumber << "]____________\n\n";
	std::cout << "Player Choice  : " << ChoiceName(RoundInfo.PlayerChoice) << "\n";
	std::cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
	std::cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	std::cout << "_________________________________\n\n";

	SetWinnerScreenColor(RoundInfo.Winner); 
}

enWinner GameWinner(short PlayerWins, short ComputerWins) {
	if (PlayerWins > ComputerWins) {
		return enWinner::Player;
	}
	else if (ComputerWins > PlayerWins) {
		return enWinner::Computer; 
	}
	else {
		return enWinner::Draw; 
	}
}

stGameResults FillGameResults(short RoundsNumber, short PlayerWins, short ComputerWins, short Draw) {
	stGameResults GameResults;

	GameResults.GameRounds = RoundsNumber;
	GameResults.PlayerWins = PlayerWins;
	GameResults.ComputerWins = ComputerWins;
	GameResults.Draw = Draw;
	GameResults.GameWinner = GameWinner(PlayerWins, ComputerWins); 
	GameResults.WinnerName = WinnerName(GameResults.GameWinner); 

	return GameResults; 
}

stGameResults PlayGame(short RoundsNumber) {
	stRoundInfo RoundInfo; 
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0; 

	for (short GameRound = 1; GameRound <= RoundsNumber; GameRound++) {
		std::cout << "\nRound [" << GameRound << "] begins:\n"; 
		RoundInfo.RoundNumber = GameRound; 
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = ReadComputerChoice();
		RoundInfo.Winner = RoundWinner(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner); 

		if (RoundInfo.Winner == enWinner::Player) {
			PlayerWinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Computer) {
			ComputerWinTimes++;
		}
		else {
			DrawTimes++; 
		}

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(RoundsNumber, PlayerWinTimes, ComputerWinTimes, DrawTimes); 
}

void ResetScreen() {
	system("cls");
	system("color 0F"); 
}

void ShowGameOverScreen() {

	std::cout << "\n\n\t\t________________________________________________________\n\n" <<
				 "\t\t               +++ G a m e O v e r +++              " <<
				 "\n\t\t________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults) {
	std::cout << "\t\t_____________________[Game Results]_____________________\n\n";

	std::cout << "\t\tGame Rounds        : " << GameResults.GameRounds << "\n";
	std::cout << "\t\tPlayer won times   : " << GameResults.PlayerWins << "\n";
	std::cout << "\t\tComputer won times : " << GameResults.ComputerWins << "\n";
	std::cout << "\t\tDraw times         : " << GameResults.Draw << "\n";
	std::cout << "\t\tFinal Winner       : " << GameResults.WinnerName << "\n";
	std::cout << "\t\t________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner); 
}

void StartGame() {
	char PlayAgain = 'Y';

	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadRoundsNumber());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults); 

		std::cout << "\n\t\t\tDo you want to play again? Y/N?";
		std::cin >> PlayAgain; 
	} while (PlayAgain == 'Y' || PlayAgain == 'y'); 
}

int main() {
	srand((unsigned)time(NULL)); 

	StartGame();
}