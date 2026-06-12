#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/social/FriendSystem.h"
void friendSystem::load(
    const unordered_map<int, unordered_set<int>>& graph
)
{
    friends = graph;
}
const unordered_map<int, unordered_set<int>>&
friendSystem::getGraph() const
{
    return friends;
}
void friendSystem::addFriend(int userId, int friendId)
{
    if (userId == friendId) return;
    friends[userId].insert(friendId);
    friends[friendId].insert(userId);
}
void friendSystem::removeFriend(int userId, int friendId)
{
    friends[userId].erase(friendId);
    friends[friendId].erase(userId);
}
bool friendSystem::isFriend(int userId, int friendId) const
{
    auto it = friends.find(userId);
    if (it == friends.end())
        return false;
    return it->second.find(friendId) != it->second.end();
}
unordered_set<int> friendSystem::getFriends(int userId) const
{
    auto it = friends.find(userId);
    if (it == friends.end())
        return {};
    return it->second;
}
vector<int> friendSystem::mutualFriends(int userId, int otherId) const
{
    vector<int> res;
    auto a = friends.find(userId);
    auto b = friends.find(otherId);
    if (a == friends.end() || b == friends.end())
        return res;
    const auto& small = (a->second.size() < b->second.size()) ? a->second : b->second;
    const auto& big   = (a->second.size() < b->second.size()) ? b->second : a->second;

    for (int f : small)
    {
        if (big.count(f))
            res.push_back(f);
    }
    return res;
}
void friendSystem::clear()
{
    friends.clear();
}