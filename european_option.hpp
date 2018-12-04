// european_option.hpp
//
// Header file for Class EuropeanOption.
//

#ifndef EUROPEAN_OPTION_HPP_
#define EUROPEAN_OPTION_HPP_
#include "option.hpp"
#include <string>
#include <vector>
#include "option_data.hpp"

using namespace std;

// Plain European options.
// Access the option type with OptType() and change it with OptType(const string&).
// Change option type (C/P, P/C) with toggle();.
// Calculate option price with Price(double), spot price version.
// Calculate option price vector with Price(const vector<double>&), spot price vector version.
// Calculate option price vector with Price(double, double, double), spot price mesh version.
// Calculate option price vector with Price(const vector<double>&, const string&, double S), param vector version.
// Calculate option price vector with Price(double, double, double, const string&, double), param mesh version.
// Calculate opposite type option price with PutCallParity(double), spot price version.
// Calculate opposite type option price with PutCallParity(const vector<double>&), spot price vector version.
// Calculate opposite type option price with PutCallParity(double, double, double), spot price price mesh version.
// Calculate delta with Delta(double), spot price version.
// Calculate delta with Delta(const vector<double>&), spot price vector version.
// Calculate delta with Delta(double, double, double), spot price mesh version.
// Calculate approximated delta with Delta(double, double), spot price version.
// Calculate approximated delta with Delta(const vector<double>&, double), spot price vector version.
// Calculate approximated delta with Delta(double, double, double, double), spot price mesh version.
// Calculate gamma with Gamma(double), spot price version.
// Calculate gamma with Gamma(const vector<double>&), spot price vector version.
// Calculate gamma with Gamma(double, double, double), spot price mesh version.
// Calculate approximated gamma with Gamma(double, double), spot price version.
// Calculate approximated gamma with Gamma(const vector<double>&, double), spot price vector version.
// Calculate approximated gamma with Gamma(double, double, double, double), spot price mesh version.
// Evaluates whether the put-call parity holds with IsParity(double, double).
// Assign value to the same type of object with binary operator =.
class EuropeanOption : public Option {
 public:
	// Constructors & destructor.
	EuropeanOption();															  // Default call option.
	EuropeanOption(const string& optionType);			  // Create option type.
	EuropeanOption(double T, double K, double sig, double r, double b, double t, double q, const string& optionType);	 // Create option with parameters and option type.
	EuropeanOption(const OptionData& optData, const string& optionType);	// Create option with OptionData and option type.
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor.
	virtual ~EuropeanOption();											// Destructor.

	// Assignment operator.
	EuropeanOption& operator = (const EuropeanOption& source);

	// Selectors.
	const string& OptType() const;	// Normal inline function to access the option type.

	// Modifiers.
	void toggle();														 // Change option type (C/P, P/C).
	void OptType(const string& new_optType) {	 // Default inline function to set the option type.
		optType = new_optType;
	}

	// Functions that calculate option price.
	double Price(double S) const;
	vector<double> Price(const vector<double>& S) const;
	vector<double> Price(double start, double end, double size) const;
	vector<double> Price(const vector<double>& param, const string& paramName, double S);
	vector<double> Price(double start, double end, double size, const string& paramName, double S);
	double PutCallParity(double S) const;
	vector<double> PutCallParity(const vector<double>& S) const;
	vector<double> PutCallParity(double start, double end, double size) const;
	
	// Functions that calculate option sensitivities.
	double Delta(double S) const;
	vector<double> Delta(const vector<double>& S) const;
	vector<double> Delta(double start, double end, double size) const;
	double Delta(double S, double h) const;
	vector<double> Delta(const vector<double>& S, double h) const;
	vector<double> Delta(double start, double end, double size, double h) const;
	double Gamma(double S) const;
	vector<double> Gamma(const vector<double>& S) const;
	vector<double> Gamma(double start, double end, double size) const;
	double Gamma(double S, double h) const;
	vector<double> Gamma(const vector<double>& S, double h) const;
	vector<double> Gamma(double start, double end, double size, double h) const;

	// Evaluation whether the put-call parity holds.
	bool IsParity(double S, double price) const;

 private:
	string optType;	 // Option type (call, put).

	// Kernel functions for option calculations.
	double CallPrice(double S) const;
	double PutPrice(double S) const;
	double CallToPut(double S) const;
	double PutToCall(double S) const;
	double CallDelta(double S) const;
	double PutDelta(double S) const;

	// Gaussian functions.
	double n(double x) const;
	double N(double x) const;

	// This function returns a mesh array with mesh size h.
	vector<double> MeshArray(double start, double end, double size) const;

};

// Implementation of the normal inline function.
inline const string& EuropeanOption::OptType() const {
	return optType;
}

#endif	// EUROPEAN_OPTION_HPP_
