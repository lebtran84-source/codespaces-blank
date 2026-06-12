#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;
class searchengine
{
private:
    unordered_map<string, unordered_set<int>> keywordIndex;

public:
    void add(int postId, const vector<string>& words);
    vector<int> search(const string& keyword) const;
    vector<int> multiSearch(const vector<string>& keywords) const;
    void removePost(int postId);
    void clear();
};