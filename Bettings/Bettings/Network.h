#pragma once

#include "InputLayer.h"
#include "OutputLayer.h"
#include "HiddenLayer.h"

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

	int numberofErrors;

	Network() {
		IL = new InputLayer();
		HL = new HiddenLayer*[2];
		string way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\first_weight.txt";	
		HL[0] = new HiddenLayer(10, way);
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\second_weight.txt";
		HL[1] = new HiddenLayer(4, way);
		OL = new OutputLayer(4);
		numberofErrors = 0;
	}
	// Подсчёт результатов
	void Vanga(vector<double> LastMatchResults) {
				
		someRes = IL->GetResultVector(LastMatchResults);
		
		//PrintVector(someRes, "Vanga");		
		
		someRes = HL[0]->GetResultVector(someRes);

		//PrintVector(someRes, "Vanga");		
		
		someRes = HL[1]->GetResultVector(someRes);

		//PrintVector(someRes, "Vanga");
		
		someRes = OL->GetResultVector(someRes);

		ShowResult(someRes);
	}

	// Умножение вектора на число со звёздочкой
	void ChangeWeights(vector<double> & tmp, double mult) {
		double summ = 0;
		for (int i = 0; i < tmp.size(); i++)
			summ += tmp[i];	// звёздочка, умножение идёт пропорционально
		for (int i = 0; i < tmp.size(); i++) {
			tmp[i] = (tmp[i] / summ) * mult;			// считаю
		}
	}
	// Обучение.
	void VangaLerning(vector<double> test, double correctValue, double learningspeed = 0.01) {
		cout << endl << "Good Result: " << correctValue << endl;
		Vanga(test);	// Прогоняем тест
		double Error = someRes[0] - correctValue;		// считаем ошибку
		
		if (Error > 0.05 || Error < -0.05) {
			vector<double> change;
			change.push_back(-learningspeed * Error);			// ???
			change.push_back(-learningspeed * Error);			// ???
			change = OL->Lerning(change);				// Выполняем обучение
			//ChangeWeights(change, -learningspeed * Error);
			change = HL[1]->Lerning(change);			// Выполняем обучение
			//ChangeWeights(change, -learningspeed * Error);
			change = HL[0]->Lerning(change);			// Выполняем обучение

			Vanga(test);							// прогоняем ещё раз, проверяем, уменьшилась ли ошибка
			if (someRes[0] - correctValue < 0.3 && someRes[0] - correctValue > -0.3) numberofErrors++;
			if (Error > 0) {
				if (someRes[0] - correctValue < Error) {
					//cout << "Change weight" << endl;
					OL->SaveWeights();
					HL[0]->SaveWeights();
					HL[1]->SaveWeights();
				}
			}
			else 
				if (someRes[0] - correctValue > Error) {
					//cout << "Change weight" << endl;
					OL->SaveWeights();
					HL[0]->SaveWeights();
					HL[1]->SaveWeights();
				}
		}
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
