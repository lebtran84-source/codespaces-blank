#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/realtime/NotificationSystem.h"
#include <iostream>
#include <algorithm>
using namespace std;
void notificationsystem::load()
{
    auto data = database::load_notifications();
    for (auto& n : data)
    {
        userNotiMap[n.receiverid].push_back(n);
        counter = max(counter, n.id);
    }
}
void notificationsystem::notify(int receiverId, int senderId, const string& message)
{
    notification n(
        ++counter,
        receiverId,
        senderId,
        message,
        "now"
    );
    userNotiMap[receiverId].push_back(n);
    database::save_notification(n);
}
void notificationsystem::showNotifications(int userId)
{
    cout << "===== NOTIFICATIONS =====\n";

    if (userNotiMap[userId].empty())
    {
        cout << "No notifications\n";
        return;
    }
    auto& list = userNotiMap[userId];

    for (auto it = list.rbegin(); it != list.rend(); ++it)
    {
        cout << (it->isRead ? "[READ] " : "[NEW] ");
        cout << it->message << "\n";
    }
}
void notificationsystem::markAsRead(int userId, int notiId)
{
    auto& list = userNotiMap[userId];
    for (auto& n : list)
    {
        if (n.id == notiId)
        {
            n.isRead = true;
            break;
        }
    }
}