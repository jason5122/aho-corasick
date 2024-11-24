#include "test_runner.h"

#include "ac.h"
#include "ac_util.h"

#include <cassert>
#include <string>
#include <vector>

bool TestRunner::run() {
    int total = 0;
    int fail = 0;

    for (auto i = tests.begin(), e = tests.end(); i != e; i++) {
        TestCase& t = *i;
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

    std::println("Test case count: {}, fail: {}", total, fail);
    return fail == 0;
}

void TestRunner::addTestCase(const TestCase& test_case) {
    tests.emplace_back(test_case);
}
