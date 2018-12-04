// option.cpp
//
// Option implementation.
//

#include "option.hpp"
#include "option_data.hpp"

using namespace std;

// Default all parameters to 0.0.
Option::Option() : data() {
}

// Create option with parameters.
Option::Option(double T, double K, double sig, double r, double b, double t, double q) {
	data.T = T;
	data.K = K;
	data.sig = sig;
	data.r = r;
	data.b = b;
	data.t = t;
	data.q = q;
}

// Create option with OptionData.
Option::Option(const OptionData& optData) : data(optData) {
}

// Copy constructor.
Option::Option(const Option& option2) : data(option2.data) {
}

// Destructor
Option::~Option() {
}

// Assignment operator.
Option& Option::operator = (const Option& source) {
	// Preclude self-assignment.
	if (this == &source)
		return *this;

	data = source.data;
	return *this;
}

const OptionData& Option::Get() const {
	return data;
}

void Option::Set(const OptionData& optData) {
	data = optData;
}