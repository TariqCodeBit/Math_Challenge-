#include <iostream>
#include <cstdlib>
using namespace std;
/*
  Requirements:                         Math Game

			-Ask For How Many Questions Do You Want To Answer ?.
			-Ask User Enter Questions Level Do You Want [1] Easy ,[2] Med , [3] Hard , [4] Mix ? .
			-Ask User Enter Operation Type [1] Add ,[2] Sub ,[3] Mul ,[4] Div ,[5] Mix ? .
			-Show The Results With Each Questions  .
	        -If The User Didn't Win The Question a Bill , and Screen Red "4F" .
	        -If User Won The Question Show Green Screen "2F" .
	        -After All Questions  Print The Results ..
	        - Then Ask The User If s/he Want To Play Again ? Y / N 

	//("Thank You")
	// I love .......................
			

*/

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType{Add = 1, Sub = 2, Mult = 3, Div = 4 , MixOP = 5 };
string GetOpTypeSymbol(enOperationType opType) {
	switch (opType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType:: Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	
	default:
		return "Mix";
	}
}
string GetQuestioLevelText(enQuestionsLevel QuestionLevel) {
	string ArrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return ArrQuestionLevelText[QuestionLevel - 1];

}
int RandomNumber(int From, int To) {
	int Number = 0;
	Number = rand() % (To - From + 1) + From;
	return Number;
}
void SetScreenColor(bool Right) {
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}
short ReadHowManyQuestions() {
	short How_Many = 0;
	do
	{
		cout << "How Many Questions Do You Want To Answer 1 to 10 ? ";
		cin >> How_Many;

	} while (How_Many < 1 || How_Many >=  10);
return How_Many;
}
enQuestionsLevel ReadQuestionsLevel() {
	short QuestionsLevel = 0;
	do {
		cout << "Enter Questions Level [1] Easy,[2] Med, [3] Hard , [4] Mix ? ";
		cin >> QuestionsLevel;
    }while (QuestionsLevel < 1 || QuestionsLevel > 4);
return enQuestionsLevel(QuestionsLevel);
}
enOperationType ReadOpType() {
	short OpType;
	do {
		cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

return enOperationType(OpType);
}


struct stQuestion {
	int Number_One = 0;
	int Number_Tow = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;

};
struct stQuizz {
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;

};
int SimpleCalculator(int Numberone, int NumberTow, enOperationType OPType) {
	switch (OPType)
	{
	case enOperationType::Add:
		return Numberone + NumberTow;

	case enOperationType::Sub:
		return Numberone - NumberTow;

	case enOperationType::Mult:
		return Numberone * NumberTow;

	case enOperationType::Div:
		return Numberone / NumberTow;

	
	default:
		return Numberone + NumberTow;
	}
}
enOperationType GetRandomOperationType() {
	int Operation = RandomNumber(1, 4);
	return (enOperationType)Operation;
}
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType) {
	stQuestion Question;
	if (QuestionLevel == enQuestionsLevel::Mix) {

		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (OpType == enOperationType::MixOP) {
		OpType = GetRandomOperationType();
	}
	Question.OperationType = OpType;
	switch (QuestionLevel) {
	     case enQuestionsLevel::EasyLevel:
			 Question.Number_One = RandomNumber(1, 10);
			 Question.Number_Tow = RandomNumber(1, 10);

			 Question.CorrectAnswer = SimpleCalculator(Question.Number_One, Question.Number_Tow, Question.OperationType);
			 Question.QuestionLevel = QuestionLevel;
			 return Question;

		 case enQuestionsLevel::MedLevel:
			 Question.Number_One = RandomNumber(10, 50);
			 Question.Number_Tow = RandomNumber(10, 50);

			 Question.CorrectAnswer = SimpleCalculator(Question.Number_One, Question.Number_Tow, Question.OperationType);
			 Question.QuestionLevel = QuestionLevel;
			 return Question;

		 case enQuestionsLevel::HardLevel:
			 Question.Number_One = RandomNumber(50, 100);
			 Question.Number_Tow = RandomNumber(50, 100);

			 Question.CorrectAnswer = SimpleCalculator(Question.Number_One, Question.Number_Tow, Question.OperationType);
			 Question.QuestionLevel = QuestionLevel;
			 return Question;

	}
	return Question;
}
void GeneratQuizzQuestions(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);

	}
}
int ReadQuestionAnswer() {
	int Answer = 0;
	cin >> Answer;
	return Answer;
}
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number_One << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number_Tow << endl;
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
		cout << "\n_____________" << endl;
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Worng Answer :-( \n";
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else {
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndcorrectQuestionListAnswers(stQuizz& Quizz) {
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}
string GetFinalResultsText(bool Pass) {
	return (Pass) ? "PASS :-)" : "Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz) {
	cout << "\n";
	cout << "____________________________\n\n";
	cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n___________________________\n\n";

	cout << "Number Of Questions    : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level         : " << GetQuestioLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType                 : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";
}
void PlayMath_Game() {
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();
	GeneratQuizzQuestions(Quizz);
	AskAndcorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);

}
void Reset_Screen() {
	system("cls");
	system("color 0F");
}
void StartGame() {
	char Ask_PlayAgain = 'Y';
	do
	{
		Reset_Screen();
		PlayMath_Game();
		cout << endl << "Do You Want To Play Again? Y/N ?";
		cin >> Ask_PlayAgain;

	} while (Ask_PlayAgain =='Y'|| Ask_PlayAgain == 'y');
}

int main() {
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}