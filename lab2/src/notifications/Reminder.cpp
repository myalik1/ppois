#include "../../include/notifications/Reminder.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

Reminder::Reminder(std::string id, std::string docId, std::string userId, int dueHour)
    : reminderId_(std::move(id)),
      documentId_(std::move(docId)),
      targetUserId_(std::move(userId)),
      dueHour_(dueHour) {}

bool Reminder::isOverdue(int currentHour) const {
    return currentHour > dueHour_;
}

void Reminder::reschedule(int newDueHour) {
    if (newDueHour <= dueHour_) {
        throw InvalidDocumentDataException("New due hour must be greater than current due hour");
    }
    dueHour_ = newDueHour;
}

int Reminder::getDueHour() const {
    return dueHour_;
}

}
