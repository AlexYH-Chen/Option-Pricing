// american_option.cpp
//
// AmericanOption implementation.
// 

#include "american_option.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <string>
#include "option_data.hpp"

using namespace std;

// Default call option, all parameters set to 0.0, default call option.
AmericanOption::AmericanOption() : Option(), optType("C") {
}

// Create option type, all parameters set to 0.0.
AmericanOption::AmericanOption(const string& optionType) : Option(), optType(optionType) {
	if (optType == "c")
		optType = "C";
	if (optType == "p")
		optType = "P";
	if ((optType != "C") && (optType != "P"))
		cout << "Wrong option type";
}

// Create option with parameters and option type.
AmericanOption::AmericanOption(double K, double sig, double r, double b, double t, double q, const string& optionType)
	: Option(0.0, K, sig, r, b, t, q),
		optType(optionType) {
}

// Create option with OptionData and option type.
AmericanOption::AmericanOption(const OptionData& optData, const string& optionType) : Option(optData), optType(optionType) {
}

// Copy constructor.
AmericanOption::AmericanOption(const AmericanOption& option2) : Option(option2), optType(option2.optType) {
}

// Destructor.
AmericanOption::~AmericanOption() {
}

AmericanOption& AmericanOption::operator = (const AmericanOption& source) {
	// Preclude self-assignment.
	if (this == &source)
		return *this;

	Option::operator=(source);	// Copy the Option data.
	optType = source.optType;
	return *this;
}

void AmericanOption::toggle() {
	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}

double AmericanOption::Price(double S) const {
	if (optType == "C") {
		return CallPrice(S);
	} else {
		return PutPrice(S);
	}
}

vector<double> AmericanOption::Price(const vector<double>& S) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(Price(*it));
	}
	return tmp;
}

vector<double> AmericanOption::Price(double start, double end, double size) const {
	return Price(MeshArray(start, end, size));
}

double AmericanOption::CallPrice(double S) const {
	double tmp = data.b / (data.sig * data.sig);
	double y1 = 0.5 - tmp + sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * data.r / (data.sig * data.sig));
	if (1.0 == y1) return S;
	return data.K / (y1 - 1) * pow((y1 - 1) / y1 * S / data.K, y1);
}

double AmericanOption::PutPrice(double S) const {
	double tmp = data.b / (data.sig * data.sig);
	double y2 = 0.5 - tmp - sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * data.r / (data.sig * data.sig));
	if (1.0 == y2) return S;
	return data.K / (1 - y2) * pow((y2 - 1) / y2 * S / data.K, y2);
}

vector<double> AmericanOption::MeshArray(double start, double end, double size) const {
	vector<double> tmp;
	for (double i = start; i <= end; i += size) {
		tmp.push_back(i);
	}
	return tmp;
}