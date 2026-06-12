#pragma once

#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/UserSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/PostSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/CommentSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/social/FriendSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/realtime/NotificationSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/analytics/AnalyticsSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/app/Menu.h"

class appcontroller
{
private:
    usersystem userSys;
    postsystem postSys;
    commentsystem commentSys;
    friendSystem friendSys;
    notificationsystem notiSys;
    int currentUserId = -1;
public:
    void init();
    void run();
    void runAuth();       
    void handleMainMenu();
    void handleUserMenu();
    void handlePostMenu();
    void handleSearchMenu();
    void handleNotificationMenu();
    void showFeed();
};