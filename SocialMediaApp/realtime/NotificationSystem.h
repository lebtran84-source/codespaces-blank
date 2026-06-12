#pragma once
#include <vector>
#include <unordered_map>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/notification.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/Database.h"

using namespace std;

class notificationsystem
{
private:
    unordered_map<int, vector<notification>> userNotiMap;
    int counter = 0;

public:
    void load();
    void notify(int receiverId, int senderId, const string& message);
    void showNotifications(int userId);
    void markAsRead(int userId, int notiId);
};