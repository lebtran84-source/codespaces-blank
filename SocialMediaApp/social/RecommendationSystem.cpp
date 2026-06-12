#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/social/RecommendationSystem.h"
#include <algorithm>
void recommendationSystem::setGraph(const unordered_map<int, unordered_set<int>>& g)
{
    graph = g;
}
int recommendationSystem::score(int userId, int candidate)
{
    if (userId == candidate) return 0;
    const auto& myFollowings = graph[userId];
    if (myFollowings.count(candidate)) return 0;

    int s = 0;

    // Candidate follows me
    if (graph.count(candidate) && graph.at(candidate).count(userId))
    {
        s += 5;
    }

    // Candidate is followed by someone I follow
    for (int f : myFollowings)
    {
        if (graph.count(f) && graph.at(f).count(candidate))
        {
            s += 3;
        }
    }

    return s;
}
vector<int> recommendationSystem::recommend(int userId, int limit)
{
    unordered_map<int, int> scores;
    const auto& myFollowings = graph[userId];

    for (auto& [user, _] : graph)
    {
        if (user == userId) continue;
        if (myFollowings.count(user)) continue;
        int s = score(userId, user);
        if (s > 0)
            scores[user] = s;
    }

    vector<pair<int,int>> sorted(scores.begin(), scores.end());
    sort(sorted.begin(), sorted.end(),
        [](auto& a, auto& b)
        {
            return a.second > b.second;
        });

    vector<int> result;
    for (int i = 0; i < sorted.size() && i < limit; i++)
        result.push_back(sorted[i].first);
    return result;
}