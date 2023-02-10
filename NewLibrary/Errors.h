//
// Created by Denisa on 06.04.2022.
//

#pragma once
#include <string>

using namespace std;

class Exception {
    string msg;

public:
    Exception(string m) : msg{ m } {

    }
    string getMessage() {
        return msg;
    }
};