#pragma once

#include "Neiron.h"

// Общий класс, от него наследуются другие
class Layer {
protected:
	vector<double> _result;
public:
	virtual vector<double> GetResultVector() { return _result; };
	virtual void Lerning() {};	
};