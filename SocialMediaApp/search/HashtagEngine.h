#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;
class hashtagengine
{
private:
    unordered_map<string, unordered_set<int>> tagIndex;
public:
    void add(int postId, const vector<string>& tags);
    vector<int> search(const string& tag) const;
    void removePost(int postId);
    void clear();
};