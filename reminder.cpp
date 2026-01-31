#include "reminder.h"
#include <iostream>
#include <limits>
#include <thread>
#include "manage.h"
using namespace std;

MakeReminder::Info MakeReminder::addReminder() {
    string reminderText;

    Manage manage;
    cout << "Which type of reminder do you want to make?\n";
    string filename = manage.selectOption();

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


