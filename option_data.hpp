// option_data.hpp
//
// OptionData definition.
//

#ifndef OPTION_DATA_HPP_
#define OPTION_DATA_HPP_

// This struct stores parameters of an option.
struct OptionData {
	double T;		 // Expiry date.
	double K;		 // Strike price.
	double sig;	 // Volatility.
	double r;		 // Interest rate.
	double b;		 // Cost of carry.
	double t;		 // Current date.
	double q;		 // Dividend yield.
};

#endif	// OPTION_DATA_HPP_