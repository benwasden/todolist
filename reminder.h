#pragma once
#include <string>
#include "files.h"

// Create MakeReminder class
class MakeReminder {
public:
    struct Info {
        std::string filename;
        Reminder reminder;
    };

    Info addReminder();
};
