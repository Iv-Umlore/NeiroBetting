#pragma once

#define _Russia_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Russia.txt"
#define _Asia_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Asia.txt"
#define _USA_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\USA.txt"
#define _Others_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Other.txt"
#define _MathForPrediction_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\results.txt"

#define _FirstWeight_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\first_weight.txt"
#define _SecondWeight_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\second_weight.txt"
#define _OutputWeight_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\output_weight.txt"

#include <fstream>

double GetAlternateMatchRate(int balls1, int balls2) {
	double tmp = (balls1 - balls2);
	if (balls1 == balls2) {
		return -(balls1 * 0.01);
	}

	if (balls1 > balls2) {
		return (tmp / 10) - (balls2+1) * 0.01;
	}

	if (balls1 < balls2) {
		return (tmp / 10) - (balls1+1) * 0.01;
	}

	return 0;
}

double GetMatchRate(int balls1, int balls2) {
	double startValue = 0.91;	// ������� ������� ���.������������������ � �������� 0,5
	double startResult = 0;	// �� ��� ����� 0,5
	int denominator = 5;		// �� ��� ����� ������� startValue
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

// ������������ ����� ����. �������� ���������� 5 ���������� ��� ����� ������.
class Match {
public:
	vector<double> lastResults;
	double CorrectResult;		// ���.��������, ��������� ��� ������������
	Match() {};
	Match(ifstream & in) {
		int firstball, secondball;
		for (int i = 0; i < 5; i++) {
			in >> firstball >> secondball;
			lastResults.push_back(GetMatchRate(firstball, secondball));
		}

		for (int i = 0; i < 5; i++) {
			in >> firstball >> secondball;
			lastResults.push_back(GetMatchRate(firstball, secondball));
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
	ways.push_back(_USA_);
	ways.push_back(_Asia_);
	ways.push_back(_Others_);
	ways.push_back(_Russia_);

	ifstream in;

	for (int i = 0; i < ways.size(); i++) {

		in.open(ways[i]);
		int count;
		int MatchCount;
		int balls1, balls2;
		in >> count;
		for (int i = 0; i < count; i++) {
			matches.push_back(Match(in));
			in >> balls1 >> balls2;
			matches[i].SetMatchResult(balls1, balls2);
		}
		in.close();
	}
	
	return matches;
}
