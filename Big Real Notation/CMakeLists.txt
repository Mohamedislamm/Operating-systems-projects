cmake_minimum_required(VERSION 3.16)
project(BigRealNotation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(BigReal STATIC src/BigReal.cpp)
target_include_directories(BigReal PUBLIC include)

add_executable(bigreal_demo examples/demo.cpp)
target_link_libraries(bigreal_demo PRIVATE BigReal)

add_executable(bigreal_tests tests/test_bigreal.cpp)
target_link_libraries(bigreal_tests PRIVATE BigReal)

enable_testing()
add_test(NAME BigRealTests COMMAND bigreal_tests)

function(add_assignment target source)
    add_executable(${target} ${source})
    if(MSVC)
        target_compile_options(${target} PRIVATE /utf-8)
    endif()
endfunction()

add_assignment(q01_sentence_formatting assignments/q01_sentence_formatting.cpp)
add_assignment(q02_inclusive_speech assignments/q02_inclusive_speech.cpp)
add_assignment(q03_split assignments/q03_split.cpp)
add_assignment(q04_primes assignments/q04_primes.cpp)
add_assignment(q05_high_score assignments/q05_high_score.cpp)
add_assignment(q06a_binary assignments/q06a_binary.cpp)
add_assignment(q06b_binary_strings assignments/q06b_binary_strings.cpp)
add_assignment(q07_domino assignments/q07_domino.cpp)
add_assignment(q08_pattern assignments/q08_pattern.cpp)
add_assignment(q09_bears assignments/q09_bears.cpp)
add_assignment(q10_word_replace assignments/q10_word_replace.cpp)
add_assignment(q11_file_compare assignments/q11_file_compare.cpp)
add_assignment(q12_phishing assignments/q12_phishing.cpp)
