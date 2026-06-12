#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class recommendationSystem
{
private:
    unordered_map<int, unordered_set<int>> graph; 
public:
    void setGraph(const unordered_map<int, unordered_set<int>>& g);
    vector<int> recommend(int userId, int limit = 10);
private:
    int score(int userId, int candidate);
};