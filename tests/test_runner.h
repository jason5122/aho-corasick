#pragma once

#include "util/std_print.h"

struct StrPair {
    std::string str;
    std::optional<std::string> match;
};

struct TestCase {
    std::string name;
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
