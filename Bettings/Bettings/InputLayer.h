#pragma once

#include "Layer.h"

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