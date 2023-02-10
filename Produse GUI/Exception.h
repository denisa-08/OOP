#pragma once
#include <string>
using namespace std;
class Exception {
private:
	string message;

public:
	Exception(string message) : message{ message } {

	}

	string getMessage() {
		return message;
	}
};
