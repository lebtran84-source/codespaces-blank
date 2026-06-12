#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/app/Menu.h"
void displayMainMenu()
{
    cout << "\n===== SOCIAL MEDIA SYSTEM =====\n";
    cout << "1. User Management\n";
    cout << "2. Post Management\n";
    cout << "3. Search\n";
    cout << "4. Notifications\n";
    cout << "5. View Feed\n";
    cout << "6. Analytics\n";
    cout << "7. Logout\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}
void displayUserMenu()
{
    cout << "\n===== USER SYSTEM =====\n";
    cout << "1. View Profile\n";
    cout << "2. Search User\n";
    cout << "3. Follow\n";
    cout << "4. Unfollow\n";
    cout << "5. Recommendations\n";
    cout << "0. Back\n";
    cout << "Choice: ";
}
void displayPostMenu()
{
    cout << "\n===== POST SYSTEM =====\n";
    cout << "1. Create Post\n";
    cout << "2. View Post\n";
    cout << "3. My Posts\n";
    cout << "4. Edit Post\n";
    cout << "5. Delete Post\n";
    cout << "6. Like/Unlike\n";
    cout << "7. Comment\n";
    cout << "0. Back\n";
    cout << "Choice: ";
}
void displaySearchMenu()
{
    cout << "\n===== SEARCH SYSTEM =====\n";
    cout << "1. Search Post (keyword)\n";
    cout << "2. Search Post (hashtag)\n";
    cout << "3. Search User\n";
    cout << "0. Back\n";
    cout << "Choice: ";
}
void displayNotificationMenu()
{
    cout << "\n===== NOTIFICATIONS =====\n";
    cout << "1. View\n";
    cout << "2. Mark as read\n";
    cout << "0. Back\n";
    cout << "Choice: ";
}
void displayAuthMenu()
{
    cout << "\n===== AUTH SYSTEM =====\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}
void displayFeaturesInfo()
{
    cout << "\n===== FEATURES =====\n";

    cout << "\n[USER]\n";
    cout << "- Register/Login\n";
    cout << "- Follow/Unfollow\n";
    cout << "- Profile + Recommendations\n";

    cout << "\n[POST]\n";
    cout << "- Create/Edit/Delete\n";
    cout << "- Like/Comment\n";
    cout << "- Hashtag support\n";

    cout << "\n[SEARCH]\n";
    cout << "- Keyword search\n";
    cout << "- Hashtag search\n";
    cout << "- User search\n";

    cout << "\n[SYSTEM]\n";
    cout << "- Notifications\n";
    cout << "- Feed\n";
    cout << "- Analytics\n";
}