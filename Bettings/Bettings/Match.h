#pragma once

#include <fstream>

double GetMatchRate(int balls1, int balls2) {
	double startValue = 1;	// попытка сделать мат.последовательность с пределом 0,5
	double startResult = 0.5;	// Ну или почти 0,5
	int denominator = 8;		// На это число делится startValue

	if (balls1 == balls2) {
		startResult += 0.02 * (balls1 + 0.5);
		return startResult;
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
// Представляет собой матч. Содержит результаты 5 предыдущих игр обеих команд.
class Match {
public:
	vector<double> lastResults;
	double CorrectResult;		// доп.параметр, необходим при тестировании
	Match() {};
	Match(ifstream & in) {
		int firstball, secondball;
		//cout << "Introduced accounts of the last 5 matches of the team 1" << endl;
		for (int i = 0; i < 5; i++) {
			in >> firstball >> secondball;
			//cout << firstball << " " << secondball << endl;
			lastResults.push_back(GetMatchRate(firstball, secondball));
		}

		//cout << "Introduced accounts of the last 5 matches of the team 2" << endl;
		for (int i = 0; i < 5; i++) {
			in >> firstball >> secondball;
			//cout << firstball << " " << secondball << endl;
			lastResults.push_back(GetMatchRate(firstball, secondball));
		}
		//in.close();
		/*for (int i = 0; i < 10; i++)
			cout << "Nubmer of parameter: " << i << " Result - " << lastResults[i] << endl;*/
	}

	void SetMatchResult(int balls1, int balls2) {
		CorrectResult = GetMatchRate(balls1, balls2);
	}

};