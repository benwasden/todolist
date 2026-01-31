#include <iostream>
#include <limits>
#include <thread>
#include "files.h"
#include "manage.h"
using namespace std;

// Basic menu setup for users to select a reminders list to open.
// Originally part of main.cpp, moved here because it was being used
// in multiple places.
string Manage::selectOption() {
    int selection = 0;
    string filename;
    string reminderText;

    while (selection < 1 || selection > 4) {
        cout << "1. General\n2. Home\n3. Personal\n4. Work\n";
        cout << "Make a selection: ";
        cin >> selection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

// Gathers the goals from a specific requested list
vector<Reminder> Manage::requestedGoals(string option) {
    ManageFile file;
    vector<Reminder> goals = file.openFile(option);
    // Checks to see if there are goals in requested file
    // If so, it then prints all them out
    if (!goals.empty()) {
        cout << "---Reminders---\n";
        for (const auto& pair : goals) {
            string result;
            if (pair.completed == 1) {
                result = "C";
            } else {
                result = "X";
            };

            cout << pair.id << ". " << pair.text << " - [" << result << "]" << endl;
        }
    } else {
        cout << "No reminders have been entered.\n";
    }
    return goals;
}

// Asks the user to enter an id and then uses the markComplete function in
// the ManageFile class to mark it as complete
void Manage::completeGoal(const string& filename) {
    int id;
    cout << "Please enter the ID of the goal you want to complete: ";
    cin >> id;
    ManageFile file;
    file.markComplete(filename, id);
}

// Runs the deleteCompleted function on all 4 lists to delete
// all completed reminders
void Manage::deleteAllCompletedGoals() {
    ManageFile file;
    file.deleteCompleted("data/general.csv");
    file.deleteCompleted("data/home.csv");
    file.deleteCompleted("data/personal.csv");
    file.deleteCompleted("data/work.csv");

    cout << "All completed goals deleted successfully.\n";
}