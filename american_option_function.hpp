// american_option_function.hpp
//
// Header file for american option functions.
//

#ifndef AMERICAN_OPTION_FUNCTION_HPP_
#define AMERICAN_OPTION_FUNCTION_HPP_

#include <vector>
#include "option_data.hpp"

using namespace std;

namespace OptionFunction {
namespace AmericanOptionFunction {
// Call option pricing function with spot price.
double CallPrice(double K, double sig, double r, double b, double S);   // Param version.
double CallPrice(const OptionData& option, double S);   // OptionData version.
vector<double> CallPrice(const OptionData& option, const vector<double>& S);    // Spot price vector version.
vector<double> CallPrice(const OptionData& option, double start, double end, double size);	// Spot price mesh version.

// Put option pricing function with spot price.
double PutPrice(double K, double sig, double r, double b, double S);    // Param version.
double PutPrice(const OptionData& option, double S);    // OptionData version.
vector<double> PutPrice(const OptionData& option, const vector<double>& S); // Spot price vector version.
vector<double> PutPrice(const OptionData& option, double start, double end, double size);   // Spot price mesh version.

} // Namespace AmericanOptionFunction.
}	// Namespace OptionFunction.

#endif	// AMERICAN_OPTION_FUNCTION_HPP_
