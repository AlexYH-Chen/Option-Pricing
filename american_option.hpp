// american_option.hpp
//
// Header file for Class AmericanOption.
// Perpetual american option.
//

#ifndef AMERICAN_OPTION_HPP_
#define AMERICAN_OPTION_HPP_
#include "option.hpp"
#include <string>
#include <vector>
#include "option_data.hpp"

using namespace std;

class AmericanOption : public Option {
public:
	// Constructors & destructor.
	AmericanOption();	// Default call option.
	AmericanOption(const string& optionType);	// Create option type.
	AmericanOption(double K, double sig, double r, double b, double t, double q, const string& optionType);	 // Create option with parameters and option type.
	AmericanOption(const OptionData& optData, const string& optionType);	// Create option with OptionData and option type.
	AmericanOption(const AmericanOption& option2);	// Copy constructor.
	virtual ~AmericanOption();	// Destructor.

	// Assignment operator.
	AmericanOption& operator = (const AmericanOption& source);

	// Selectors.
	const string& OptType() const;	// Normal inline function to access the option type.

	// Modifiers.
	void toggle();	// Change option type (C/P, P/C).
	void OptType(const string& new_optType) {	// Default inline function to set the option type.
		optType = new_optType;
	}

	// Functions that calculate option price.
	double Price(double S) const;
	vector<double> Price(const vector<double>& S) const;
	vector<double> Price(double start, double end, double size) const;

private:
	string optType;	 // Option type (call, put).

	// Kernel functions for option calculations.
	double CallPrice(double S) const;
	double PutPrice(double S) const;

	// This function returns a mesh array with mesh size h.
	vector<double> MeshArray(double start, double end, double size) const;

};

// Implementation of the normal inline function.
inline const string& AmericanOption::OptType() const {
	return optType;
}

#endif	// AMERICAN_OPTION_HPP_
