#ifndef __ILLEGAL_BALANCE_EXCEPTION_H__
#define __ILLEGAL_BALANCE_EXCEPTION_H__
// #include <exception>

class IllegalBalanceException : public std::exception
{
public:
    IllegalBalanceException() noexcept = default;
    ~IllegalBalanceException() = default;

    // virtual const char *what() const noexcept override;

    virtual const char *what() const noexcept override{
        return "Illegal balance exception";
    };
};

#endif // __ILLEGAL_BALANCE_EXCEPTION_H__
