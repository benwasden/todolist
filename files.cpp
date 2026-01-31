#include "files.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Opens a csv file and takes its info and stores it in a vector
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

// Opens a csv file and writes a new reminder to it
void ManageFile::writeFile(const string& filename, const Reminder& remind) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error when opening file " << filename << "\n";
        return;
    }

    file << remind.id << "," << remind.text << "," << (remind.completed ? "true" : "false") << "\n";
}

// Uses the prior openFile function to get the reminders from all files
vector<Reminder> ManageFile::readAllFiles() {
    vector<Reminder> all;

    // Sets up function to append the contents of one file
    // to the end of the existing "all" vector
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

// Iterates through a file to see the next for-sure available ID
int ManageFile::getNextId(const string& filename) {
    auto reminders = openFile(filename);

    // Iterating
    int maxId = 0;
    for (const auto& remind : reminders) {
        if (remind.id > maxId) {
            maxId = remind.id;
        }
    }

    return maxId + 1;
}

// Opens a file and adds them all to a vector and then marks the requested reminder as complete before writing
// the vector back to the csv file
void ManageFile::markComplete(const string& filename, int id) {
    vector<Reminder> reminders = openFile(filename);

    // Iterates through all entries in csv and finds the id
    // of requested reminder, then marks as complete
    bool found = false;
    for (auto& remind : reminders) {
        if (remind.id == id) {
            remind.completed = true;
            found = true;
            break;
        }
    };

    if (!found) {
        cerr << "Couldn't find a reminder with ID " << id << "\n";
        return;
    };

    // Opens the file
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error trying to open that file.\n";
        return;
    };

    // Rewrites the data of all reminders back to file with completed goal
    for (const auto& remind : reminders) {
        file << remind.id << "," << remind.text << "," << (remind.completed ? "true" : "false") << "\n";
    }

    cout << "Reminder complete!\n";
}

// Function to delete all completed reminders across all files
void ManageFile::deleteCompleted(const string& filename) {
    vector<Reminder> reminders = openFile(filename);

    if (reminders.empty()) {
        return;
    }

    // Sets up a vector that compares new remainder vector
    // to reminders and deletes completed goals
    vector<Reminder> remainder;
    for (const auto& remind : reminders) {
        if (!remind.completed) {
            remainder.push_back(remind);
        };
    };

    if (remainder.size() == reminders.size()) {
        return;
    };

    // Writes remainder to file
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error opening" << filename << "\n";
        return;
    };

    for (const auto& remind : remainder) {
        file << remind.id << "," << remind.text << "," << (remind.completed ? "true" : "false") << "\n";
    };
}