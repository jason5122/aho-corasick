#include "test/test_runner.h"

TestCase test1{
    .dict = {"he", "she", "his", "her"},
    .strpairs = {{"he", "he"},
                 {"she", "she"},
                 {"his", "his"},
                 {"hers", "he"},
                 {"ahe", "he"},
                 {"shhe", "he"},
                 {"shis2", "his"},
                 {"ahhe", "he"}},
};
TestCase test2{.dict = {"poto", "poto"}, .strpairs = {{"The pot had a handle", std::nullopt}}};
TestCase test3{.dict = {"The"}, .strpairs = {{"The pot had a handle", "The"}}};
TestCase test4{.dict = {"pot"}, .strpairs = {{"The pot had a handle", "pot"}}};
TestCase test5{.dict = {"pot "}, .strpairs = {{"The pot had a handle", "pot "}}};
TestCase test6{.dict = {"ot h"}, .strpairs = {{"The pot had a handle", "ot h"}}};
TestCase test7{.dict = {"andle"}, .strpairs = {{"The pot had a handle", "andle"}}};
TestCase test8{.dict = {"aaab"}, .strpairs = {{"aaaaaaab", "aaab"}}};
TestCase test9{.dict = {"haha", "z"}, .strpairs = {{"aaaaz", "z"}, {"z", "z"}}};
TestCase test10{.dict = {"abc"}, .strpairs = {{"cde", std::nullopt}}};
TestCase test11{
    .dict = {"‼️", "ØØ"},
    .strpairs = {{"hello‼️", "‼️"}, {"asdf", std::nullopt}, {"ØØØ", "ØØ"}, {"Ø", std::nullopt}},
};
TestCase test12{
    .dict = {"abc﷽def"},
    .strpairs =
        {
            {"hello﷽worldabc﷽abc﷽def", "abc﷽def"},
            {"abc\x{EF}\x{B7}\x{BD}def", "abc﷽def"},
            {"abc\x{EF}\x{B7}\x{B7}\x{BD}def", std::nullopt},
            {"abc\x{EF}\x{B7}\x{BD}def\x{BD}", "abc﷽def"},
        },
};
TestCase test13{.dict = {""}, .strpairs = {{"", std::nullopt}, {"abc", std::nullopt}}};
TestCase test14{.dict = {"3"}, .strpairs = {{"abc123", "3"}, {"3", "3"}}};

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
    tests.addTestCase(test12);
    tests.addTestCase(test13);
    tests.addTestCase(test14);
    return tests.run() ? 0 : 1;
};
