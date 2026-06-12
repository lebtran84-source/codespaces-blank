#pragma once
#include <string>
#include <unordered_set>
using namespace std;
class profanityfilter
{
private:
    static unordered_set<string> badWords;

public:
    static void loadBadWords(const string& filename);
    static bool isClean(const string& text);
    static string clean(const string& text);
};