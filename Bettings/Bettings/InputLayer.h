#pragma once

#include "Layer.h"
// ¬ходной класс, не содержит нейроном, нужен дл€ передачи данных на следующие слои
class InputLayer : public Layer {
public:

	InputLayer() {}

	vector<double> GetResultVector(vector<double> result) {
		return result;
	}

	void Learning() {};

	~InputLayer() {
		Layer::~Layer();
	}
};