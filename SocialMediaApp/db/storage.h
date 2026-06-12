#pragma once
#include <string>
#include <vector>
using namespace std;
class storage
{
public:
    static void write(const string& file, const string& line);
    static vector<string> read(const string& file);
    static void clear(const string& file);
};