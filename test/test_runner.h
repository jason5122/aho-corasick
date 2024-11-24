#pragma once

#include "test/std_print.h"
#include <optional>
#include <string>
#include <vector>

struct StrPair {
    std::string str;
    std::optional<std::string> match;
};

struct TestCase {
    std::vector<std::string> dict;
    std::vector<StrPair> strpairs;
};

class TestRunner {
public:
    bool run();
    void addTestCase(const TestCase& test_case);

private:
    std::vector<TestCase> tests;
};
