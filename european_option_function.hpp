// european_option_function.hpp
//
// Header file for global european option functions.
//

#ifndef EUROPEAN_OPTION_FUNCTION_HPP_
#define EUROPEAN_OPTION_FUNCTION_HPP_

#include <vector>
#include "option_data.hpp"

using namespace std;

namespace OptionFunction {
namespace EuropeanOptionFunction {
// Gaussian distribution.
double n(double x);	 // Pdf(x).
double N(double x);	 // Cdf(x).

// Call option pricing function with spot price.
double CallPrice(double T, double K, double sig, double r, double b, double S); // Param version.
double CallPrice(const OptionData& option, double S);   // OptionData version.
vector<double> CallPrice(const OptionData& option, const vector<double>& S);    // Spot price vector version.
vector<double> CallPrice(const OptionData& option, double start, double end, double size);  // Spot price mesh version.
	
// Call option pricing function with one changing parameter.
vector<double> CallPrice(const OptionData& option, const vector<double>& param, const string& paramName, double S); // Param vector version.
vector<double> CallPrice(const OptionData& option, double start, double end, double size, const string& paramName, double S);   // Param mesh version.

// Put option pricing function with spot price.
double PutPrice(double T, double K, double sig, double r, double b, double S);	// Param version.
double PutPrice(const OptionData& option, double S);    // OptionData version.
vector<double> PutPrice(const OptionData& option, const vector<double>& S); // Spot price vector version.
vector<double> PutPrice(const OptionData& option, double start, double end, double size);   // Spot price mesh version.

// Put option pricing function with one changing parameter.
vector<double> PutPrice(const OptionData& option, const vector<double>& param, const string& paramName, double S);  // Param vector version.
vector<double> PutPrice(const OptionData& option, double start, double end, double size, const string& paramName, double S);    // Param mesh version.

// Put-call parity pricing function (call to put).
double CallToPut(const OptionData& option, double C, double S); // Given call price, spot price version.
vector<double> CallToPut(const OptionData& option, double C, const vector<double>& S);  // Given call price, spot price vector version.
vector<double> CallToPut(const OptionData& option, double C, double start, double end, double size);    // Given call price, spot price mesh version.
double CallToPut(const OptionData& option, double S);   // No given price, spot price version.
vector<double> CallToPut(const OptionData& option, const vector<double>& S);    // No given price, spot price vector version.
vector<double> CallToPut(const OptionData& option, double start, double end, double size);  // No given price, spot price mesh version.

// Put-call parity pricing function (put to call).
double PutToCall(const OptionData& option, double P, double S); // Given put price, spot price version.
vector<double> PutToCall(const OptionData& option, double P, const vector<double>& S);  // Given put price, spot price vector version.
vector<double> PutToCall(const OptionData& option, double P, double start, double end, double size);    // Given put price, spot price mesh version.
double PutToCall(const OptionData& option, double S);   // No given price, spot price version.
vector<double> PutToCall(const OptionData& option, const vector<double>& S);    // No given price, spot price vector version.
vector<double> PutToCall(const OptionData& option, double start, double end, double size);  // No given price, spot price mesh version.

// Call option delta function.
double CallDelta(const OptionData& data, double S); // Spot price version.
vector<double> CallDelta(const OptionData& data, const vector<double>& S);  // Spot price vector version.
vector<double> CallDelta(const OptionData& data, double start, double end, double size);    // Spot price mesh version.

// Call option delta approximation function. 
double CallDelta(const OptionData& data, double S, double h);   // Spot price version.
vector<double> CallDelta(const OptionData& data, const vector<double>& S, double h);    // Spot price vector version.
vector<double> CallDelta(const OptionData& data, double start, double end, double size, double h);  // Spot price mesh version.

// Put option delta function.
double PutDelta(const OptionData& data, double S);  // Spot price version.
vector<double> PutDelta(const OptionData& data, const vector<double>& S);   // Spot price vector version.
vector<double> PutDelta(const OptionData& data, double start, double end, double size); // Spot price mesh version.

// Put option delta approximation function. 
double PutDelta(const OptionData& data, double S, double h);    // Spot price version.
vector<double> PutDelta(const OptionData& data, const vector<double>& S, double h); // Spot price vector version.
vector<double> PutDelta(const OptionData& data, double start, double end, double size, double h);   // Spot price mesh version.
	
// Call option gamma function.
double CallGamma(const OptionData& data, double S); // Spot price version.
vector<double> CallGamma(const OptionData& data, const vector<double>& S);  // Spot price vector version.
vector<double> CallGamma(const OptionData& data, double start, double end, double size);    // Spot price mesh version.

// Call option gamma approximation function.
double CallGamma(const OptionData& data, double S, double h);   // Spot price version.
vector<double> CallGamma(const OptionData& data, const vector<double>& S, double h);    // Spot price vector version.
vector<double> CallGamma(const OptionData& data, double start, double end, double size, double h);  // Spot price mesh version.

// Put option gamma function.
double PutGamma(const OptionData& data, double S);  // Spot price version.
vector<double> PutGamma(const OptionData& data, const vector<double>& S);   // Spot price vector version.
vector<double> PutGamma(const OptionData& data, double start, double end, double size); // Spot price mesh version.
	
// Put option gamma approximation function.
double PutGamma(const OptionData& data, double S, double h);    // Spot price version.
vector<double> PutGamma(const OptionData& data, const vector<double>& S, double h); // Spot price vector version.
vector<double> PutGamma(const OptionData& data, double start, double end, double size, double h);   // Spot price mesh version.
	
}	// Namespace EuropeanOptionFunction.
}	// Namespace OptionFunction.

#endif	// EUROPEAN_OPTION_FUNCTION_HPP_
