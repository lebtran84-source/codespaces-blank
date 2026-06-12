#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/feed/feedsystem.h"
#include <iostream>
#include <algorithm>
using namespace std;
void feedsystem::loadPosts()
{
    auto data = database::load_posts();
    for (auto& p : data)
    {
        posts[p.id] = p;
    }
}
int scorePost(const post& p)
{
    int likeScore = p.likes.size() * 2;
    int commentScore = p.commentids.size();
    return likeScore + commentScore;
}
vector<int> feedsystem::getFeed(int userId)
{
    vector<pair<int,int>> ranked; 
    for (auto& [id, p] : posts)
    {
        int score = p.likes.size() * 2 + p.commentids.size();
        ranked.push_back({score, id});
    }

    sort(ranked.begin(), ranked.end(),
        [](auto& a, auto& b)
        {
            return a.first > b.first;
        });

    vector<int> feed;
    for (auto& x : ranked)
        feed.push_back(x.second);
    return feed;
}
void feedsystem::printFeed(int userId)
{
    auto feed = getFeed(userId);
    cout << "===== YOUR FEED =====\n";
    for (int id : feed)
    {
        auto& p = posts[id];
        cout << "Post ID: " << p.id << "\n";
        cout << "Author: " << p.authorid << "\n";
        cout << "Content: " << p.content << "\n";
        cout << "Likes: " << p.likes.size() << "\n";
        cout << "----------------------\n";
    }
}
