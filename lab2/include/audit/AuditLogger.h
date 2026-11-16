#pragma once

#include "../core/User.h"
#include "../documents/Document.h"
#include "AuditEntry.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class AuditLogger {
public:
    AuditLogger(std::string loggerName, std::size_t maxEntries);
    void recordAction(const User& actor, const Document& document, const std::string& action);
    std::size_t countActionsByUser(const std::string& userId) const;
    void clearOldEntries(std::size_t keepCount);
    std::size_t getEntriesCount() const;

private:
    std::string loggerName_;
    std::size_t maxEntries_;
    std::vector<AuditEntry> entries_;
};

}
