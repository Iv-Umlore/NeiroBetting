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
	Network() {
		IL = new InputLayer();
		HL = new HiddenLayer*[2];
		string way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\first_weight.txt";	
		HL[0] = new HiddenLayer(10, way);
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\second_weight.txt";
		HL[1] = new HiddenLayer(4, way);
		OL = new OutputLayer(4);
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
	void multiplication(vector<double> & tmp, double mult) {
		double summ = 0;
		for (int i = 0; i < tmp.size(); i++)
			summ += tmp[i];	// звёздочка, умножение идёт пропорционально
		for (int i = 0; i < tmp.size(); i++) {
			tmp[i] = tmp[i] * (tmp[i] / summ) * mult;
		}
	}
	// Обучение.
	void VangaLerning(vector<double> test, double correctValue) {
		cout << endl << "Good Result: " << correctValue << endl;
		Vanga(test);	// Прогоняем тест
		double learningspeed = 0.2;
		double Error = someRes[0] - correctValue;		// считаем ошибку
		
		if (Error > 0.1 || Error < -0.1) {
			vector<double> change;
			change.push_back(-learningspeed * Error);			// ???
			change.push_back(-learningspeed * Error);			// ???
			change = OL->Lerning(change);				// Выполняем обучение
			multiplication(change, -learningspeed * Error);
			change = HL[1]->Lerning(change);			// Выполняем обучение
			multiplication(change, -learningspeed * Error);
			change = HL[0]->Lerning(change);			// Выполняем обучение

			Vanga(test);							// прогоняем ещё раз, проверяем, уменьшилась ли ошибка

			if (Error > 0) {
				if (someRes[0] - correctValue < Error) {
					cout << "Change weight" << endl;
					OL->SaveWeights();
					HL[0]->SaveWeights();
					HL[1]->SaveWeights();
				}
			}
			else 
				if (someRes[0] - correctValue > Error) {
					cout << "Change weight" << endl;
					OL->SaveWeights();
					HL[0]->SaveWeights();
					HL[1]->SaveWeights();
				}
		}
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
