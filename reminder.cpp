#include "reminder.h"
#include <iostream>
#include <limits>
#include <thread>
#include "manage.h"
using namespace std;

// The format to ask users when trying to add a reminder
MakeReminder::Info MakeReminder::addReminder() {
    string reminderText;

    // Ask for reminder
    Manage manage;
    cout << "Which type of reminder do you want to make?\n";
    // Call selectOption function in MakeReminder class (manage.cpp/h)
    string filename = manage.selectOption();

    while (reminderText.empty()) {
        cout << "Please enter a new reminder: ";
        getline(cin, reminderText);
    }

    // Access files class to get a free id to use for a reminder
    ManageFile files;
    int nextId = files.getNextId(filename);

    Reminder remind;
    remind.id = nextId;
    remind.text = reminderText;
    remind.completed = false;

    // Use a Info struct to create an Info object
    Info information;
    information.filename = filename;
    information.reminder = remind;

    return information;
}


