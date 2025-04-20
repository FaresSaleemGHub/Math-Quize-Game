#include <iostream>
#include<cstdlib>
#include <chrono>
#include <thread>

using namespace std;

enum enQuestionLenvel { Easy = 1, Miduim = 2, Hard = 3, Mix = 4 };
enum enQuestionType { Add = 1, Subtract = 2, Multiply = 3, Devision = 4, MixOp = 5 };
enum enQuestionAnswerStatus { Succesful = 1, Fail = 2, Equalizer = 3 };

struct stQuizz {
	enQuestionLenvel enQL = enQuestionLenvel::Easy;
	enQuestionType enQT = enQuestionType::Add;
	enQuestionAnswerStatus enFinalResult = enQuestionAnswerStatus::Succesful;
	int NumQuestions = 0;
	int NumRightQuestions = 0;
	int NumWrongQuestions = 0;
};
struct stQuestion {
	int Num1 = 0;
	int Num2 = 0;
	float Answer = 0;
	stQuizz Quizz; // => To Access Game Information.
};

void BreakPoint() {
	int Break;
	cin >> Break;
}
void SetScreenColor(enQuestionAnswerStatus enQAS) {
	switch (enQAS)
	{
	case Succesful:
		system("color 2F");//Green
		break;
	case Fail:
		system("color 4F");//Red
		break;
	case Equalizer:
		system("color 7C");//Gray
		break;
	default:
		system("Color 3C");//Gray
	}
}
void ResetScreen() {
	system("cls");
	system("color 0F");
}
void TimerSleep(int NumSec) {
	std::this_thread::sleep_for(std::chrono::seconds(NumSec));
}
void WaitingFinalResultColorScreen() {
	TimerSleep(0.5);
	for (int i = 0; i < 30; i++) {
		SetScreenColor(enQuestionAnswerStatus(i % 4));
	}
	TimerSleep(1);
	cout << "\a";
}
void PrintDividingLine() {
	for (int i = 0; i <= 50; i++) {
		cout << "_";
	}
}
void ReadGameSettings(stQuizz& Game) {
	short QuestionLevel = 0, QuestionType = 0;
	cout << "How many Questions Do you Want? ";
	cin >> Game.NumQuestions;

	cout << "Enter Question Level => [1]:Easy. [2]:Mid. [3]:Hard. [4]:Mix. ";
	cin >> QuestionLevel;
	Game.enQL = (enQuestionLenvel)QuestionLevel;

	cout << "Enter Question Type => [1]: Add. [2]:Suptract. [3]:Multiply. [4]:Devide. [5]:Mix. ";
	cin >> QuestionType;
	Game.enQT = (enQuestionType)QuestionType;
}
short RandomNumber(int From, int To) {
	return  rand() % (To - From + 1) + From;
}
string QuestionTypeName(stQuizz Game) {
	string QuestionTypes[4] = { "+", "-", "*", "/" };
	return QuestionTypes[Game.enQT - 1];
}
string QuestionLevelName(stQuizz Game) {
	string QuestionLevels[4] = { "Easy","Mid","Hard","Mix" };
	return QuestionLevels[Game.enQL - 1];
}
void RandomQuestionType(stQuizz& Quizz) {
	Quizz.enQT = (enQuestionType)RandomNumber(1, 4);
}
void GenerateQuestionAnswer(stQuestion& Question) {
	switch (Question.Quizz.enQT)
	{
	case enQuestionType::Add:
		Question.Answer = (float)Question.Num1 + Question.Num2;
		break;
	case enQuestionType::Subtract:
		Question.Answer = (float)Question.Num1 - Question.Num2;
		break;
	case enQuestionType::Multiply:
		Question.Answer = (float)Question.Num1 * Question.Num2;
		break;
	case enQuestionType::Devision:
		Question.Answer = (float)Question.Num1 / Question.Num2;
		break;
	default:
		Question.Answer = (float)Question.Num1 + Question.Num2;
		break;
	}
}
void GenerateQuestion(stQuestion& Question) {
	switch (Question.Quizz.enQL)
	{
	case Easy:
		Question.Num1 = RandomNumber(1, 10);
		Question.Num2 = RandomNumber(1, 10);
		break;
	case Miduim:
		Question.Num1 = RandomNumber(10, 50);
		Question.Num2 = RandomNumber(10, 50);
		break;
	case Hard:
		Question.Num1 = RandomNumber(50, 100);
		Question.Num2 = RandomNumber(50, 100);
		break;
	case Mix:
		Question.Num1 = RandomNumber(1, 100);
		Question.Num2 = RandomNumber(1, 100);
		break;
	}
	GenerateQuestionAnswer(Question);
}
void GenerateQuizzQuestions(stQuizz& MainQuizz) {
	float UserAnswer = 0;
	stQuestion Question;
	Question.Quizz = MainQuizz;
	for (int i = 1; i <= Question.Quizz.NumQuestions; i++) {
		if (MainQuizz.enQT == enQuestionType::MixOp) {
			RandomQuestionType(Question.Quizz);
		}
		cout << endl;
		cout << "Question[" << i << "/" << Question.Quizz.NumQuestions << "]\n";
		GenerateQuestion(Question);
		cout << Question.Num1 << endl;
		cout << QuestionTypeName(Question.Quizz);
		cout << Question.Num2;
		cout << "\n__________________\n";
		cin >> UserAnswer;
		if (UserAnswer == Question.Answer) {
			SetScreenColor(enQuestionAnswerStatus::Succesful);
			Question.Quizz.NumRightQuestions++;
		}
		else {
			SetScreenColor(enQuestionAnswerStatus::Fail);
			Question.Quizz.NumWrongQuestions++;
		}
	}
	MainQuizz = Question.Quizz;
}
void ShowFinalResult(stQuizz Game) {
	PrintDividingLine();
	if (Game.NumRightQuestions == Game.NumWrongQuestions) {
		cout << "\nFinal Result is: Equalizer\n";
		SetScreenColor(enQuestionAnswerStatus::Equalizer);
	}
	else if (Game.NumRightQuestions < Game.NumWrongQuestions) {
		cout << "\nFinal Result is: Fail :( \n";
		SetScreenColor(enQuestionAnswerStatus::Fail);
	}
	else {
		cout << "\nFinal Result is: successful :) \n";
		SetScreenColor(enQuestionAnswerStatus::Succesful);
	}
	PrintDividingLine();
	cout << endl;
	cout << "Number of questions: " << Game.NumQuestions << endl;
	cout << "Question Level: " << QuestionLevelName(Game) << endl;
	cout << "Operation Type: " << QuestionTypeName(Game) << endl;
	cout << "Number of Right Answers: " << Game.NumRightQuestions << endl;
	cout << "Number of Wrong Answers: " << Game.NumWrongQuestions << endl;
	PrintDividingLine();
	cout << endl;
}
void StartGame() {
	char PlayAgain = 'Y';
	do {
		stQuizz Game;
		ResetScreen();
		ReadGameSettings(Game);
		cout << endl;
		GenerateQuizzQuestions(Game);
		WaitingFinalResultColorScreen();
		ShowFinalResult(Game);
		cout << "Do you want to play again? [Y]:Yes. [N]:No. ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}
