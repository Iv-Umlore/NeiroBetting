#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum NeironType {classic, special};

void PrintVector(vector<double> vect, string from) {
	cout << endl <<from << ":\n";
	for (int i = 0; i < vect.size(); i++)
		cout << vect[i] << " ";
	if (vect.size() == 0) cout << "is empty";
	cout << endl;
}

class Neiron {
private:
	NeironType NT;	// NeironType
	vector<double> _weight;
public:
	Neiron(vector<double> weight, NeironType type = classic) {
		_weight = weight;
		NT = type;
	}
	// ������� ��������� (������� ��������)
	double ActivationFunction(vector<double> value) {
		double result = 0.0;
		if (NT == classic) {
			for (int i = 0; i < value.size(); i++) {
				result += value[i] * _weight[i];
			}
			return result;
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
			return result;
		}
	}
	// ��������, ���������� ���������
	vector<double> Lerning(double error) {
		vector<double> res;
		for (int i = 0; i < _weight.size(); i++) {
			_weight[i] += _weight[i] * error;		// ����������� ��� �� ������� �� ���� ������
			if (_weight[i] > 5.0) _weight[i] = 5.0;
			if (_weight[i] < -5.0) _weight[i] = -5.0;
			res.push_back(error / _weight[i]);		// ���������� ����������� ���������
		}
			
		return res;
	};

	vector<double> GetWeight() {
		return _weight;
	}

	~Neiron() {
		_weight.~vector();
	};
};