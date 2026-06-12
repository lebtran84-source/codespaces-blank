#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/analytics/AnalyticsSystem.h"
#include <iostream>
#include <unordered_map>
using namespace std;
int analyticssystem::totalUsers(usersystem& us)
{
    return us.getUsers().size();
}
int analyticssystem::totalPosts(postsystem& ps)
{
    return ps.getPosts().size();
}
int analyticssystem::totalComments(commentsystem& cs)
{
    return cs.getComments().size();
}
int analyticssystem::totalLikes(postsystem& ps)
{
    int total = 0;
    for (auto& [id, p] : ps.getPosts())
    {
        total += p.likes.size();
    }
    return total;
}
int analyticssystem::mostLikedPost(postsystem& ps)
{
    int bestPost = -1;
    int bestLikes = -1;
    for (auto& [id, p] : ps.getPosts())
    {
        int likeCount = p.likes.size();
        if (likeCount > bestLikes)
        {
            bestLikes = likeCount;
            bestPost = id;
        }
    }
    return bestPost;
}
int analyticssystem::mostFollowedUser(usersystem& us)
{
    int bestUser = -1;
    int bestFollowers = -1;
    for (auto& [id, u] : us.getUsers())
    {
        int count = u.followers.size();
        if (count > bestFollowers)
        {
            bestFollowers = count;
            bestUser = id;
        }
    }
    return bestUser;
}
int analyticssystem::mostCommentedPost(postsystem& ps)
{
    int bestPost = -1;
    int bestComments = -1;
    for (auto& [id, p] : ps.getPosts())
    {
        int commentCount = p.commentids.size();
        if (commentCount > bestComments)
        {
            bestComments = commentCount;
            bestPost = id;
        }
    }
    return bestPost;
}
int analyticssystem::totalEngagement(postsystem& ps, commentsystem& cs)
{
    int total = 0;
    total += totalLikes(ps);
    total += totalComments(cs);
    return total;
}
pair<int, int> analyticssystem::topCommenter(commentsystem& cs)
{
    unordered_map<int, int> userCommentCount;
    for (auto& [id, c] : cs.getComments())
    {
        userCommentCount[c.authorid]++;
    }
    int bestUser = -1;
    int bestCount = -1;
    for (auto& [userId, count] : userCommentCount)
    {
        if (count > bestCount)
        {
            bestCount = count;
            bestUser = userId;
        }
    }
    return make_pair(bestUser, bestCount);
}
void analyticssystem::showDashboard(
    usersystem& us,
    postsystem& ps,
    commentsystem& cs
)
{
    cout << "\n===== ANALYTICS DASHBOARD =====\n";
    cout << "\n[BASIC STATS]\n";
    cout << "Total Users: " << totalUsers(us) << "\n";
    cout << "Total Posts: " << totalPosts(ps) << "\n";
    cout << "Total Comments: " << totalComments(cs) << "\n";
    cout << "Total Likes: " << totalLikes(ps) << "\n";
    
    cout << "\n[TOP POSTS]\n";
    int mostLiked = mostLikedPost(ps);
    if (mostLiked != -1)
    {
        cout << "Most Liked Post: ID " << mostLiked 
             << " (" << ps.getPosts().at(mostLiked).likes.size() << " likes)\n";
    }
    int mostCommented = mostCommentedPost(ps);
    if (mostCommented != -1)
    {
        cout << "Most Commented Post: ID " << mostCommented 
             << " (" << ps.getPosts().at(mostCommented).commentids.size() << " comments)\n";
    }
    
    cout << "\n[TOP USERS]\n";
    int mostFollowed = mostFollowedUser(us);
    if (mostFollowed != -1)
    {
        cout << "Most Followed User: ID " << mostFollowed 
             << " (" << us.getUsers().at(mostFollowed).followers.size() << " followers)\n";
    }
    auto [topUser, topCount] = topCommenter(cs);
    if (topUser != -1)
    {
        cout << "Top Commenter: User " << topUser 
             << " (" << topCount << " comments)\n";
    }
    cout << "\n";
}