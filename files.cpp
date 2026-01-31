#include "files.h"
#include <iostream>
#include <fstream>
#include <sstream>

vector<Reminder> ManageFile::openFile(const string& filename) {
    vector<Reminder> reminders;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: couldn't open file " << filename << "\n";
        return reminders;
    }

    string line;
    while (getline(file, line)) {
        stringstream lineToParse(line);
        string idStr, text, completedStr;

        if (getline(lineToParse, idStr, ',') &&
            getline(lineToParse, text, ',') &&
            getline(lineToParse, completedStr)) {

            Reminder remind;
            remind.id = stoi(idStr);
            remind.text = text;
            remind.completed = (completedStr == "true");

            reminders.push_back(remind);
        }
    }

    return reminders;
}

void ManageFile::writeFile(const string& filename, const Reminder& remind) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error when opening file " << filename << "\n";
        return;
    }

    file << remind.id << "," << remind.text << "," << (remind.completed ? "true" : "false") << "\n";
    cout << "Reminder added!";
}

vector<Reminder> ManageFile::readAllFiles() {
    vector<Reminder> all;

    auto append = [&](const string& file) {
        auto next = openFile(file);
        all.insert(all.end(), next.begin(), next.end());
    };

    append("data/general.csv");
    append("data/home.csv");
    append("data/personal.csv");
    append("data/work.csv");

    return all;
}

int ManageFile::getNextId(const string& filename) {
    auto reminders = openFile(filename);

    int maxId = 0;
    for (const auto& remind : reminders) {
        if (remind.id > maxId) {
            maxId = remind.id;
        }
    }

    return maxId + 1;
}
