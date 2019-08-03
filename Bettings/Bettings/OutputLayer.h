#pragma once

#include <iostream>
#include <fstream>
#include "Layer.h"
#include "Neiron.h"

class OutputLayer : public Layer {
private:
	Neiron** neirons;
	int neironsSize;
	string way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\output_weight.txt";
	int _LastLevelSize;
public:

	OutputLayer(int levelsize) {
		neironsSize = 2;
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

	vector<double> Lerning(double changes) {
		ReadWeights();
		//cout << "\n From OL\n" << changes ;
		return neirons[0]->Lerning(changes);
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