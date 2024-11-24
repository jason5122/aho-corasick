#include "test_runner.h"

#include "src/ac.h"
#include "src/ac_util.h"

#include <cassert>

bool TestRunner::run() {
    int total = 0;
    int fail = 0;

    for (size_t i = 0; i < tests.size(); ++i) {
        TestCase& t = tests[i];
        ac_t* ac = ac_create(t.dict);

        std::println(">Test {}", i + 1);
        std::print("Dictionary: [");
        for (size_t j = 0; j < t.dict.size(); ++j) {
            if (j == t.dict.size() - 1) {
                std::print("{}", t.dict[j]);
            } else {
                std::print("{}, ", t.dict[j]);
            }
        }
        std::println("]");

        for (size_t j = 0; j < t.strpairs.size(); ++j, ++total) {
            const StrPair& sp = t.strpairs[j];
            std::string str = sp.str;
            std::optional<std::string> match = sp.match;

            std::print("[{}] Testing '{}' : ", total, str);

            int len = str.length();
            ac_result_t r = ac_match(ac, str.data(), len);

            int m_b = r.match_begin;
            int m_e = r.match_end;

            // The return value per se is insane.
            if (m_b > m_e || ((m_b < 0 || m_e < 0) && (m_b != -1 || m_e != -1))) {
                std::println("Insane return value ({}, {})", m_b, m_e);
                fail++;
                continue;
            }

            // If the string is not supposed to match the dictionary.
            if (!match) {
                if (m_b != -1 || m_e != -1) {
                    fail++;
                    std::println("Not Supposed to match ({}, {})", m_b, m_e);
                } else {
                    std::println("Pass");
                }
                continue;
            }

            // The string or its substring is match the dict.
            if (m_b >= len || m_b >= len) {
                fail++;
                std::println("Return value >= the length of the string ({}, {})", m_b, m_e);
                continue;
            } else {
                int mlen = (*match).length();
                if ((mlen != m_e - m_b + 1) || strncmp(str.data() + m_b, (*match).data(), mlen)) {
                    fail++;
                    std::println("Fail");
                } else {
                    std::println("Pass");
                }
            }
        }
        std::println("");
        ac_free(ac);
    }

    std::println("Test case count: {}, fail: {}", total, fail);
    return fail == 0;
}

void TestRunner::addTestCase(const TestCase& test_case) {
    tests.emplace_back(test_case);
}
