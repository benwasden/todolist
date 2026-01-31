#include <iostream>
#include <limits>
#include <thread>
#include "files.h"
#include "manage.h"
using namespace std;

string Manage::selectOption() {
    int selection = 0;
    string filename;
    string reminderText;

    while (selection < 1 || selection > 4) {
        cout << "Which type of reminder do you want to make?\n";
        cout << "1. General\n2. Home\n3. Personal\n4. Work\n";
        cout << "Make a selection: ";
        cin >> selection;

        switch (selection) {
            case 1: filename = "data/general.csv"; break;
            case 2: filename = "data/home.csv"; break;
            case 3: filename = "data/personal.csv"; break;
            case 4: filename = "data/work.csv"; break;
            default:
                cout << "Please enter a valid option\n";
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
    return filename;
};

vector<int> Manage::requestedGoals(string option) {
    vector<int> remIndex;
    ManageFile file;
    vector<Reminder> goals = file.openFile(option);
    if (!goals.empty()) {
        cout << "---Reminders---\n";
        for (const auto& pair : goals) {
            string result;
            if (pair.completed == 1) {
                result = "C";
            } else {
                result = "X";
            };
            remIndex.push_back(pair.id);
            cout << pair.id << ". " << pair.text << " - [" << result << "]" << endl;
        }
    } else {
        cout << "No reminders have been entered.\n";
    }
    return remIndex;
}