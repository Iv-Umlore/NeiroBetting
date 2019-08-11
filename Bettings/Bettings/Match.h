#pragma once

#define _Russia_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Russia.txt"
#define _Asia_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Asia.txt"
#define _USA_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\USA.txt"
#define _Others_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Other.txt"
#define _MathForPrediction_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\results.txt"

#include <fstream>

double GetAlternateMatchRate(int balls1, int balls2) {
	double tmp = (balls1 - balls2);
	if (balls1 == balls2) {
		return -(balls1 * 0.01);
	}

	double SmallBalls;

	if (balls1 > balls2) {
		SmallBalls = 0.1 / (9 - (balls1 - balls2) + 1);
		return (tmp / 10) - balls2 * SmallBalls;
	}

	if (balls1 < balls2) {
		SmallBalls = 0.1 / (9 - (balls2 - balls1) + 1);
		return (tmp / 10) - balls1 * SmallBalls;;
	}

	return 0;
}

double GetMatchRate(int balls1, int balls2) {
	double startValue = 0.91;	// попытка сделать мат.последовательность с пределом 0,5
	double startResult = 0;	// Ну или почти 0,5
	int denominator = 5;		// На это число делится startValue
	double multyply = (balls1 + balls2);
	if (balls1 == balls2) {
		return (GetMatchRate(balls1, balls2 - 1) + GetMatchRate(balls1, balls2 + 1)) / 2;
	}
	while (balls1 > 0 || balls2 > 0) {
		if (balls1 > 0) {
			balls1--;
			startResult += startValue / denominator;
		}
		if (balls2 > 0) {
			balls2--;
			startResult -= startValue / denominator;
		}
		denominator++;
	}

	return startResult;
}

void PrintMatchPrediction(double answer) {
	cout << answer << endl;
	int ball1 = 0, ball2 = 0;
	double min = 1.0;
	double tmp;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			tmp = GetAlternateMatchRate(i, j);
			tmp = (answer - tmp) * (answer - tmp);
			
			if (tmp < min) {
				min = tmp;
				ball1 = i;
				ball2 = j;
			}
		}	
	cout << "I think, that score will be : " << ball1 << " : " << ball2 << endl;
}

// Представляет собой матч. Содержит результаты 5 предыдущих игр обеих команд.
class Match {
public:
	vector<double> lastResults;
	double CorrectResult;		// доп.параметр, необходим при тестировании
	Match() {};
	Match(ifstream & in) {
		int firstball, secondball;
		for (int i = 0; i < 5; i++) {
			in >> firstball >> secondball;
			lastResults.push_back(GetAlternateMatchRate(firstball, secondball));
		}

		for (int i = 0; i < 5; i++) {
			in >> firstball >> secondball;
			lastResults.push_back(GetAlternateMatchRate(firstball, secondball));
		}

	}

	void SetMatchResult(int balls1, int balls2) {
		//CorrectResult = GetMatchRate(balls1, balls2);
		CorrectResult = GetAlternateMatchRate(balls1, balls2);
	}

};

vector<Match> ReadAllMatches() {
	vector<Match> matches;
	vector<string> ways;	

	ways.push_back(_Others_);
	ways.push_back(_Asia_);
	ways.push_back(_USA_);
	ways.push_back(_Russia_);	

	ifstream in;

	int count;
	int MatchCount;
	int balls1, balls2;
	int currPos = 0;

	for (int j = 0; j < ways.size(); j++) {

		in.open(ways[j]);
		
		in >> count;
		for (int i = 0; i < count; i++) {
			matches.push_back(Match(in));
			in >> balls1 >> balls2;
			matches[currPos].SetMatchResult(balls1, balls2);
			currPos++;
		}
		in.close();
	}
	
	return matches;
}
