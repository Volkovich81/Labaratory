#ifndef VALIDATION_EXCEPTION_H
#define VALIDATION_EXCEPTION_H

#include <stdexcept>
#include <string>

class ValidationException : public std::exception {
private:
    std::string message;

public:
    explicit ValidationException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif