#include "test_runner.h"

std::vector<std::string> dict1 = {"he", "she", "his", "her"};
std::vector<StrPair> strpair1 = {{"he", "he"},  {"she", "she"}, {"his", "his"},   {"hers", "he"},
                                 {"ahe", "he"}, {"shhe", "he"}, {"shis2", "his"}, {"ahhe", "he"}};
TestCase test1{"test 1", dict1, strpair1};

std::vector<std::string> dict2 = {"poto", "poto"}; /* duplicated strings*/
std::vector<StrPair> strpair2 = {{"The pot had a handle", std::nullopt}};
TestCase test2{"test 2", dict2, strpair2};

std::vector<std::string> dict3 = {"The"};
std::vector<StrPair> strpair3 = {{"The pot had a handle", "The"}};
TestCase test3{"test 3", dict3, strpair3};

std::vector<std::string> dict4 = {"pot"};
std::vector<StrPair> strpair4 = {{"The pot had a handle", "pot"}};
TestCase test4{"test 4", dict4, strpair4};

std::vector<std::string> dict5 = {"pot "};
std::vector<StrPair> strpair5 = {{"The pot had a handle", "pot "}};
TestCase test5{"test 5", dict5, strpair5};

std::vector<std::string> dict6 = {"ot h"};
std::vector<StrPair> strpair6 = {{"The pot had a handle", "ot h"}};
TestCase test6{"test 6", dict6, strpair6};

std::vector<std::string> dict7 = {"andle"};
std::vector<StrPair> strpair7 = {{"The pot had a handle", "andle"}};
TestCase test7{"test 7", dict7, strpair7};

std::vector<std::string> dict8 = {"aaab"};
std::vector<StrPair> strpair8 = {{"aaaaaaab", "aaab"}};
TestCase test8{"test 8", dict8, strpair8};

std::vector<std::string> dict9 = {"haha", "z"};
std::vector<StrPair> strpair9 = {{"aaaaz", "z"}, {"z", "z"}};
TestCase test9{"test 9", dict9, strpair9};

std::vector<std::string> dict10 = {"abc"};
std::vector<StrPair> strpair10 = {{"cde", std::nullopt}};
TestCase test10{"test 10", dict10, strpair10};

std::vector<std::string> dict11 = {"‼️", "ØØ"};
std::vector<StrPair> strpair11 = {
    {"asdlfjadlskfjklads‼️", "‼️"}, {"asdf", std::nullopt}, {"ØØØ", "ØØ"}, {"Ø", std::nullopt}};
TestCase test11{"test 11", dict11, strpair11};

int main(int argc, char** argv) {
    TestRunner tests;
    tests.addTestCase(test1);
    tests.addTestCase(test2);
    tests.addTestCase(test3);
    tests.addTestCase(test4);
    tests.addTestCase(test5);
    tests.addTestCase(test6);
    tests.addTestCase(test7);
    tests.addTestCase(test8);
    tests.addTestCase(test9);
    tests.addTestCase(test10);
    tests.addTestCase(test11);
    return tests.run() ? 0 : 1;
};
