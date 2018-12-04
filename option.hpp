// option.hpp
//
// Header file for class option.
//

#ifndef OPTION_HPP_
#define OPTION_HPP_
#include "option_data.hpp"

// Option with parameters.
// Access the expiry date with T() and change it with T(double).
// Access the strike price with K() and change it with K(double).
// Access the volatility with sig() and change it with sig(double).
// Access the interest rate with r() and change it with r(double).
// Access the cost of carry with b() and change it with b(double).
// Access the current date with t() and change it with t(double).
// Access the dividend yield with q() and change it with q(double).
// Access the option parameters with Get().
// Set the parameters with Set(const OptionData&).
// Assign value to the same type of object with binary operator =.
class Option {
public:
	// Constructors & destructor.
	Option();	// Default constructor.
	Option(double T, double K, double sig, double r, double b, double t, double q);	 // Create option with parameters.
	Option(const OptionData& optData);	// Create option with OptionData.
	Option(const Option& option2);	// Copy constructor.
	virtual ~Option();	// Destructor.

	// Assignment operator.
	Option& operator = (const Option& source);

	// Selectors.
	double T() const;					// Normal inline function to access the expiry date.
	double K() const;					// Normal inline function to access the strike price.
	double sig() const;					// Normal inline function to access the volatility.
	double r() const;					// Normal inline function to access the interest rate.
	double b() const;					// Normal inline function to access the cost of carry.
	double t() const;					// Normal inline function to access the current date.
	double q() const;					// Normal inline function to access the dividend yield.
	const OptionData& Get() const;		// Return the option parameters.

	// Modifiers.
	void T(double new_T) {			// Default inline function to set the expiry date.
		data.T = new_T;
	}

	void K(double new_K) {			// Default inline function to set the Strike price.
		data.K = new_K;
	}

	void sig(double new_sig) {		// Default inline function to set the volatility.
		data.sig = new_sig;
	}

	void r(double new_r) {			// Default inline function to set the interest rate.
		data.r = new_r;
	}

	void b(double new_b) {			// Default inline function to set the cost of carry.
		data.b = new_b;
	}

	void t(double new_t) {			// Default inline function to set the current date.
		data.t = new_t;
	}

	void q(double new_q) {			// Default inline function to set the dividend yield.
		data.q = new_q;
	}

	void Set(const OptionData& optData);	// Set the parameters with OptionData.

protected:
	OptionData data;	 // Option parameters.
};

// Implementation of the normal inline function.
inline double Option::T() const {
	return data.T;
}

inline double Option::K() const {
	return data.K;
}

inline double Option::sig() const {
	return data.sig;
}

inline double Option::r() const {
	return data.r;
}

inline double Option::b() const {
	return data.b;
}

inline double Option::t() const {
	return data.t;
}

inline double Option::q() const {
	return data.q;
}

#endif	// OPTION_HPP_

