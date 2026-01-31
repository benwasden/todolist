#pragma once

#include <string>
#include <vector>

using namespace std;

// A Reminder object with its own variables for use in other parts of app
struct Reminder {
    int id;
    string text;
    bool completed;
};

// Largest class meant to do operations with csv files
class ManageFile {
public:
    vector<Reminder> openFile(const string& filename);
    void writeFile(const string& filename, const Reminder& remind);
    vector<Reminder> readAllFiles();
    int getNextId(const string& filename);
    void markComplete(const string& filename, int id);
    void deleteCompleted(const string& filename);
};
