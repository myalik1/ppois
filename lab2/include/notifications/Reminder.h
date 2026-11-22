#pragma once

#include <string>

namespace docflow {

class Reminder {
public:
    Reminder(std::string id, std::string docId, std::string userId, int dueHour);
    bool isOverdue(int currentHour) const;
    void reschedule(int newDueHour);
    int getDueHour() const;

private:
    std::string reminderId_;
    std::string documentId_;
    std::string targetUserId_;
    int dueHour_;
};

}
