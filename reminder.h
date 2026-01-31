#pragma once
#include <string>
#include "files.h"  // gives access to Reminder and ManageFile

class MakeReminder {
public:
    struct Info {
        std::string filename;
        Reminder reminder;
    };

    Info addReminder();
};
