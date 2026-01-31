#pragma once
#include <string>
#include "files.h"

using namespace std;

class Manage {
    public:
        string selectOption();
        vector<int> requestedGoals(string option);
};