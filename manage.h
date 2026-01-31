#pragma once
#include <string>
#include "files.h"

using namespace std;

// Create manage class
class Manage {
    public:
        string selectOption();
        vector<Reminder> requestedGoals(string option);
        void completeGoal(const string& filename);
        void deleteAllCompletedGoals();
};