#pragma once

#define _FirstWeight_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\first_weight.txt"
#define _SecondWeight_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\second_weight.txt"
#define _OutputWeight_ "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Debug\\output_weight.txt"

#include "Neiron.h"

// Общий класс, от него наследуются другие
class Layer {
protected:
	vector<double> _result;
public:
	virtual vector<double> GetResultVector() { return _result; };
	virtual void Lerning() {};	
};