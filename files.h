#pragma once

#include <string>
#include <vector>

using namespace std;

struct Reminder {
    int id;
    string text;
    bool completed;
};

class ManageFile {
public:
    vector<Reminder> openFile(const string& filename);
    void writeFile(const string& filename, const Reminder& remind);
    vector<Reminder> readAllFiles();
    int getNextId(const string& filename);
    void markComplete(const string& filename, int id);
    void deleteCompleted(const string& filename);
};
