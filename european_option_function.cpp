// option_function.cpp
//
// Functions implementation.
//

#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>	 // For non-member functions of distributions.
#include <iostream>
#include <cmath>
#include <vector>
#include "option_data.hpp"
#include "option_function.hpp"

using namespace std;
using namespace boost::math;

namespace OptionFunction {
namespace EuropeanOptionFunction {
// Using boost library normal_distribution. 
double n(double x) {
	normal_distribution<> myNormal(0.0, 1.0);
	return pdf(myNormal, x);
}

// Using boost library normal_distribution. 
double N(double x) {
	normal_distribution<> myNormal(0.0, 1.0);
	return cdf(myNormal, x);
}

// Using n(x) and N(x).
double CallPrice(double T, double K, double sig, double r, double b, double S) {
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (S * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
}

// Using n(x) and N(x).
double CallPrice(const OptionData& option, double S) {
	double tmp = option.sig * sqrt(option.T);
	double d1 = (log(S / option.K) + (option.b + (option.sig * option.sig) * 0.5) * option.T) / tmp;
	double d2 = d1 - tmp;
	return (S * exp((option.b - option.r) * option.T) * N(d1)) - (option.K * exp(-option.r * option.T) * N(d2));
}

// Using n(x), N(x) and CallPrice(const OptionData&, double).
vector<double> CallPrice(const OptionData& option, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallPrice(option, *it));
	}
	return tmp;
}

// Using CallPrice(const OptionData&, const vector<double>&) and MeshArray(double, double, double).
vector<double> CallPrice(const OptionData& option, double start, double end, double size) {
	return CallPrice(option, MeshArray(start, end, size));
}

// Using paraName to decide which parameter to change while other parameters hold constant. 
vector<double> CallPrice (const OptionData& option, const vector<double>& param, const string& paramName, double S) {
	OptionData data = option;
	vector<double> tmp;
	vector<double>::const_iterator it;

	if (paramName == "T") {
		for (it = param.begin(); it != param.end(); it++) {
			data.T = *it;
			tmp.push_back(CallPrice(data, S));
		}
	} else if (paramName == "K") {
		for (it = param.begin(); it != param.end(); it++) {
			data.K = *it;
			tmp.push_back(CallPrice(data, S));
		}
	} else if (paramName == "sig") {
		for (it = param.begin(); it != param.end(); it++) {
			data.sig = *it;
			tmp.push_back(CallPrice(data, S));
		}
	} else {
		cout << "Wrong parameter name" << endl;
	}
	return tmp;
}

// Using paraName to decide which parameter to change while other parameters hold constant. 
vector<double> CallPrice(const OptionData& option, double start, double end, double size, const string& paramName, double S) {
	return CallPrice(option, MeshArray(start, end, size), paramName, S);
}

// Using n(x) and N(x).
double PutPrice(double T, double K, double sig, double r, double b, double S) {
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (K * exp(-r * T) * N(-d2)) - (S * exp((b - r) * T) * N(-d1));
}

// Using n(x) and N(x).
double PutPrice(const OptionData& option, double S) {
	double tmp = option.sig * sqrt(option.T);
	double d1 = (log(S / option.K) + (option.b + (option.sig * option.sig) * 0.5) * option.T) / tmp;
	double d2 = d1 - tmp;
	return (option.K * exp(-option.r * option.T) * N(-d2)) - (S * exp((option.b - option.r) * option.T) * N(-d1));
}

// Using n(x), N(x) and PutPrice(const OptionData&, double).
vector<double> PutPrice(const OptionData& option, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutPrice(option, *it));
	}
	return tmp;
}

// Using PutPrice(const OptionData&, const vector<double>&) and MeshArray(double, double, double).
vector<double> PutPrice(const OptionData& option, double start, double end, double size) {
	return PutPrice(option, MeshArray(start, end, size));
}

// Using paraName to decide which parameter to change while others hold constant. 
vector<double> PutPrice(const OptionData& option, const vector<double>& param, const string& paramName, double S) {
	OptionData data = option;
	vector<double> tmp;
	vector<double>::const_iterator it;

	if (paramName == "T") {
		for (it = param.begin(); it != param.end(); it++) {
			data.T = *it;
			tmp.push_back(PutPrice(data, S));
		}
	} else if (paramName == "K") {
		for (it = param.begin(); it != param.end(); it++) {
			data.K = *it;
			tmp.push_back(PutPrice(data, S));
		}
	} else if (paramName == "sig") {
		for (it = param.begin(); it != param.end(); it++) {
			data.sig = *it;
			tmp.push_back(PutPrice(data, S));
		}
	} else {
		cout << "Wrong parameter name" << endl;
	}
	return tmp;
}

// Using paraName to decide which parameter to change while others hold constant.
vector<double> PutPrice(const OptionData& option, double start, double end, double size, const string& paramName, double S) {
	return PutPrice(option, MeshArray(start, end, size), paramName, S);
}


// Put-call parity pricing function (call to put).

double CallToPut(const OptionData& option, double C, double S) {
	return (C + option.K * exp(-option.r * option.T) - S);
}

vector<double> CallToPut(const OptionData& option, double C, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallToPut(option, C, *it));
	}
	return tmp;
}

vector<double> CallToPut(const OptionData& option, double C, double start, double end, double size) {
	return CallToPut(option, C, MeshArray(start, end, size));
}

double CallToPut(const OptionData& option, double S) {
	return CallToPut(option, CallPrice(option, S), S);
}

vector<double> CallToPut(const OptionData& option, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallToPut(option, *it));
	}
	return tmp;
}

vector<double> CallToPut(const OptionData& option, double start, double end, double size) {
	return CallToPut(option, MeshArray(start, end, size));
}

// Put-call parity pricing function (put to call).

double PutToCall(const OptionData& option, double P, double S) {
	return (P + S - option.K * exp(-option.r * option.T));
}

vector<double> PutToCall(const OptionData& option, double P, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutToCall(option, P, *it));
	}
	return tmp;
}

vector<double> PutToCall(const OptionData& option, double P, double start, double end, double size) {
	return PutToCall(option, P, MeshArray(start, end, size));
}

double PutToCall(const OptionData& option, double S) {
	return PutToCall(option, PutPrice(option, S), S);
}

vector<double> PutToCall(const OptionData& option, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutToCall(option, *it));
	}
	return tmp;
}

vector<double> PutToCall(const OptionData& option, double start, double end, double size) {
	return PutToCall(option, MeshArray(start, end, size));
}

// Call option delta function.

double CallDelta(const OptionData& data, double S) {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * N(d1);
}

vector<double> CallDelta(const OptionData& data, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallDelta(data, *it));
	}
	return tmp;
}

vector<double> CallDelta(const OptionData& data, double start, double end, double size) {
	return CallDelta(data, MeshArray(start, end, size));
}

// Call option delta approximation function.

double CallDelta(const OptionData& data, double S, double h) {
	return (CallPrice(data, S + h) - CallPrice(data, S - h)) / (2 * h);
}

vector<double> CallDelta(const OptionData& data, const vector<double>& S, double h) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallDelta(data, *it, h));
	}
	return tmp;
}

vector<double> CallDelta(const OptionData& data, double start, double end, double size, double h) {
	return CallDelta(data, MeshArray(start, end, size), h);
}

// Put option delta function.

double PutDelta(const OptionData& data, double S) {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * (N(d1) - 1.0);
}

vector<double> PutDelta(const OptionData& data, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutDelta(data, *it));
	}
	return tmp;
}

vector<double> PutDelta(const OptionData& data, double start, double end, double size) {
	return PutDelta(data, MeshArray(start, end, size));
}

// Put option delta approximation function.

double PutDelta(const OptionData& data, double S, double h) {
	return (PutPrice(data, S + h) - PutPrice(data, S - h)) / (2 * h);
}

vector<double> PutDelta(const OptionData& data, const vector<double>& S, double h) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutDelta(data, *it, h));
	}
	return tmp;
}

vector<double> PutDelta(const OptionData& data, double start, double end, double size, double h) {
	return PutDelta(data, MeshArray(start, end, size), h);
}

// Call option gamma function.

double CallGamma(const OptionData& data, double S){
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * n(d1) / (S * tmp);
}

vector<double> CallGamma(const OptionData& data, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallGamma(data, *it));
	}
	return tmp;
}

vector<double> CallGamma(const OptionData& data, double start, double end, double size) {
	return CallGamma(data, MeshArray(start, end, size));
}

// Call option gamma approximation function.

double CallGamma(const OptionData& data, double S, double h) {
	return (CallPrice(data, S + h) - 2 * CallPrice(data, S) + CallPrice(data, S - h)) / (h * h);
}

vector<double> CallGamma(const OptionData& data, const vector<double>& S, double h){
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(CallGamma(data, *it, h));
	}
	return tmp;
}

vector<double> CallGamma(const OptionData& data, double start, double end, double size, double h) {
	return CallGamma(data, MeshArray(start, end ,size), h);
}

// Put option gamma function.

double PutGamma(const OptionData& data, double S) {
	double tmp = data.sig * sqrt(data.T);
	double d1 = (log(S / data.K) + (data.b + (data.sig * data.sig) * 0.5) * data.T) / tmp;
	return exp((data.b - data.r) * data.T) * n(d1) / (S * tmp);
}

vector<double> PutGamma(const OptionData& data, const vector<double>& S) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutGamma(data, *it));
	}
	return tmp;
}

vector<double> PutGamma(const OptionData& data, double start, double end, double size) {
	return PutGamma(data, MeshArray(start, end, size));
}

// Put option gamma approximation function.

double PutGamma(const OptionData& data, double S, double h) {
	return (PutPrice(data, S + h) - 2 * PutPrice(data, S) + PutPrice(data, S - h)) / (h * h);
}

vector<double> PutGamma(const OptionData& data, const vector<double>& S, double h) {
	vector<double> tmp;
	vector<double>::const_iterator it;
	for (it = S.begin(); it != S.end(); it++) {
		tmp.push_back(PutGamma(data, *it, h));
	}
	return tmp;
}

vector<double> PutGamma(const OptionData& data, double start, double end, double size, double h) {
	return PutGamma(data, MeshArray(start, end, size), h);
}

}	// Namespace EuropeanOptionFunction.
}	// Namespace OptionFunction.