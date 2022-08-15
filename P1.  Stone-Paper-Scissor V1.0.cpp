#include <iostream>

int GenerateRandomNumberInRange(int from, int to) {
	return rand() % (to - from + 1) + from; 
}

/* INPUT */
int ReadRoundsNumber() {
	int Rounds = 0; 

	do {
		std::cout << "Please enter the number of rounds from 1 to 10: "; 
		std::cin >> Rounds;
	} while (Rounds <= 0 || Rounds > 10);

	return Rounds;
}
int ReadPlayerChoice() {
	int PlayerChoice = 0; 

	do {
		std::cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissor? ";
		std::cin >> PlayerChoice; 
	} while (PlayerChoice <= 0 || PlayerChoice > 3); 

	return PlayerChoice; 
}
int ReadComputerChoice() {
	return GenerateRandomNumberInRange(1, 3); 
}

/* OUTPUT */
void PrintRoundStats(int PlayerChoice, int ComputerChoice, int RoundWinner) {
	if (PlayerChoice == 1) {
		std::cout << "Player Choice: Stone\n";
	}
	else if (PlayerChoice == 2) {
		std::cout << "Player Choice: Paper\n";
	}
	else if (PlayerChoice == 3) {
		std::cout << "Player Choice: Scissor\n";
	}

	if (ComputerChoice == 1) {
		std::cout << "Computer Choice: Stone\n";
	}
	else if (ComputerChoice == 2) {
		std::cout << "Computer Choice: Paper\n";
	}
	else if (ComputerChoice == 3) {
		std::cout << "Computer Choice: Scissor\n";
	}

	if (RoundWinner == 1) {
		std::cout << "Round Winner    : [Player 1]\n";
	}
	else if (RoundWinner == 2) {
		std::cout << "Round Winner    : [Computer]\n";
	}
	else if (RoundWinner == 3) {
		std::cout << "Round Winner    : [No Winner]\n";
	}
}

void PrintGameStats(int GameRounds, int PlayerWinTimes, int ComputerWinTimes, int DrawTimes) {
	std::cout << "\n\n________________________________________________________\n\n" <<
		"                 +++ G a m e O v e r +++              " <<
		"\n\n________________________________________________________\n\n";

	std::cout << "\n_____________________[Game Results]_____________________\n\n";

	std::cout << "Game Rounds        : " << GameRounds << "\n";
	std::cout << "Player won times   : " << PlayerWinTimes << "\n";
	std::cout << "Computer won times : " << ComputerWinTimes << "\n";
	std::cout << "Draw times         : " << DrawTimes << "\n";

	if (PlayerWinTimes > ComputerWinTimes) {
		std::cout << "Final Winner       : Player\n";
	}
	else if (ComputerWinTimes > PlayerWinTimes) {
		std::cout << "Final Winner       : Computer\n";
	}
	else {
		std::cout << "Final Winner       : No Winner\n";
	}

	std::cout << "________________________________________________________\n\n";
}

/* PROCESS */
void PlayGame() {
	int RoundWinner = 0; // Player = 1 , Computer = 2, Draw = 3 
	int RoundNumber = 0;
	int PlayerChoice = 0;
	int ComputerChoice = 0; 
	

	char PlayGame = 'Y';

	do {
		RoundNumber = ReadRoundsNumber();
		int PlayerWins = 0;
		int ComputerWins = 0;
		int DrawTimes = 0; 
	
		for (int i = 1; i <= RoundNumber; i++) {
			std::cout << "\nRound [" << i << "] begins:\n\n";
			PlayerChoice = ReadPlayerChoice();
			ComputerChoice = ReadComputerChoice();
		
			std::cout << "\n___________Round [" << i << "]___________\n\n";

			if (PlayerChoice == ComputerChoice) {
				RoundWinner = 3;
				DrawTimes++;
				system("Color 6F");
				PrintRoundStats(PlayerChoice, ComputerChoice, RoundWinner);
				std::cout << "_______________________________\n\n";

			} else if (PlayerChoice == 2 && ComputerChoice == 1 || PlayerChoice == 1 && ComputerChoice == 3 || PlayerChoice == 3 && ComputerChoice == 2) {
				RoundWinner = 1; 
				PlayerWins++;
				system("Color 2F");
				PrintRoundStats(PlayerChoice, ComputerChoice, RoundWinner);
				std::cout << "_______________________________\n\n";
			}
			else {
				RoundWinner = 2;
				ComputerWins++;
				system("Color 4F");
				PrintRoundStats(PlayerChoice, ComputerChoice, RoundWinner);
				std::cout << "_______________________________\n\n";
			}
		}

		PrintGameStats(RoundNumber, PlayerWins, ComputerWins, DrawTimes); 

		std::cout << "Do you want to play again? [Y/N]\n";
		std::cin >> PlayGame;
		std::cout << "\n";
	} while (PlayGame == 'Y' || PlayGame == 'y');

}


int main() {
	srand((unsigned)time(NULL)); 

	PlayGame();
}