#pragma once

#include "Neiron.h"

class Layer {
protected:
	vector<double> _result;
public:
	virtual vector<double> GetResultVector() { return _result; };
	virtual void Lerning() {};
};