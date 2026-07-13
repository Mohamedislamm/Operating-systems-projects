#include <cassert>
#include <iostream>
#include "BigReal/BigReal.h"

int main() {
    BigReal a("12.34");
    BigReal b("5.6");
    BigReal c("-3.0");

    assert((a + b) == BigReal("17.94"));
    assert((a - b) == BigReal("6.74"));
    assert((a > b));
    assert(!(a < b));
    assert(BigReal::isValid("123.456"));
    assert(!BigReal::isValid("12..34"));
    assert((c == BigReal("-3.0")));

    std::cout << "All BigReal tests passed." << std::endl;
    return 0;
}
