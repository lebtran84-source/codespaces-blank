#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/User.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/Post.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/Comment.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/notification.h"
using namespace std;
class database
{
public:
    static void save_user(const user& u);
    static vector<user> load_users();
    static void save_post(const post& p);
    static vector<post> load_posts();
    static void save_comment(const comment& c);
    static vector<comment> load_comments();
    static void clear_file(const string& file);
    static void save_notification(const notification& n);
    static vector<notification> load_notifications();
};