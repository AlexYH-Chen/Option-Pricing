// option_function.hpp
//
// Header file for option functions.
//

#ifndef OPTION_FUNCTION_HPP_
#define OPTION_FUNCTION_HPP_

#include <vector>

using namespace std;

namespace OptionFunction {
// This function returns a mesh array with mesh size h.
vector<double> MeshArray(double start, double end, double size);

// This function prints the elements of a double vector.
void PrintVector(const vector<double>& v);

}	// Namespace OptionFunction.

#endif	// OPTION_FUNCTION_HPP_
