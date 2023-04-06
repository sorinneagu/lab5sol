#pragma once

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>

class BigInteger {
public:
    BigInteger();
    BigInteger(const std::string& str);
    BigInteger(const BigInteger& other);
    ~BigInteger();

    int sgn() const;

    bool operator==(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;

    BigInteger& operator=(const BigInteger& other);
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);

    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;

    BigInteger& operator++(); // pre-increment
    BigInteger operator++(int); // post-increment

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& number);

    void prependZeros(std::string& str, size_t numOfZeros) const;
    void negate();
    std::string add(const std::string& a, const std::string& b) const;
    std::string sub(const std::string& a, const std::string& b) const;
    std::string digitize(const std::string& str, bool isNeg = false) const;

private:
    std::string m_data;
    int sign;
};

#endif
