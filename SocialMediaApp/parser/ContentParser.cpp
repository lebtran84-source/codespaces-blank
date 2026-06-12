#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/parser/ContentParser.h"
#include <sstream>
#include <cctype>
string contentparser::normalize(const string& text)
{
    string res;
    for (char c : text)
        res += tolower(c);
    return res;
}
vector<string> contentparser::extractWords(const string& text)
{
    vector<string> res;
    stringstream ss(text);
    string word;
    while (ss >> word)
    {
        res.push_back(word);
    }
    return res;
}
vector<string> contentparser::extractHashtags(const string& text)
{
    vector<string> res;
    stringstream ss(text);
    string word;
    while (ss >> word)
    {
        if (!word.empty() && word[0] == '#')
        {
            res.push_back(word.substr(1));
        }
    }
    return res;
}
vector<string> contentparser::extractMentions(const string& text)
{
    vector<string> res;
    stringstream ss(text);
    string word;
    while (ss >> word)
    {
        if (!word.empty() && word[0] == '@')
        {
            res.push_back(word.substr(1));
        }
    }
    return res;
}