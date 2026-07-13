#include "BigReal/BigReal.h"

#include <algorithm>
#include <cctype>
#include <utility>

BigReal::BigReal() : integerPart("0"), fractionalPart("0"), negative(false) {}

BigReal::BigReal(std::string value) : integerPart("0"), fractionalPart("0"), negative(false) {
    if (!isValid(value)) {
        return;
    }

    std::string input = std::move(value);
    if (!input.empty() && (input[0] == '+' || input[0] == '-')) {
        negative = input[0] == '-';
        input.erase(0, 1);
    }

    const std::size_t dotPos = input.find('.');
    if (dotPos != std::string::npos) {
        integerPart = input.substr(0, dotPos);
        fractionalPart = input.substr(dotPos + 1);
    } else {
        integerPart = input;
        fractionalPart = "0";
    }

    if (integerPart.empty()) {
        integerPart = "0";
    }
    if (fractionalPart.empty()) {
        fractionalPart = "0";
    }
    normalize();
}

bool BigReal::isValid(const std::string& value) {
    if (value.empty()) {
        return false;
    }

    std::size_t index = 0;
    if (value[0] == '+' || value[0] == '-') {
        index = 1;
        if (index >= value.size()) {
            return false;
        }
    }

    bool seenDigit = false;
    bool seenDot = false;
    for (; index < value.size(); ++index) {
        const char ch = value[index];
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            seenDigit = true;
        } else if (ch == '.') {
            if (seenDot) {
                return false;
            }
            seenDot = true;
        } else {
            return false;
        }
    }

    return seenDigit;
}

bool BigReal::operator<(const BigReal& other) const {
    if (negative != other.negative) {
        return negative;
    }

    const int cmp = compareAbsoluteValues(*this, other);
    if (negative) {
        return cmp > 0;
    }
    return cmp < 0;
}

bool BigReal::operator>(const BigReal& other) const {
    if (negative != other.negative) {
        return other.negative;
    }

    const int cmp = compareAbsoluteValues(*this, other);
    if (negative) {
        return cmp < 0;
    }
    return cmp > 0;
}

bool BigReal::operator==(const BigReal& other) const {
    return negative == other.negative && integerPart == other.integerPart && fractionalPart == other.fractionalPart;
}

bool BigReal::operator!=(const BigReal& other) const {
    return !(*this == other);
}

BigReal BigReal::operator+(const BigReal& other) const {
    if (negative == other.negative) {
        const int scale = std::max(fractionalPart.size(), other.fractionalPart.size());
        const std::string leftDigits = toScaledDigits(scale);
        const std::string rightDigits = other.toScaledDigits(scale);
        return BigReal::fromScaledDigits(addMagnitude(leftDigits, rightDigits), scale, negative);
    }

    const int scale = std::max(fractionalPart.size(), other.fractionalPart.size());
    const std::string leftDigits = toScaledDigits(scale);
    const std::string rightDigits = other.toScaledDigits(scale);
    const int cmp = compareMagnitude(leftDigits, rightDigits);
    if (cmp == 0) {
        return BigReal("0");
    }

    const std::string magnitude = cmp > 0 ? subtractMagnitude(leftDigits, rightDigits)
                                         : subtractMagnitude(rightDigits, leftDigits);
    const bool isNegative = cmp > 0 ? negative : other.negative;
    return BigReal::fromScaledDigits(magnitude, scale, isNegative);
}

BigReal BigReal::operator-(const BigReal& other) const {
    BigReal otherSigned = other;
    otherSigned.negative = !otherSigned.negative;
    return *this + otherSigned;
}

std::ostream& operator<<(std::ostream& out, const BigReal& value) {
    if (value.negative && !(value.integerPart == "0" && value.fractionalPart == "0")) {
        out << '-';
    }
    out << value.integerPart;
    if (value.fractionalPart != "0") {
        out << '.' << value.fractionalPart;
    }
    return out;
}

std::istream& operator>>(std::istream& in, BigReal& value) {
    std::string raw;
    in >> raw;
    value = BigReal(raw);
    return in;
}

BigReal BigReal::fromScaledDigits(const std::string& digits, int scale, bool negative) {
    BigReal result;
    result.negative = negative;
    if (digits.empty()) {
        return result;
    }

    std::string magnitude = trimLeadingZeros(digits);
    if (magnitude.size() <= static_cast<std::size_t>(scale)) {
        result.integerPart = "0";
        result.fractionalPart = std::string(static_cast<std::size_t>(scale) - magnitude.size(), '0') + magnitude;
    } else {
        result.integerPart = magnitude.substr(0, magnitude.size() - static_cast<std::size_t>(scale));
        result.fractionalPart = magnitude.substr(magnitude.size() - static_cast<std::size_t>(scale));
    }

    result.normalize();
    return result;
}

int BigReal::compareAbsoluteValues(const BigReal& left, const BigReal& right) {
    const int scale = std::max(left.fractionalPart.size(), right.fractionalPart.size());
    std::string leftDigits = left.toScaledDigits(scale);
    std::string rightDigits = right.toScaledDigits(scale);
    return BigReal::compareMagnitude(leftDigits, rightDigits);
}

void BigReal::normalize() {
    integerPart = trimLeadingZeros(integerPart);
    if (integerPart.empty()) {
        integerPart = "0";
    }
    fractionalPart = trimTrailingZeros(fractionalPart);
    if (fractionalPart.empty()) {
        fractionalPart = "0";
    }
    if (integerPart == "0" && fractionalPart == "0") {
        negative = false;
    }
}

std::string BigReal::toScaledDigits(int scale) const {
    if (scale < 0) {
        scale = 0;
    }

    std::string digits = integerPart;
    if (digits.empty()) {
        digits = "0";
    }

    std::string fraction = fractionalPart;
    if (fraction.size() < static_cast<std::size_t>(scale)) {
        fraction.append(static_cast<std::size_t>(scale) - fraction.size(), '0');
    }
    digits += fraction;

    if (digits.empty()) {
        digits = "0";
    }
    return digits;
}

std::string BigReal::addMagnitude(const std::string& left, const std::string& right) {
    std::string a = trimLeadingZeros(left);
    std::string b = trimLeadingZeros(right);
    if (a.empty()) {
        a = "0";
    }
    if (b.empty()) {
        b = "0";
    }

    std::string result;
    result.reserve(std::max(a.size(), b.size()) + 1);
    int carry = 0;
    std::size_t i = a.size();
    std::size_t j = b.size();
    while (i > 0 || j > 0 || carry != 0) {
        int sum = carry;
        if (i > 0) {
            sum += a[--i] - '0';
        }
        if (j > 0) {
            sum += b[--j] - '0';
        }
        result.push_back(static_cast<char>('0' + (sum % 10)));
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

std::string BigReal::subtractMagnitude(const std::string& left, const std::string& right) {
    std::string a = trimLeadingZeros(left);
    std::string b = trimLeadingZeros(right);
    if (a.empty()) {
        a = "0";
    }
    if (b.empty()) {
        b = "0";
    }

    std::string result;
    result.reserve(std::max(a.size(), b.size()));
    int borrow = 0;
    std::size_t i = a.size();
    std::size_t j = b.size();
    while (i > 0) {
        int diff = (a[--i] - '0') - borrow;
        if (j > 0) {
            diff -= b[--j] - '0';
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(static_cast<char>('0' + diff));
    }
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

int BigReal::compareMagnitude(const std::string& left, const std::string& right) {
    const std::string a = trimLeadingZeros(left);
    const std::string b = trimLeadingZeros(right);
    if (a.size() != b.size()) {
        return a.size() < b.size() ? -1 : 1;
    }
    if (a == b) {
        return 0;
    }
    return a < b ? -1 : 1;
}

std::string BigReal::trimLeadingZeros(const std::string& value) {
    std::size_t start = 0;
    while (start < value.size() && value[start] == '0') {
        ++start;
    }
    if (start == value.size()) {
        return "0";
    }
    return value.substr(start);
}

std::string BigReal::trimTrailingZeros(const std::string& value) {
    std::size_t end = value.size();
    while (end > 0 && value[end - 1] == '0') {
        --end;
    }
    if (end == 0) {
        return "0";
    }
    return value.substr(0, end);
}
