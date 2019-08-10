#pragma once

#include "InputLayer.h"
#include "OutputLayer.h"
#include "HiddenLayer.h"
#include "Match.h"

// Необходимо допиливать 100%
void ShowResult(vector<double> vect) {
	cout << vect[0] << " Risk: " << vect[1] << endl;
}
// Нейросеть
class Network {
private:
	InputLayer* IL;		// Входной слой
	OutputLayer* OL;	// Выходной слой
	HiddenLayer** HL;	// Массив внутренних слоёв
	vector<double> someRes;
	
public:
	int goodValue;
	int numberofErrors;
	int tests;
	const bool isSingle = false;

	Network() {
		IL = new InputLayer();
		HL = new HiddenLayer*[2];
		string way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\first_weight.txt";	
		HL[0] = new HiddenLayer(10, way);
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\second_weight.txt";
		HL[1] = new HiddenLayer(4, way);
		OL = new OutputLayer(4);
		numberofErrors = 0;			// tests in [-0.3, 0.3]
		goodValue = 0;				// tests in [-0.4, 0.4]
		tests = 0;					// tests out [-0.1 , 0.1]
	}
	// Подсчёт результатов
	void Vanga(vector<double> LastMatchResults) {
				
		someRes = IL->GetResultVector(LastMatchResults);
		someRes = HL[0]->GetResultVector(someRes);	
		someRes = HL[1]->GetResultVector(someRes);		
		someRes = OL->GetResultVector(someRes);

		if (isSingle) ShowResult(someRes);
	}
		
	double CountTheError(Match matches) {
		
		double Error;
			
			Vanga(matches.lastResults);			// Прогоняем тест

			Error = someRes[0] - matches.CorrectResult;
			
			if (isSingle) {
				cout << endl << "Good Result: " << matches.CorrectResult << endl;
				cout << "This Error: " << Error << endl;
			}
			
		return Error;		
	}

	void VangaLerning(vector<Match> AllMathes, int numberOfHellCircle) {
		
		int bestCircle = 0;
		int circle = 0;
		double firstError;
		double secondError;
		double ERROR = 0.0;
		double bestErr = 0.0;
		double lastSumm = 100000.0;
		ReadWeight();
		for (int i = 0; i < AllMathes.size(); i++) {
			firstError = CountTheError(AllMathes[i]);
			ERROR += firstError * firstError;
		}
		cout << endl << ERROR << endl << endl;
		double summM = 0.0;
		double summ = 0.0;

		for (int k = 0; k < numberOfHellCircle; k++) {			
				
				tests = 0;
				
				for (int i = 0; i < AllMathes.size(); i++) {

					firstError = CountTheError(AllMathes[i]);
					Learning(firstError);				
					
				}
				for (int i = 0; i < AllMathes.size(); i++) {
					secondError = CountTheError(AllMathes[i]);
					if (secondError * secondError <= 0.01) tests++;
					summ += secondError * secondError;
				}

				if (summ < ERROR) {	
					cout << summ << endl;
					ERROR = summ;
					bestCircle = k;
					SaveWeight();
					circle = 0;
					
				}
				if (lastSumm > summ) {
					bestErr = summ;
					circle = 0;
				}
				else circle++;
				lastSumm = summ;

				if (circle > 500) {
					srand(time(0));
					ReadWeight();
					cout <<"Best res: " << bestErr << " Last value: " << lastSumm << " Circle: " << k << endl;
					lastSumm = 250.0;
					ChangeWeights();
					circle = 0;
				}

				summ = 0;
			}
		cout << lastSumm << endl;
		cout << "BEST OF THE BEST\n\n\n";
		cout << "ERROR: " << ERROR << " On Circle: " << bestCircle << endl;
		cout << "Total good tests: " << tests << endl;
	}

	// Обучение.
	void Learning(double error) {

		vector<double> tmp = OL->Lerning(error);	// Выполняем обучение
		tmp = HL[1]->Lerning(tmp);					// Выполняем обучение
		tmp = HL[0]->Lerning(tmp);					// Выполняем обучение
	}

	void ReadWeight() {
		OL->ReadWeights();
		HL[1]->ReadWeights();
		HL[0]->ReadWeights();
	}
	
	void SaveWeight() {
		if (isSingle) cout << "Change weight" << endl;
		OL->SaveWeights();
		HL[0]->SaveWeights();
		HL[1]->SaveWeights();
	}

	void ChangeWeights() {
		OL->ChangeWeights();
		HL[0]->ChangeWeights();
		HL[1]->ChangeWeights();
		cout << "\nChanged!\n";
	}

	void SpecialSave() {
		OL->SSaveWeights();
		HL[0]->SSaveWeights();
		HL[1]->SSaveWeights();
	}

	double GetPrediction() {
		return someRes[0];
	}
	
	~Network() {
		IL->~InputLayer();
		delete IL;
		OL->~OutputLayer();
		delete OL;
		HL[0]->~HiddenLayer();
		HL[1]->~HiddenLayer();
		delete[] HL;
	}
};
