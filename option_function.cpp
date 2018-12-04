// option_function.cpp
//
// Functions implementation.
//

#include "option_function.hpp"
#include <iostream>
#include <vector>
#include "option_data.hpp"

using namespace std;

namespace OptionFunction {

vector<double> MeshArray(double start, double end, double size) {
	vector<double> tmp;
	for (double i = start; i <= end; i += size) {
		tmp.push_back(i);
	}
	return tmp;
}

void PrintVector(const vector<double>& v) {
	vector<double>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		cout << (*it) << "  ";
	}
	cout << endl;
}

}	// Namespace OptionFunction.

