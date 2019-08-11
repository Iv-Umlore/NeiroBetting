#pragma once

#include <iostream>
#include <fstream>
#include "Layer.h"
#include "Neiron.h"

class OutputLayer : public Layer {
private:
	Neiron** neirons;
	int neironsSize;
	string way;
	int _LastLevelSize;
	vector<double> output;
public:

	OutputLayer(int levelsize, string Oway) {
		neironsSize = 2;
		way = Oway;
		_LastLevelSize = levelsize;
		ReadWeights();
	}

	void ReadWeights() {
		
			if (neirons != nullptr) delete[] neirons;
			neirons = new Neiron*[neironsSize];
			std::ifstream in(way);
			vector<double> weights;
			double tmp;
			for (int j = 0; j < neironsSize; j++) {
				for (int i = 0; i < _LastLevelSize; i++) {
					in >> tmp;
					weights.push_back(tmp);
				}

				neirons[j] = new Neiron(weights);
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

	vector<double> Lerning(double changes) {
		vector< vector<double> > result;
		result.push_back(neirons[0]->Lerning(changes, output));
		return GetReturnVector(result);
	}
	
	void SaveWeights() {
		ofstream out(way);
		vector<double> tmp;
		for (int i = 0; i < neironsSize; i++) {			
			tmp = neirons[i]->GetWeight();
			for (int j = 0; j < tmp.size(); j++)
				if (j+1 < tmp.size())
					out << tmp[j] << " ";
				else out << tmp[j];
			out << endl;
		}
		out.close();
	}
	
	void ChangeWeights() {
			neirons[0]->ChangeWeights();
	}

	vector<double> GetResultVector(vector<double> result) {
		_result.clear();
		output = result;
		for (int i = 0; i < neironsSize; i++)
			_result.push_back(neirons[i]->ActivationFunction(result));
		return _result;
	}

	~OutputLayer() {
		Layer::~Layer();
	}
};