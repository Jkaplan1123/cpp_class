#ifndef __INSUFFICIENT_FUNDS_EXCEPTION_H__
#define __INSUFFICIENT_FUNDS_EXCEPTION_H__
#include <exception>

class InsufficientFundsException : public std::exception
{
public:
    InsufficientFundsException() noexcept = default;
    ~InsufficientFundsException() = default;

    virtual const char *what() const noexcept override {
        return "Insufficient Funds Exception";
    }
};

#endif // __INSUFFICIENT_FUNDS_EXCEPTION_H__