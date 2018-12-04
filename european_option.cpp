// european_option.cpp
//
// EuropeanOption implementation.
// 

#include "european_option.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <string>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>	 // For non-member functions of distributions.
#include "option_data.hpp"

using namespace std;
using namespace boost::math;

// Default call option, all parameters set to 0.0, default call option.
EuropeanOption::EuropeanOption() : Option(), optType("C"){
}

// Create option type, all parameters set to 0.0.
EuropeanOption::EuropeanOption(const string& optionType) : Option(), optType(optionType) {
	if (optType == "c")
		optType = "C";
	if (optType == "p")
		optType = "P";
	if ((optType!="C")&&(optType!="P"))
		cout << "Wrong option type";
}

// Create option with parameters and option type.
EuropeanOption::EuropeanOption(double T, double K, double sig, double r, double b, double t, double q, const string& optionType)
		: Option(T, K, sig, r, b, t, q),
			optType(optionType) {
}

// Create option with OptionData and option type.
EuropeanOption::EuropeanOption(const OptionData& optData, const string& optionType) : Option(optData), optType(optionType) {
}

// Copy constructor.
EuropeanOption::EuropeanOption(const EuropeanOption& option2) : Option(option2), optType(option2.optType) {
}

// Destructor.
EuropeanOption::~EuropeanOption() {
}

EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source) {
	// Preclude self-assignment.
	if (this == &source)	
		return *this;
	
	Option::operator=(source);	// Copy the Option data.
	optType = source.optType;
	return *this;
}

void EuropeanOption::toggle() { 
	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}

double EuropeanOption::Price(double S) const {
	if (optType == "C") {
		return CallPrice(S);
	} else {
		return PutPrice(S);
	}
}

vector<double> EuropeanOption::Price(const vector<double>& S) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(Price(*it));
	}
	return tmp;
}

vector<double> EuropeanOption::Price(double start, double end, double size) const {
	return Price(MeshArray(start, end, size));
}

// Using paraName to decide which parameter to change while other parameters hold constant.
vector<double> EuropeanOption::Price(const vector<double>& param, const string& paramName, double S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	double hold;

	if (paramName == "T") {
		hold = data.T;
		for (it = param.begin(); it != param.end(); it++) {
			Option::T(*it);
			tmp.push_back(Price(S));
		}
		Option::T(hold);
	} else if (paramName == "K") {
		hold = data.K;
		for (it = param.begin(); it != param.end(); it++) {
			Option::K(*it);
			tmp.push_back(Price(S));
		}
		Option::K(hold);
	} else if (paramName == "sig") {
		hold = data.sig;
		for (it = param.begin(); it != param.end(); it++) {
			Option::sig(*it);
			tmp.push_back(Price(S));
		}
		Option::sig(hold);
	} else {
		cout << "Wrong parameter name" << endl;
	}
	return tmp;
}

vector<double> EuropeanOption::Price(double start, double end, double size, const string& paramName, double S) {
	return Price(MeshArray(start, end, size), paramName, S);
}

double EuropeanOption::PutCallParity(double S) const {
	if (optType == "C")
		return CallToPut(S);
	else
		return PutToCall(S);
}

vector<double> EuropeanOption::PutCallParity(const vector<double>& S) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	if (optType == "C") {
		for (it = S.begin(); it != S.end(); it++) {
			tmp.push_back(CallToPut(*it));
		}
	} else {
		for (it = S.begin(); it != S.end(); it++) {
			tmp.push_back(PutToCall(*it));
		}
	}
	return tmp;
}

vector<double> EuropeanOption::PutCallParity(double start, double end, double size) const {
	return PutCallParity(MeshArray(start, end, size));
}

double EuropeanOption::Delta(double S) const {
	if (optType == "C")
		return CallDelta(S);
	else
		return PutDelta(S);
}

vector<double> EuropeanOption::Delta(const vector<double>& S) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	if (optType == "C") {
		for (it = S.begin(); it != S.end(); it++) {
			tmp.push_back(CallDelta(*it));
		}
	} else {
		for (it = S.begin(); it != S.end(); it++) {
			tmp.push_back(PutDelta(*it));
		}
	}
	return tmp;
}

vector<double> EuropeanOption::Delta(double start, double end, double size) const {
	return Delta(MeshArray(start, end, size));
}

double EuropeanOption::Delta(double S, double h) const {
	return (Price(S + h) - Price(S - h)) / (2 * h);
}

vector<double> EuropeanOption::Delta(const vector<double>& S, double h) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(Delta(*it, h));
	}
	return tmp;
}

vector<double> EuropeanOption::Delta(double start, double end, double size, double h) const {
	return Delta(MeshArray(start, end, size), h);
}

double EuropeanOption::Gamma(double S) const {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * n(d1) / (S * tmp);
}

vector<double> EuropeanOption::Gamma(const vector<double>& S) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(Gamma(*it));
	}
	return tmp;
}

vector<double> EuropeanOption::Gamma(double start, double end, double size) const {
	return Gamma(MeshArray(start, end, size));
}

double EuropeanOption::Gamma(double S, double h) const {
	return (Price(S + h) - 2 * Price(S) + Price(S - h)) / (h * h);
}

vector<double> EuropeanOption::Gamma(const vector<double>& S, double h) const {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(Gamma(*it, h));
	}
	return tmp;
}

vector<double> EuropeanOption::Gamma(double start, double end, double size, double h) const {
	return Gamma(MeshArray(start, end, size), h);
}

bool EuropeanOption::IsParity(double S, double price) const {
	double epsilon = 0.00001;
	if (abs(PutCallParity(S) - price) < epsilon)
		return true;
	else
		return false;
}

// Private function.

double EuropeanOption::CallPrice(double S) const {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	double d2 = d1 - tmp;
	return (S * exp((data.b - data.r) * data.T) * N(d1)) - (data.K * exp(-data.r * data.T) * N(d2));
}

double EuropeanOption::PutPrice(double S) const {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	double d2 = d1 - tmp;
	return (data.K * exp(-data.r * data.T) * N(-d2)) - (S * exp((data.b - data.r) * data.T) * N(-d1));
}

double EuropeanOption::CallToPut(double S) const {
	return (Price(S) + data.K * exp(-data.r * data.T) - S);
}

double EuropeanOption::PutToCall(double S) const {
	return (Price(S) + S - data.K * exp(-data.r * data.T));
}

double EuropeanOption::CallDelta(double S) const {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * N(d1);
}

double EuropeanOption::PutDelta(double S) const {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * (N(d1) - 1.0);
}

// Using boost library normal_distribution. 
double EuropeanOption::n(double x) const {
	normal_distribution<> myNormal(0.0, 1.0);
	return pdf(myNormal, x);
}

// Using boost library normal_distribution. 
double EuropeanOption::N(double x) const {
	normal_distribution<> myNormal(0.0, 1.0);
	return cdf(myNormal, x);
}

vector<double> EuropeanOption::MeshArray(double start, double end, double size) const {
	vector<double> tmp;
	for (double i = start; i <= end; i += size) {
		tmp.push_back(i);
	}
	return tmp;
}