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

	vector<double> Srednee(vector<vector<double> > that) {
		double tmp = 0.0;
		vector<double> res;
		for (int i = 0; i < that[0].size(); i++) {
			for (int j = 0; j < that.size(); j++)
				tmp += that[j][i];
			res.push_back(tmp / that.size());
			tmp = 0.0;
		}
		return res;
	}

	vector<double> Lerning(vector<double> changes) {
		ReadWeights();
		//PrintVector(changes, "Vector from HL");
		vector<vector<double> > tmp;
		for (int i = 0; i < neironsSize; i++)
			tmp.push_back(neirons[i]->Lerning(changes[i]));
		return (Srednee(tmp));
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

	vector<double> GetResultVector(vector<double> result) {
		_result.clear();
		for (int i = 0; i < neironsSize; i++)
			_result.push_back(neirons[i]->ActivationFunction(result));
		return _result;
	}

	~HiddenLayer() {
		Layer::~Layer();
	}
};