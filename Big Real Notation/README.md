# BigReal Notation — OOP Assignment 2

**Course:** CS213 — Object-Oriented Programming  
**Institution:** Faculty of Computers and Artificial Intelligence, Cairo University  
**Supervisor:** Dr. Mohamed El-Ramly  

**Team Members:**

| Name | ID | Tasks |
|------|----|-------|
| Belal Mohamed Youness | 20220087 | Constructor, `>`, `<` operators |
| Mohamed Gamal Abd El-Nasser | 20221119 | `+`, `-`, padding |
| Mohamed Islam Khaled | 20220282 | `=`, `<<`, `>>`, `isValid` |

---

## Project Overview

This project implements a `BigReal` class for arbitrary-precision real number arithmetic in C++.
Numbers are stored as strings internally to preserve precision far beyond standard floating-point limits.

Alongside the core library, the project includes standalone solutions for all 12 questions of
OOP Assignment 2.

---

## Project Structure

```
BigRealNotation/
├── include/
│   └── BigReal/
│       └── BigReal.h           # BigReal class declaration
├── src/
│   └── BigReal.cpp             # BigReal class implementation
├── examples/
│   └── demo.cpp                # Interactive demo of BigReal operations
├── tests/
│   └── test_bigreal.cpp        # Regression tests for BigReal
├── assignments/                # Assignment 2 question solutions (Q1–Q12)
│   ├── q01_sentence_formatting.cpp
│   ├── q02_inclusive_speech.cpp
│   ├── q03_split.cpp
│   ├── q04_primes.cpp
│   ├── q05_high_score.cpp
│   ├── q06a_binary.cpp
│   ├── q06b_binary_strings.cpp
│   ├── q07_domino.cpp
│   ├── q08_pattern.cpp
│   ├── q09_bears.cpp
│   ├── q10_word_replace.cpp
│   ├── q11_file_compare.cpp
│   └── q12_phishing.cpp
├── data/
│   ├── file_compare/           # Sample files for Q11 (text1.txt, text2.txt)
│   └── word_replace/           # Input files for Q10 (input.txt, mapinput.txt)
├── CMakeLists.txt
├── Requirements.pdf            # Original assignment specification
└── README.md
```

---

## BigReal Class

### Features

- Parse signed decimal strings of arbitrary length (e.g., `"632145269.3698745"`)
- Addition (`+`) and subtraction (`-`) with correct sign handling
- Comparison operators: `<`, `>`, `==`, `!=`
- Input validation via `BigReal::isValid()`
- Stream operators: `<<` (output) and `>>` (input)

### API Summary

```cpp
BigReal();                                // Default: 0.0
BigReal(std::string value);               // Construct from string

static bool isValid(const std::string& value);  // Validate numeric string

BigReal operator+(const BigReal& other) const;
BigReal operator-(const BigReal& other) const;
bool    operator<(const BigReal& other) const;
bool    operator>(const BigReal& other) const;
bool    operator==(const BigReal& other) const;
bool    operator!=(const BigReal& other) const;

friend std::ostream& operator<<(std::ostream&, const BigReal&);
friend std::istream& operator>>(std::istream&, BigReal&);
```

### Usage Example

```cpp
#include "BigReal/BigReal.h"

BigReal a("632145269.3698745");
BigReal b("-254789631.3698747");

BigReal sum  = a + b;
BigReal diff = a - b;

std::cout << sum  << std::endl;           // 377355638
std::cout << (a < b) << std::endl;        // 0 (false)
std::cout << BigReal::isValid("123.456"); // 1 (true)
```

---

## Assignment Solutions

| Executable | Question | Author | Description |
|------------|----------|--------|-------------|
| `q01_sentence_formatting` | Q1  | Belal Youness | Sentence capitalization and whitespace normalization |
| `q02_inclusive_speech`    | Q2  | Mohamed Islam | Male-to-inclusive pronoun replacement (`he/him → he or she / him or her`) |
| `q03_split`               | Q3  | Mohamed Gamal | String split by a delimiter |
| `q04_primes`              | Q4  | Belal Youness | Sieve of Eratosthenes — prints all primes up to N |
| `q05_high_score`          | Q5  | Mohamed Islam | Interactive high-score manager (add, list top 10, search) |
| `q06a_binary`             | Q6A | Mohamed Gamal | Decimal to binary converter (recursive) |
| `q06b_binary_strings`     | Q6B | Mohamed Gamal | Generate all binary strings of length k |
| `q07_domino`              | Q7  | Belal Youness | Domino chain solver (backtracking) |
| `q08_pattern`             | Q8  | Mohamed Islam | Recursive asterisk pattern printer |
| `q09_bears`               | Q9  | Mohamed Gamal | Bears puzzle solver (recursive) |
| `q10_word_replace`        | Q10 | Belal Youness | Word replacement from a mapping file (supports Arabic via wide streams) |
| `q11_file_compare`        | Q11 | Mohamed Islam | File comparison char-by-char or word-by-word |
| `q12_phishing`            | Q12 | Mohamed Gamal | Phishing term detector and scorer for text files |

---

## Build Instructions

### Requirements

- **Compiler:** C++17-compliant (GCC 7+, Clang 5+, or MSVC 2017+)
- **Build system:** CMake 3.16 or later

### Steps

```bash
# 1. Configure
cmake -S . -B build

# 2. Build all targets
cmake --build build

# On Windows with MSVC you can also open build/BigRealNotation.sln in Visual Studio
```

---

## Running the Programs

### BigReal Demo

```bash
./build/bigreal_demo
```

### BigReal Tests

```bash
./build/bigreal_tests
# or via CTest:
ctest --test-dir build --verbose
```

### Assignment Programs

```bash
# Q1 — Sentence formatting
./build/q01_sentence_formatting

# Q3 — String split
./build/q03_split

# Q4 — Primes up to N
./build/q04_primes

# Q6A — Decimal to binary
./build/q06a_binary

# Q6B — Binary strings of length k
./build/q06b_binary_strings

# Q7 — Domino chain (hardcoded test set in main)
./build/q07_domino

# Q8 — Asterisk pattern
./build/q08_pattern

# Q9 — Bears puzzle
./build/q09_bears

# Q10 — Word replace (reads data/word_replace/input.txt and mapinput.txt)
# IMPORTANT: run from the project root so the data/ paths resolve correctly
./build/q10_word_replace

# Q11 — File compare (prompts for two file paths)
./build/q11_file_compare
# Sample files: data/file_compare/text1.txt  data/file_compare/text2.txt

# Q12 — Phishing detector (prompts for a .txt file path)
./build/q12_phishing
```

---

## Implementation Notes

- **BigReal internals:** Numbers are split into `integerPart` and `fractionalPart` (both `std::string`) plus a `bool negative`. Arithmetic is performed by aligning decimal places and operating digit-by-digit, similar to long addition/subtraction by hand.
- **Q10 (Word Replace):** Uses `wifstream`/`wofstream` with wide strings to handle Unicode (Arabic) text. Run from the project root so relative paths to `data/word_replace/` resolve correctly.
- **Q11 (File Compare):** Prompts the user to enter two file paths at runtime. Sample test files are in `data/file_compare/`.
- **Q12 (Phishing):** Scores a text file against a built-in dictionary of phishing phrases, each weighted by likelihood.

---

## References

- Assignment specification: [`Requirements.pdf`](Requirements.pdf)
