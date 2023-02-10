//
// Created by Denisa on 26.03.2022.
//

#pragma once
#include <string>
#include "Book.h"
#include <vector>

using std::string;
using std::vector;
using std::ostream;

class ValidateException {
    vector<string> errorMsg;
public:
    ValidateException(const vector<string>& errors) :errorMsg{ errors } {};

    string getErrorMessages() {
        string fullMsg = "";
        for(const string e : errorMsg){
            fullMsg += e + "\n";
        }
        return fullMsg;
    }
};


