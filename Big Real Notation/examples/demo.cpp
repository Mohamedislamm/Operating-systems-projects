#include <iostream>
#include "BigReal/BigReal.h"

int main() {
    std::cout << "=== BigReal Demo ===\n\n";

    BigReal a("12.34");
    BigReal b("5.6");
    std::cout << "Basic operations:\n";
    std::cout << "  a = " << a << ", b = " << b << '\n';
    std::cout << "  a + b = " << (a + b) << '\n';
    std::cout << "  a - b = " << (a - b) << '\n';
    std::cout << "  a < b: " << (a < b) << '\n';
    std::cout << "  a > b: " << (a > b) << '\n';
    std::cout << '\n';

    BigReal num1("632145269.3698745");
    BigReal num2("254789631.3698747");
    BigReal num3("-632145269.3698745");
    BigReal num4("-254789631.3698747");
    BigReal num5("50000000.555");
    BigReal num6("-3.0");

    std::cout << "Large number operations:\n";
    std::cout << "  num1 + num2 = " << (num1 + num2) << '\n';
    std::cout << "  num1 + num3 = " << (num1 + num3) << '\n';
    std::cout << "  num5 + num6 = " << (num5 + num6) << '\n';
    std::cout << "  num1 - num2 = " << (num1 - num2) << '\n';
    std::cout << "  num1 - num4 = " << (num1 - num4) << '\n';
    std::cout << "  num4 - num1 = " << (num4 - num1) << '\n';
    std::cout << "  num1 < num2: " << (num1 < num2) << '\n';
    std::cout << "  num1 > num2: " << (num1 > num2) << '\n';
    std::cout << "  num5 == num6: " << (num5 == num6) << '\n';
    std::cout << '\n';

    std::cout << "Validation:\n";
    std::cout << "  isValid(\"632145269.3698745\"): " << BigReal::isValid("632145269.3698745") << '\n';
    std::cout << "  isValid(\"+ 254789631.3698747\"): " << BigReal::isValid("+ 254789631.3698747") << '\n';
    std::cout << "  isValid(\"abc\"): " << BigReal::isValid("abc") << '\n';
    std::cout << "  isValid(\"1.2.3\"): " << BigReal::isValid("1.2.3") << '\n';

    return 0;
}
