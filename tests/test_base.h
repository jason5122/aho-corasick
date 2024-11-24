#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string>

class ACTestBase {
public:
    ACTestBase(const char* name) : _banner(name) {}
    virtual void PrintBanner() {
        fprintf(stdout, "\n===== %s ====\n", _banner.c_str());
    }

    virtual bool Run() = 0;

private:
    std::string _banner;
};

bool Run_AC_Simple_Test();
