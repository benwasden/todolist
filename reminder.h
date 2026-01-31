#pragma once
#include <string>
#include "files.h"

class MakeReminder {
public:
    struct Info {
        std::string filename;
        Reminder reminder;
    };

    Info addReminder();
};
