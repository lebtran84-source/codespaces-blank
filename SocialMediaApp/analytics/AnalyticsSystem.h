#pragma once
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/UserSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/PostSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/CommentSystem.h"
#include <vector>
#include <utility>
using namespace std;

class analyticssystem
{
public:
    static int totalUsers(usersystem& us);
    static int totalPosts(postsystem& ps);
    static int totalComments(commentsystem& cs);
    static int totalLikes(postsystem& ps);
    static int mostLikedPost(postsystem& ps);
    static int mostFollowedUser(usersystem& us);
    static int mostCommentedPost(postsystem& ps);
    static int totalEngagement(postsystem& ps, commentsystem& cs);
    static pair<int, int> topCommenter(commentsystem& cs);
    static void showDashboard(
        usersystem& us,
        postsystem& ps,
        commentsystem& cs
    );
};