#include <cassert>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#include "ac.h"
#include "ac_util.h"
#include "test_base.h"

namespace {
struct StrPair {
    std::string str;
    std::optional<std::string> match;
};

struct TestingCase {
    std::string name;
    std::vector<std::string> dict;
    std::vector<StrPair> strpairs;
};

class Tests {
public:
    Tests(std::string_view name,
          const std::vector<std::string>& dict,
          const std::vector<StrPair>& strpairs) {
        if (!_tests) _tests = new std::vector<TestingCase>;

        TestingCase tc;
        tc.name = name;
        tc.dict = dict;
        tc.strpairs = strpairs;
        _tests->push_back(tc);
    }

    static std::vector<TestingCase>* Get_Tests() {
        return _tests;
    }

private:
    static std::vector<TestingCase>* _tests;
};

std::vector<TestingCase>* Tests::_tests = 0;

class ACTestSimple {
public:
    ACTestSimple(const char* banner) {}
    virtual bool Run();

private:
    void PrintSummary(int total, int fail) {
        fprintf(stdout, "Test case count: %d, fail: %d\n", total, fail);
        fflush(stdout);
    }
};
}  // namespace

bool ACTestSimple::Run() {
    int total = 0;
    int fail = 0;

    std::vector<TestingCase>* tests = Tests::Get_Tests();
    if (!tests) {
        PrintSummary(0, 0);
        return true;
    }

    for (auto i = tests->begin(), e = tests->end(); i != e; i++) {
        TestingCase& t = *i;
        int dict_len = t.dict.size();
        unsigned int* strlen_v = new unsigned int[dict_len];

        fprintf(stdout, ">Testing %s\nDictionary:[ ", t.name.data());
        for (int i = 0, need_break = 0; i < dict_len; i++) {
            const std::string& s = t.dict[i];
            fprintf(stdout, "%s, ", s.data());
            strlen_v[i] = s.length();
            if (need_break++ == 16) {
                fputs("\n  ", stdout);
                need_break = 0;
            }
        }
        fputs("]\n", stdout);

        // TODO: Refactor this.
        std::vector<std::string> dict;
        for (int i = 0; i < dict_len; i++) {
            dict.emplace_back(t.dict[i]);
        }

        /* Create the dictionary */
        ac_t* ac = ac_create(dict);
        delete[] strlen_v;

        for (int ii = 0, ee = t.strpairs.size(); ii < ee; ii++, total++) {
            const StrPair& sp = t.strpairs[ii];
            std::string str = sp.str;
            std::optional<std::string> match = sp.match;

            fprintf(stdout, "[%3d] Testing '%s' : ", total, str.data());

            int len = str.length();
            ac_result_t r = ac_match(ac, str.data(), len);

            int m_b = r.match_begin;
            int m_e = r.match_end;

            // The return value per se is insane.
            if (m_b > m_e || ((m_b < 0 || m_e < 0) && (m_b != -1 || m_e != -1))) {
                fprintf(stdout, "Insane return value (%d, %d)\n", m_b, m_e);
                fail++;
                continue;
            }

            // If the string is not supposed to match the dictionary.
            if (!match) {
                if (m_b != -1 || m_e != -1) {
                    fail++;
                    fprintf(stdout, "Not Supposed to match (%d, %d) \n", m_b, m_e);
                } else fputs("Pass\n", stdout);
                continue;
            }

            // The string or its substring is match the dict.
            if (m_b >= len || m_b >= len) {
                fail++;
                fprintf(stdout, "Return value >= the length of the string (%d, %d)\n", m_b, m_e);
                continue;
            } else {
                int mlen = (*match).length();
                if ((mlen != m_e - m_b + 1) || strncmp(str.data() + m_b, (*match).data(), mlen)) {
                    fail++;
                    fprintf(stdout, "Fail\n");
                } else fprintf(stdout, "Pass\n");
            }
        }
        fputs("\n", stdout);
        ac_free(ac);
    }

    PrintSummary(total, fail);
    return fail == 0;
}

bool Run_AC_Simple_Test() {
    ACTestSimple t("AC Simple test");
    return t.Run();
}

//////////////////////////////////////////////////////////////////////////////
//
//    Testing cases for first-match variant (i.e. test ac_match())
//
//////////////////////////////////////////////////////////////////////////////
//

/* test 1*/
std::vector<std::string> dict1 = {"he", "she", "his", "her"};
std::vector<StrPair> strpair1 = {{"he", "he"},  {"she", "she"}, {"his", "his"},   {"hers", "he"},
                                 {"ahe", "he"}, {"shhe", "he"}, {"shis2", "his"}, {"ahhe", "he"}};
Tests test1("test 1", dict1, strpair1);

/* test 2*/
std::vector<std::string> dict2 = {"poto", "poto"}; /* duplicated strings*/
std::vector<StrPair> strpair2 = {{"The pot had a handle", std::nullopt}};
Tests test2("test 2", dict2, strpair2);

/* test 3*/
std::vector<std::string> dict3 = {"The"};
std::vector<StrPair> strpair3 = {{"The pot had a handle", "The"}};
Tests test3("test 3", dict3, strpair3);

/* test 4*/
std::vector<std::string> dict4 = {"pot"};
std::vector<StrPair> strpair4 = {{"The pot had a handle", "pot"}};
Tests test4("test 4", dict4, strpair4);

/* test 5*/
std::vector<std::string> dict5 = {"pot "};
std::vector<StrPair> strpair5 = {{"The pot had a handle", "pot "}};
Tests test5("test 5", dict5, strpair5);

/* test 6*/
std::vector<std::string> dict6 = {"ot h"};
std::vector<StrPair> strpair6 = {{"The pot had a handle", "ot h"}};
Tests test6("test 6", dict6, strpair6);

/* test 7*/
std::vector<std::string> dict7 = {"andle"};
std::vector<StrPair> strpair7 = {{"The pot had a handle", "andle"}};
Tests test7("test 7", dict7, strpair7);

std::vector<std::string> dict8 = {"aaab"};
std::vector<StrPair> strpair8 = {{"aaaaaaab", "aaab"}};
Tests test8("test 8", dict8, strpair8);

std::vector<std::string> dict9 = {"haha", "z"};
std::vector<StrPair> strpair9 = {{"aaaaz", "z"}, {"z", "z"}};
Tests test9("test 9", dict9, strpair9);

/* test the case when input string doesn't contain even a single char
 * of the pattern in dictionary.
 */
std::vector<std::string> dict10 = {"abc"};
std::vector<StrPair> strpair10 = {{"cde", std::nullopt}};
Tests test10("test 10", dict10, strpair10);

/* test 11*/
std::vector<std::string> dict11 = {"‼️", "ØØ"};
std::vector<StrPair> strpair11 = {
    {"asdlfjadlskfjklads‼️", "‼️"}, {"asdf", std::nullopt}, {"ØØØ", "ØØ"}, {"Ø", std::nullopt}};
Tests test11("test 11", dict11, strpair11);
