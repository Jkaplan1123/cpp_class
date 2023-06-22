#ifndef __ILLEGAL_TRUST_WITHDRAWAL_EXCEPTION_H__
#define __ILLEGAL_TRUST_WITHDRAWAL_EXCEPTION_H__
// #include <exception>

class IllegalTrustWithdrawalException : public std::exception
{
public:
    IllegalTrustWithdrawalException() noexcept = default;
    ~IllegalTrustWithdrawalException() = default;

    virtual const char *what() const noexcept override {
        return "Illegal Trust Withdrawal Exception";
    }
};

#endif // __ILLEGAL_TRUST_WITHDRAWAL_EXCEPTION_H__