#include "reminder.h"
#include <iostream>
#include <limits>
#include <thread>
using namespace std;

MakeReminder::Info MakeReminder::addReminder() {
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

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (reminderText.empty()) {
        cout << "Please enter a new reminder: ";
        getline(cin, reminderText);
    }

    ManageFile files;
    int nextId = files.getNextId(filename);

    Reminder remind;
    remind.id = nextId;
    remind.text = reminderText;
    remind.completed = false;

    Info information;
    information.filename = filename;
    information.reminder = remind;

    return information;
}
