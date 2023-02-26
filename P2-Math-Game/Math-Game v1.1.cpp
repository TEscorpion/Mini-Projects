#include <iostream>

enum enQuestionLevel{Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType{Add = 1, Sub = 2, Mul = 3, Div = 4, OpMix = 5};

struct stQuestion
{
	enQuestionLevel QuestionLevel;
	char QuestionOpType; 
	float Num1 = 0;
	float Num2 = 0; 
	float QuestionAnswer;
	float UserAnswer = 0; 
};

struct stQuiz
{
	int QuestionsNumber = 0;
	enQuestionLevel QuestionsLevel; 
	enOperationType OpType;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
	bool FinalResult; 
};

int GenerateRandomNumberInRange(int From, int To)
{
	return rand() % (To - From + 1) + From; 
}

int ReadNumber(std::string Msg)
{
	int Number; 

	std::cout << Msg; 
	std::cin >> Number;

	return Number;
}

enQuestionLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;

	do
	{
		std::cout << "\nEnter Questions Level [1]: Easy, [2]: Med, [3]: Hard, [4]: Mix? ";
		std::cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel; 
}

enOperationType ReadOperationsType()
{
	short OpType = 0;

	do
	{

		std::cout << "Enter Operation Type [1]: Add, [2]: Sub, [3]: Mul, [4]: Div, [5] Mix? "; 
		std::cin >> OpType; 

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType; 
}

enQuestionLevel GetQuestionLevel(enQuestionLevel QuizLevel)
{
	switch (QuizLevel)
	{
	case Easy:
		return enQuestionLevel::Easy;
		break;
	case Med:
		return enQuestionLevel::Med;
		break;
	case Hard:
		return enQuestionLevel::Hard;
		break;
	case Mix:
		return (enQuestionLevel)GenerateRandomNumberInRange(1, 3); 
		break;
	default:
		return enQuestionLevel::Easy;
		break;
	}

}

char GetQuestionOpType(enOperationType QuizOpType)
{
	char OpArr[4] = { '+', '-', '*', '/' };

	switch (QuizOpType)
	{
	case Add:
		return '+';
		break; 
	case Sub:
		return '-';
		break;
	case Mul:
		return '*';
		break;
	case Div:
		return '/';
		break;
	case OpMix:
		return OpArr[GenerateRandomNumberInRange(1,4)-1];
		break;
	default:
		return '+';
		break;
	}
}

float ReadQuestionNumber(enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case Easy:
		return (float)GenerateRandomNumberInRange(1, 10);
	case Med:
		return (float)GenerateRandomNumberInRange(10, 100);
	case Hard:
		return (float)GenerateRandomNumberInRange(100, 1000);
	default:
		return (float)GenerateRandomNumberInRange(1, 10);
		break;
	}
}

float GetQuestionAnswer(float Num1, float Num2, char OpType)
{
	switch (OpType)
	{
	case '+':
		return Num1 + Num2; 
	case '-':
		return Num1 - Num2;
	case '*':
		return Num1 * Num2;
	case '/':
		return Num1 / Num2;
	default:
		return Num1 + Num2;
		break;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuizLevel, enOperationType QuizOpType)
{
	stQuestion Question;

	Question.QuestionLevel = GetQuestionLevel(QuizLevel);
	Question.QuestionOpType = GetQuestionOpType(QuizOpType);
	Question.Num1 = ReadQuestionNumber(Question.QuestionLevel);
	Question.Num2 = ReadQuestionNumber(Question.QuestionLevel); 
	Question.QuestionAnswer = GetQuestionAnswer(Question.Num1, Question.Num2, Question.QuestionOpType); 

	return Question;
}

void ShowQuestion(stQuestion Question)
{
	std::cout << "\n";
	std::cout << Question.Num1 << "\n";
	std::cout << Question.Num2 << " " << Question.QuestionOpType << "\n";
	std::cout << "__________\n";
}

float ReadUserAnswer()
{
	float Answer; 
	std::cin >> Answer;

	return Answer;
}

bool CheckUserAnswer(float QuestionAnswer, float UserAnswer)
{
	if (QuestionAnswer == UserAnswer)
	{
		return true;
	}
	else
	{
		return false; 
	}
}

void ShowQuestionResult(float QuestionAnswer, float UserAnswer)
{
	if (QuestionAnswer == UserAnswer)
	{
		system("color 2F");
		std::cout << "Right Answer :-)\n"; 
	}
	else
	{
		system("color 4F");
		std::cout << "\aWrong Answer :-(\n";
		std::cout << "The right answer is: " << QuestionAnswer << "\n"; 
	}
}

bool GetFinalResult(int RightAnswers, int WrongAnswers)
{
	if (RightAnswers >= WrongAnswers)
	{
		return true; 
	}
	else
	{
		return false; 
	}
}

stQuiz StartQuiz(int QuestionsNumber)
{
	stQuiz Quiz; 
	stQuestion Question;

	Quiz.QuestionsNumber = QuestionsNumber; 
	Quiz.QuestionsLevel = ReadQuestionsLevel();
	Quiz.OpType = ReadOperationsType();


	for (int i = 1; i <= QuestionsNumber; i++)
	{
		std::cout << "\nQuestion [" << i << "/" << QuestionsNumber << "]\n";
		Question = GenerateQuestion(Quiz.QuestionsLevel, Quiz.OpType);
		ShowQuestion(Question); 
		Question.UserAnswer = ReadUserAnswer();

		if (CheckUserAnswer(Question.QuestionAnswer, Question.UserAnswer)) 
		{
			Quiz.NumberOfRightAnswers++;
		}
		else
		{
			Quiz.NumberOfWrongAnswers++; 
		}

		ShowQuestionResult(Question.QuestionAnswer, Question.UserAnswer); 
	}

	Quiz.FinalResult = GetFinalResult(Quiz.NumberOfRightAnswers, Quiz.NumberOfWrongAnswers);

	return Quiz; 
}

void ShowQuizFinalResult(bool QuizResult)
{
	std::cout << "\n\n______________________________\n\n";
	if (QuizResult == true)
	{
		system("color 2F");
		std::cout << "Final Results is PASS :-)\n";
	}
	else
	{
		system("color 4F");
		std::cout << "Final Results is FAIL :-(\n";
	}
	std::cout << "______________________________\n\n";
}

std::string GetQuizLevelName(enQuestionLevel QuizLevel)
{
	switch (QuizLevel)
	{
	case Easy:
		return "Easy";
		break;
	case Med:
		return "Med";
		break;
	case Hard:
		return "Hard";
		break;
	case Mix:
		return "Mix";
		break;
	default:
		return "Easy"; 
		break;
	}
}

std::string GetQuizOpTypeName(enOperationType QuizOpType)
{
	switch (QuizOpType)
	{
	case Add:
		return "+";
		break;
	case Sub:
		return "-";
		break;
	case Mul:
		return "*";
		break;
	case Div:
		return "/";
		break;
	case OpMix:
		return "Mix";
		break;
	default:
		return "Add";
		break;
	}
}

void ShowQuizResult(stQuiz Quiz)
{
	std::cout << "Number of Questions    : " << Quiz.QuestionsNumber << "\n";
	std::cout << "Questions Level        : " << GetQuizLevelName(Quiz.QuestionsLevel) << "\n";
	std::cout << "Operations Type        : " << GetQuizOpTypeName(Quiz.OpType) << "\n";
	std::cout << "Number of Right Answers: " << Quiz.NumberOfRightAnswers << "\n";
	std::cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << "\n"; 
	std::cout << "______________________________\n\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	int QuestionsNumber;
	stQuiz Quiz; 

	do
	{
		ResetScreen();
		 
		QuestionsNumber = ReadNumber("How many questions do you want to answer? ");
		Quiz = StartQuiz(QuestionsNumber);

		ShowQuizFinalResult(Quiz.FinalResult);
		ShowQuizResult(Quiz);

		std::cout << "Do you want to play again? [Y/N]? ";
		std::cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}