#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <random>
#include <ctime>

using namespace std;

enum NeironType {classic, special};

const double learningspeed = 0.01;
const int coefficient = 5;

void PrintVector(vector<double> vect, string from) {
	cout << endl << from << ":\n";
	for (int i = 0; i < vect.size(); i++)
		cout << vect[i] << " ";
	if (vect.size() == 0) cout << "is empty";
	cout << endl;
}

class Neiron {
private:
	NeironType NT;	// NeironType
	vector<double> _weight;
	double myResult;

	double SigmaFunction(double x) {
		return 2 / (1 + exp( -coefficient * x )) - 1;
	}

	double Derivative(double x) {
		double tmp = exp(-coefficient * x);
		tmp = (2 * coefficient * tmp) / (pow((1 + tmp), 2));
		return tmp;
	}

public:
	Neiron(vector<double> weight, NeironType type = classic) {
		_weight = weight;
		NT = type;
	}
	// Функция активации (рабочий механизм)
	double ActivationFunction(vector<double> value) {
		double result = 0.0;
		if (NT == classic) {
			for (int i = 0; i < value.size(); i++) {
				result += value[i] * _weight[i];
			}
			myResult = SigmaFunction(result);
			return myResult;
		}
		else {
			vector<double> firstTeam;
			vector<double> secondTeam;
			for (int i = 0; i < value.size()/2 + 1; i++)
				firstTeam.push_back(value[i]);
			for (int i = value.size() / 2 + 1; i < value.size(); i++)
				secondTeam.push_back(value[i]);
			std::sort(firstTeam.begin(), firstTeam.end());
			std::sort(secondTeam.begin(), secondTeam.end());
			value.clear();
			for (int i = 0; i < firstTeam.size(); i++)
				value.push_back(firstTeam[i]);
			for (int i = 0; i < secondTeam.size(); i++)
				value.push_back(secondTeam[i]);
			for (int i = 0; i < value.size(); i++) {
				result += value[i] * _weight[i];
			}
			myResult = SigmaFunction(result);
			return myResult;
		}
	}
	
	// Обучение, необходима доработка
	vector<double> Lerning(double error , vector<double> output) {
		vector<double> res;
		double deltaW = Derivative(myResult) * error;
		for (int i = 0; i < _weight.size(); i++) {			
			_weight[i] -= output[i] * deltaW * learningspeed;						
			res.push_back(_weight[i] * deltaW);
		}

		return res;
	};

	void ChangeWeights() {	
		for (int i = 0; i < _weight.size(); i++)
			_weight[i] += (double)((rand() % 2001) - 1000) / 10000;
	}

	vector<double> GetWeight() {
		return _weight;
	}

	~Neiron() {
		_weight.~vector();
	};
};
