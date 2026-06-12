#pragma once
#include <string>
#include <vector>
using namespace std;
class contentparser
{
public:
    static string normalize(const string& text);
    static vector<string> extractWords(const string& text);
    static vector<string> extractHashtags(const string& text);
    static vector<string> extractMentions(const string& text);
};