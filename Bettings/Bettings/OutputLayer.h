#pragma once

#include <iostream>
#include <fstream>
#include "Layer.h"
#include "Neiron.h"

class OutputLayer : public Layer {
private:
	Neiron** neirons;
	int neironsSize;
	string way = "D:\\PROGRAMS\\MyNeiron\\Bettings\\Debug\\output_weight.txt";
public:

	OutputLayer(int levelsize) {
		neironsSize = 2;
		neirons = new Neiron*[neironsSize];
		std::ifstream in(way);
		vector<double> weights;
		double tmp;
		for (int j = 0; j < neironsSize; j++) {
			for (int i = 0; i < levelsize; i++) {
				in >> tmp;
				weights.push_back(tmp);
			}
			
			neirons[j] = new Neiron(weights);
			weights.clear();
		}
		in.close();
	}

	vector<double> Lerning(vector<double> changes) {
		vector<vector<double> > tmp;
		for (int i = 0; i < neironsSize; i++)
			tmp.push_back(neirons[i]->Lerning(changes[i]));
		vector<double> res;
		res = tmp[0];
		for (int i = 1; i < tmp.size(); i++) {
			for (int j = 0; j < res.size(); j++)
				res[j] = res[j] + tmp[i][j];
		}
		for (int j = 0; j < res.size(); j++)
			res[j] = res[j]/tmp.size();		// находим среднее весов
		return res;
	}
	
	void SaveWeights() {
		ofstream out(way);
		vector<double> tmp;
		for (int i = 0; i < neironsSize; i++) {			
			tmp = neirons[i]->GetNewWeight();
			for (int j = 0; j < tmp.size(); j++)
				if (j+1 < tmp.size())
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

	~OutputLayer() {
		Layer::~Layer();
	}
};