#pragma once

#include <iostream>
#include <fstream>
#include "Layer.h"
#include "Neiron.h"

class HiddenLayer : public Layer {
private:
	Neiron** neirons;
	int neironsSize;
	string _way;
	int _LastLevelSize;
	bool ISspesical;
	vector<double> output;
public:

	HiddenLayer(int levelsize ,string way, bool spesialHL = false) {
		neironsSize = 4;
		_way = way;
		_LastLevelSize = levelsize;
		ISspesical = spesialHL;
		ReadWeights();		// считать веса
	}
	// считать веса, из файлика считывает текущие рабочие веса 
	void ReadWeights() {
		if (neirons != nullptr) delete[] neirons;
		neirons = new Neiron*[neironsSize];
		std::ifstream in(_way);
		vector<double> weights;
		double tmp;
		for (int j = 0; j < neironsSize; j++) {
			for (int i = 0; i < _LastLevelSize; i++) {
				in >> tmp;
				weights.push_back(tmp);
			}
			if (ISspesical && j > 1)
				neirons[j] = new Neiron(weights, special);
			else neirons[j] = new Neiron(weights);
			weights.clear();
		}
		in.close();
	}
	
	vector<double> GetReturnVector(vector<vector<double> > vvd) {
		vector<double> res;
		double summ = 0.0;
		for (int i = 0; i < vvd[0].size(); i++) {
			for (int j = 0; j < vvd.size(); j++)
				summ += vvd[j][i];
			res.push_back(summ);
			summ = 0.0;
		}
		return res;
	}

	vector<double> Lerning(vector<double> changes) {
		vector<vector<double> > result;
		for (int i = 0; i < changes.size();i++)
			result.push_back(neirons[i]->Lerning(changes[i], output));
		return GetReturnVector(result);
	}

	void SaveWeights() {
		ofstream out(_way);
		vector<double> tmp;
		for (int i = 0; i < neironsSize; i++) {
			tmp = neirons[i]->GetWeight();
			for (int j = 0; j < tmp.size(); j++)
				if (j + 1 < tmp.size())
					out << tmp[j] << " ";
				else out << tmp[j];
			out << endl;
		}
		out.close();
	}

	void SSaveWeights() {
		ofstream out(_way + ".txt");
		vector<double> tmp;
		for (int i = 0; i < neironsSize; i++) {
			tmp = neirons[i]->GetWeight();
			for (int j = 0; j < tmp.size(); j++)
				if (j + 1 < tmp.size())
					out << tmp[j] << " ";
				else out << tmp[j];
			out << endl;
		}
		out.close();
	}

	void ChangeWeights() {
		for (int i = 0; i < neironsSize; i++)
			neirons[i]->ChangeWeights();
	}

	vector<double> GetResultVector(vector<double> result) {
		output = result;
		_result.clear();
		for (int i = 0; i < neironsSize; i++)
			_result.push_back(neirons[i]->ActivationFunction(result));
		return _result;
	}

	~HiddenLayer() {
		Layer::~Layer();
	}
};