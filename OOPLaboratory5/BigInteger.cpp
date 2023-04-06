#include "BigInteger.h"

#include <cctype> // for isdigit
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

BigInteger::BigInteger() : m_data("0") {
}

BigInteger::BigInteger(const std::string& str) {}

BigInteger::BigInteger(const BigInteger& other) : m_data(other.m_data) {}

BigInteger::~BigInteger() {}

int BigInteger::sgn() const {
    if (m_data == "0")
        return 0;
    else if (m_data[0] == '-')
        return -1;
    else
        return 1;
    return 1;
}

// Helper function to prepend zeros to a string
void BigInteger::prependZeros(std::string& str, size_t numOfZeros) const {
    str = std::string(numOfZeros, '0') + str;
}

void BigInteger::negate() {
    if (m_data == "0") {
        // Do nothing, the sign of zero is already zero
    }
    else if (m_data[0] == '-') {
        m_data = m_data.substr(1);
    }
    else {
        m_data = "-" + m_data;
    }
}


//helper function for add
std::string BigInteger::add(const std::string& a, const std::string& b) const {
    std::string result;
    int carry = 0, sum = 0;
    int i = a.size() - 1, j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? (a[i--] - '0') : 0;
        int digitB = (j >= 0) ? (b[j--] - '0') : 0;
        sum = digitA + digitB + carry;
        carry = sum / 10;
        sum %= 10;
        result = static_cast<char>(sum + '0') + result;
    }

    return result;
}

// Helper function to subtract two positive strings
std::string BigInteger::sub(const std::string& a, const std::string& b) const {
    std::string result;
    int borrow = 0, diff = 0;
    int i = a.size() - 1, j = b.size() - 1;

    while (i >= 0 || j >= 0) {
        int digitA = (i >= 0) ? (a[i--] - '0') : 0;
        int digitB = (j >= 0) ? (b[j--] - '0') : 0;
        diff = digitA - digitB - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result = static_cast<char>(diff + '0') + result;
    }

    return result;
}

// Helper function to convert a string to its digitized form
std::string BigInteger::digitize(const std::string& str, bool isNeg) const {
    std::string result = str;
    if (result == "-0") {
        result = "0";
    }
    if (isNeg) {
        BigInteger temp(result);
        temp.negate();
        result = temp.to_string();
    }
    return result;
}

bool BigInteger::operator==(const BigInteger& other) const {
    return m_data == other.m_data;
}

bool BigInteger::operator<(const BigInteger& other) const {
    if (sgn() != other.sgn())
        return sgn() < other.sgn();

    if (m_data.size() != other.m_data.size())
        return sgn() == 1 ? m_data.size() < other.m_data.size() : m_data.size() > other.m_data.size();

    return sgn() == 1 ? m_data < other.m_data : m_data > other.m_data;
}

bool BigInteger::operator<=(const BigInteger& other) const {
    return (*this < other) || (*this == other);
}

bool BigInteger::operator>(const BigInteger& other) const {
    return !(*this <= other);
}

bool BigInteger::operator>=(const BigInteger& other) const {
    return !(*this < other);
}

BigInteger& BigInteger::operator=(const BigInteger& other)
{
    if (this != &other)
    {
        m_data = other.m_data;
    }
    return *this;
}

BigInteger& BigInteger::operator +=(const BigInteger& other)
{
    std::string sum;
    int carry = 0, i = m_data.size() - 1, j = other.m_data.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int digit1 = (i >= 0) ? (m_data[i--] - '0') : 0;
        int digit2 = (j >= 0) ? (other.m_data[j--] - '0') : 0;
        int digitSum = digit1 + digit2 + carry;
        sum.insert(sum.begin(), (digitSum % 10) + '0');
        carry = digitSum / 10;
    }
    m_data = sum;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other)
{
    std::string diff;
    int borrow = 0, i = m_data.size() - 1, j = other.m_data.size() - 1;
    while (i >= 0 || j >= 0)
    {
        int digit1 = (i >= 0) ? (m_data[i--] - '0') : 0;
        int digit2 = (j >= 0) ? (other.m_data[j--] - '0') : 0;
        int digitDiff = digit1 - digit2 - borrow;
        if (digitDiff < 0)
        {
            digitDiff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        diff.insert(diff.begin(), digitDiff + '0');
    }
    while (diff.size() > 1 && diff[0] == '0')
    {
        diff.erase(diff.begin());
    }
    m_data = diff;
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    std::string sum;

    int carry = 0;
    int i = m_data.length() - 1;
    int j = other.m_data.length() - 1;

    while (i >= 0 || j >= 0 || carry != 0) {
        int digit = carry;
        if (i >= 0) {
            digit += m_data[i] - '0';
            i--;
        }
        if (j >= 0) {
            digit += other.m_data[j] - '0';
            j--;
        }
        carry = digit / 10;
        digit %= 10;
        sum.insert(0, 1, digit + '0');
    }

    return BigInteger(sum);
}

// Subtraction operator
BigInteger BigInteger::operator-(const BigInteger& other) const {
    std::string difference;

    int borrow = 0;
    int i = m_data.length() - 1;
    int j = other.m_data.length() - 1;

    while (i >= 0 || j >= 0) {
        int digit = borrow;
        if (i >= 0) {
            digit += m_data[i] - '0';
            i--;
        }
        if (j >= 0) {
            digit -= other.m_data[j] - '0';
            j--;
        }
        if (digit < 0) {
            digit += 10;
            borrow = -1;
        }
        else {
            borrow = 0;
        }
        difference.insert(0, 1, digit + '0');
    }

    // Remove leading zeros
    while (difference.length() > 1 && difference[0] == '0') {
        difference.erase(0, 1);
    }

    return BigInteger(difference);
}

// Pre-increment operator
BigInteger& BigInteger::operator++()
{
    // Check if the number is negative
    bool isNeg = (sgn() == -1);

    // Convert the number to digitized form
    std::string digits = digitize(m_data, isNeg);

    // Increment the digits by 1
    int carry = 1;
    for (int i = digits.size() - 1; i >= 0 && carry > 0; i--)
    {
        int digit = digits[i] - '0';
        digit += carry;
        carry = digit / 10;
        digit %= 10;
        digits[i] = digit + '0';
    }

    // If there's a carry, prepend a '1'
    if (carry > 0)
    {
        digits = '1' + digits;
    }

    // Convert the number back to its original form
    m_data = digitize(digits, isNeg);

    return *this;
}


// Post-increment operator
BigInteger BigInteger::operator++(int) {
    BigInteger temp(*this);
    ++(*this);
    return temp;
}

// Conversion to string
std::string BigInteger::to_string() const {
    return m_data;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const BigInteger& number) {
    os << number.to_string();
    return os;
}
