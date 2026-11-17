#pragma once
#include <ostream>
#include <string>
#include <utility>

class StudentRecord {
private:
    std::string name_;
    double gpa_ = 0.0;

public:
    StudentRecord() = default;
    StudentRecord(std::string name, double gpa)
        : name_(std::move(name)), gpa_(gpa) {}

    const std::string& getName() const { return name_; }
    double getGpa() const { return gpa_; }

    explicit operator double() const { return gpa_; }

    bool operator<(const StudentRecord& other) const {
        if (gpa_ != other.gpa_) return gpa_ < other.gpa_;
        return name_ < other.name_;
    }

    bool operator==(const StudentRecord& other) const {
        return gpa_ == other.gpa_ && name_ == other.name_;
    }

    bool operator!=(const StudentRecord& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const StudentRecord& s) {
        os << s.name_ << " (" << s.gpa_ << ")";
        return os;
    }
};
