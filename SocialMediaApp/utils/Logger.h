#pragma once
#include <string>
using namespace std;
class logger
{
public:
    static void info(
        const string& msg
    );
    static void warning(
        const string& msg
    );
    static void error(
        const string& msg
    );
};