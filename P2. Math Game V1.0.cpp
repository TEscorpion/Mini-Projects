#include <iostream>

enum enQuestionLevel {
	Easy = 1,
	Med = 2,
	Hard = 3,
	Mix = 4
};

enum enOperationType {
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	mix = 5
};

struct stQuestion {
	int Num1 = 0; 
	int Num2 = 0;
	int Result;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	bool isRight = 1; 
};

struct stFinalResult {
	int QuestionsNumber = 0;
	std::string QuestionsLevel = "";
	std::string OperationType = "";
	int RightAnswers = 0;
	int WrongAnswers = 0;
	bool isPass = 1; 
};

int GenerateRandomNumberInRange(int From, int To) {
	return rand() % (To - From + 1) + From; 
}

char GenerateRandomOperationType() {
	int RandomOp = GenerateRandomNumberInRange(1, 4);

	switch (RandomOp)
	{
		case 1:
			return '+';
		case 2: 
			return '-';
		case 3:
			return '*';
		case 4:
			return '/';
		default:
			return '+'; 
	}
}

int ReadQuestionsNumber() {
	int QuestionsNumber = 0;

	do {
		std::cout << "How many questions do you want to answer? "; 
		std::cin >> QuestionsNumber;
	} while (QuestionsNumber < 1); 

	return QuestionsNumber; 
}

enQuestionLevel ReadQuestionLevel() {
	short QuestionLevel = 0; 

	do {
		std::cout << "Enter Questions Level: [1] Easy, [2] Med, [3] Hard, [4] Mix? ";
		std::cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4); 


	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType() {
	short OperationType = 0;

	do {
		std::cout << "Enter Operation Type: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? ";
		std::cin >> OperationType;
	} while (OperationType < 1 || OperationType > 5);


	return (enOperationType)OperationType;
}

void ShowQuestion(int Num1, int Num2, char OperationType) {
	std::cout << "\n" << Num1 << "\n" << Num2 << " " << OperationType << "\n";
	std::cout << "\n__________\n"; 
}

void GenerateQuestion(stQuestion &Question) {
	Question.Num1 = 0;
	Question.Num2 = 0; 

	switch (Question.QuestionLevel)
	{
		case enQuestionLevel::Easy:
			Question.Num1 = GenerateRandomNumberInRange(1, 9);
			Question.Num2 = GenerateRandomNumberInRange(1, 9);
			break;
		case enQuestionLevel::Med:
			Question.Num1 = GenerateRandomNumberInRange(10, 99);
			Question.Num2 = GenerateRandomNumberInRange(10, 99);
			break;
		case enQuestionLevel::Hard:
			Question.Num1 = GenerateRandomNumberInRange(100, 999);
			Question.Num2 = GenerateRandomNumberInRange(100, 999);
			break;
		default: 
			Question.Num1 = GenerateRandomNumberInRange(1, 999);
			Question.Num2 = GenerateRandomNumberInRange(1, 999);
			break;
	}

	switch (Question.OperationType)
	{
	case enOperationType::Add:
		ShowQuestion(Question.Num1, Question.Num2, '+');
		Question.Result = Question.Num1 + Question.Num2; 
		break;
	case enOperationType::Sub:
		ShowQuestion(Question.Num1, Question.Num2, '-');
		Question.Result = Question.Num1 - Question.Num2;
		break;
	case enOperationType::Mul:
		ShowQuestion(Question.Num1, Question.Num2, '*');
		Question.Result = Question.Num1 * Question.Num2;
		break;
	case enOperationType::Div:
		ShowQuestion(Question.Num1, Question.Num2, '/');
		Question.Result = Question.Num1 / Question.Num2;
		break;
	default:
		char OpType = GenerateRandomOperationType();
		ShowQuestion(Question.Num1, Question.Num2, OpType);

		switch (OpType)
		{
		case '+':
			Question.Result = Question.Num1 + Question.Num2;
			break;
		case '-':
			Question.Result = Question.Num1 - Question.Num2;
			break;
		case '*':
			Question.Result = Question.Num1 * Question.Num2;
			break;
		case '/':
			Question.Result = Question.Num1 / Question.Num2;
			break;
		
		}

		break;
	}
}

std::string GetQuestionLevelName(enQuestionLevel QuestionLevel) {
	std::string arrQuestionLevels[] = {"Easy", "Med", "Hard", "Mix"};

	return arrQuestionLevels[QuestionLevel - 1];
}

std::string GetOperationTypeName(enOperationType OpType) {
	std::string arrOpType[] = { "Add", "Sub", "Mul", "Div", "Mix"};

	return arrOpType[OpType - 1];
}

bool isPass(int RightAnswers, int WrongAnswers) {
	if (RightAnswers >= WrongAnswers) {
		return 1;
	}
	else {
		return 0; 
	}
}

stFinalResult FillFinalResult(int QuestionsNumber, std::string QuestionsLevel, std::string OperationsType, int RightAnswers, int WrongAnswers) {
	stFinalResult FinalResult;
	FinalResult.QuestionsNumber = QuestionsNumber; 
	FinalResult.QuestionsLevel = QuestionsLevel; 
	FinalResult.OperationType = OperationsType;
	FinalResult.RightAnswers = RightAnswers;
	FinalResult.WrongAnswers = WrongAnswers;
	FinalResult.isPass = isPass(RightAnswers, WrongAnswers);

	return FinalResult; 
}

void ShowFinalResult(stFinalResult FinalResult) {
	std::cout << "\n\n______________________________\n\n";
	if (FinalResult.isPass) {
		std::cout << "  Final result is PASS :-)\n";
		system("color 2F");
	}
	else {
		std::cout << "  Final result is FAIL :-)\n";
		system("color 4F");
	}
	std::cout << "\n______________________________\n\n";

	std::cout << "Number of Questions    : " << FinalResult.QuestionsNumber << "\n";
	std::cout << "Questions Level        : " << FinalResult.QuestionsLevel << "\n";
	std::cout << "Operations Type        : " << FinalResult.OperationType << "\n";
	std::cout << "Number of Right Answers: " << FinalResult.RightAnswers << "\n";
	std::cout << "Number of Wrong Answers: " << FinalResult.WrongAnswers << "\n";

	std::cout << "\n______________________________\n";
}

stFinalResult StartGame(int QuestionsNumber) {
	int RightAnswers = 0, WrongAnswers = 0, Result = 0;
 
	stQuestion Question; 
	Question.QuestionLevel = ReadQuestionLevel();
	Question.OperationType = ReadOperationType();

	std::string QuestionLevelName = GetQuestionLevelName(Question.QuestionLevel); 
	std::string OperationTypeName = GetOperationTypeName(Question.OperationType);

	for (int question = 1; question <= QuestionsNumber; question++) {
		std::cout << "\nQuestion [" << question << "/" << QuestionsNumber << "]\n";
		GenerateQuestion(Question); 
		std::cin >> Result;

		if (Result == Question.Result) {
			RightAnswers++; 
			system("color 2F");
			std::cout << "Right Answer :-)\n\n";
		}
		else {
			WrongAnswers++;
			system("color 4F");
			std::cout << "Wrong Answer :-(\n";
			std::cout << "The right answer is: " << Question.Result << "\n\n";
		}
	}

	return FillFinalResult(QuestionsNumber, QuestionLevelName, OperationTypeName, RightAnswers, WrongAnswers); 

}

void ResetScreen() {
	system("cls");
	system("color 0F"); 
}

void StartGame() {
	char PlayAgain = 'Y'; 

	do {
		ResetScreen(); 
		stFinalResult FinalResult = StartGame(ReadQuestionsNumber());
		ShowFinalResult(FinalResult);

		std::cout << "\nDo you want to play again? Y/N? ";
		std::cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
	srand((unsigned)time(NULL));

	StartGame();
}