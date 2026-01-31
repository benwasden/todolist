#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "reminder.h"
#include "files.h"
#include "manage.h"
using namespace std;

void clearScreen();

int main()
{
    int choice = 0;

    while (choice != 5) {
        clearScreen();
        cout << "---Reminders Application---\n";
        cout << "Please select an option from the following list:\n";
        cout << "1. Create a new reminder\n2. View all reminders\n3. View reminders by list\n4. Delete Completed Goals\n5. Exit\n";
        cout << "Make a selection: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                clearScreen();
                MakeReminder reminder;
                auto newReminder = reminder.addReminder();

                ManageFile file;
                file.writeFile(newReminder.filename, newReminder.reminder);
                cout << "Successfully added!\n";
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            case 2: {
                clearScreen();
                ManageFile files;
                vector<Reminder> genFile = files.readAllFiles();
                if (!genFile.empty()) {
                    cout << "---All Reminders---\n";
                    for (const auto& pair : genFile) {
                        string result;
                        if (pair.completed == 1) {
                            result = "C";
                        } else {
                            result = "X";
                        };
                        cout << pair.text << " - [" << result << "]" << endl;
                    };
                } else {
                    cout << "No reminders have been entered.\n";
                };
                cout << "Press Enter to continue..." << flush;
                cin.ignore();
                cin.get();
                break;
            }
            case 3: {
                clearScreen();
                Manage manage;
                string selection = manage.selectOption();
                vector<int> reminderIndex = manage.requestedGoals(selection);
                if (!reminderIndex.empty()) {
                    
                };
                cout << "Press Enter to continue..." << flush;
                cin.ignore();
                cin.get();
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                clearScreen();
                cout << "Thanks for using the Reminders app!\n";
                return 0;
            }
            default: {
                cout << "Please enter a valid selection\n" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }
};

void clearScreen() {
    cout << "\033[2J\033[1;1H" << flush;
};
