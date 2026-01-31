#pragma once
#include <string>
#include "files.h"

using namespace std;

class Manage {
    public:
        string selectOption();
        vector<Reminder> requestedGoals(string option);
        void completeGoal(const string& filename);
        void deleteAllCompletedGoals();
};