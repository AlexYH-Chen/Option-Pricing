// american_option_function.cpp
//
// Functions implementation.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "option_data.hpp"
#include "option_function.hpp"

using namespace std;
// using namespace OptionFunction;

namespace OptionFunction{
namespace AmericanOptionFunction {

double CallPrice(double K, double sig, double r, double b, double S) {
	double tmp = b / (sig * sig);
	double y1 = 0.5 - tmp + sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * r / (sig * sig));
	return K / (y1 - 1) * pow((y1 - 1) / y1 * S / K, y1);
}

double CallPrice(const OptionData& data, double S) {
	double tmp = data.b / (data.sig * data.sig);
	double y1 = 0.5 - tmp + sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * data.r / (data.sig * data.sig));
	if (1.0 == y1) return S;
	return data.K / (y1 - 1) * pow((y1 - 1) / y1 * S / data.K, y1);
}

vector<double> CallPrice(const OptionData& option, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallPrice(option, *it));
	}
	return tmp;
}

vector<double> CallPrice(const OptionData& option, double start, double end, double size) {
	return CallPrice(option, MeshArray(start, end, size));
}

double PutPrice(double K, double sig, double r, double b, double S) {
	double tmp = b / (sig * sig);
	double y2 = 0.5 - tmp - sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * r / (sig * sig));
	if (1.0 == y2) return S;
	return K / (1 - y2) * pow((y2 - 1) / y2 * S / K, y2);
}

double PutPrice(const OptionData& data, double S) {
	double tmp = data.b / (data.sig * data.sig);
	double y2 = 0.5 - tmp - sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * data.r / (data.sig * data.sig));
	return data.K / (1 - y2) * pow((y2 - 1) / y2 * S / data.K, y2);
}

vector<double> PutPrice(const OptionData& option, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutPrice(option, *it));
	}
	return tmp;
}

vector<double> PutPrice(const OptionData& option, double start, double end, double size) {
	return PutPrice(option, MeshArray(start, end, size));
}

}	// Namespace AmericanOptionFunction
}	// Namespace OptionFunction