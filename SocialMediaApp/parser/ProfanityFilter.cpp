#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/parser/ProfanityFilter.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
unordered_set<string> profanityfilter::badWords;
void profanityfilter::loadBadWords(const string& filename)
{
    ifstream file(filename);
    string word;
    while (getline(file, word))
    {
        if (!word.empty())
        {
            // replace punctuation with spaces so we can split into tokens
            for (char& c : word)
            {
                if (ispunct((unsigned char)c))
                    c = ' ';
                else
                    c = tolower((unsigned char)c);
            }
            string token;
            stringstream ss(word);
            while (ss >> token)
            {
                // trim surrounding punctuation (if any) and lowercasing already done
                size_t start = 0;
                while (start < token.size() && ispunct((unsigned char)token[start])) start++;
                size_t end = token.size();
                while (end > start && ispunct((unsigned char)token[end-1])) end--;
                string clean = token.substr(start, end - start);
                if (!clean.empty())
                    badWords.insert(clean);
            }
        }
    }
}
bool profanityfilter::isClean(const string& text)
{
    string word;
    stringstream ss(text);

    while (ss >> word)
    {
        for (char& c : word)
            c = tolower((unsigned char)c);
        size_t start = 0;
        while (start < word.size() && ispunct((unsigned char)word[start])) start++;
        size_t end = word.size();
        while (end > start && ispunct((unsigned char)word[end-1])) end--;
        string clean = word.substr(start, end - start);
        if (!clean.empty() && badWords.find(clean) != badWords.end())
            return false;
    }

    return true;
}
string profanityfilter::clean(const string& text)
{
    string result;
    string word;
    stringstream ss(text);

    while (ss >> word)
    {
        string lower = word;
        for (char& c : lower)
            c = tolower((unsigned char)c);
        size_t start = 0;
        while (start < lower.size() && ispunct((unsigned char)lower[start])) start++;
        size_t end = lower.size();
        while (end > start && ispunct((unsigned char)lower[end-1])) end--;
        string cleanToken = lower.substr(start, end - start);
        if (!cleanToken.empty() && badWords.find(cleanToken) != badWords.end())
        {
            result += "*** ";
        }
        else
        {
            result += word + " ";
        }
    }
    return result;
}