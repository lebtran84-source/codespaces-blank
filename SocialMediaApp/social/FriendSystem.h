#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class friendSystem
{
private:
    unordered_map<int, unordered_set<int>> friends;
public:
 void load(
        const unordered_map<int, unordered_set<int>>& graph
    );
    void addFriend(int userId, int friendId);
    void removeFriend(int userId, int friendId);
    bool isFriend(int userId, int friendId) const;
    unordered_set<int> getFriends(int userId) const;
    vector<int> mutualFriends(int userId, int otherId) const;
     const unordered_map<int, unordered_set<int>>&
    getGraph() const;
    void clear();
};