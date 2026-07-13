#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H

#include <iostream>
#include <string>

class BigReal {
public:
    BigReal();
    explicit BigReal(std::string value);

    static bool isValid(const std::string& value);

    bool operator<(const BigReal& other) const;
    bool operator>(const BigReal& other) const;
    bool operator==(const BigReal& other) const;
    bool operator!=(const BigReal& other) const;

    BigReal operator+(const BigReal& other) const;
    BigReal operator-(const BigReal& other) const;

    friend std::ostream& operator<<(std::ostream& out, const BigReal& value);
    friend std::istream& operator>>(std::istream& in, BigReal& value);

private:
    std::string integerPart;
    std::string fractionalPart;
    bool negative = false;

    void normalize();
    std::string toScaledDigits(int scale) const;
    static BigReal fromScaledDigits(const std::string& digits, int scale, bool negative);
    static int compareAbsoluteValues(const BigReal& left, const BigReal& right);
    static std::string addMagnitude(const std::string& left, const std::string& right);
    static std::string subtractMagnitude(const std::string& left, const std::string& right);
    static int compareMagnitude(const std::string& left, const std::string& right);
    static std::string trimLeadingZeros(const std::string& value);
    static std::string trimTrailingZeros(const std::string& value);
};

#endif
