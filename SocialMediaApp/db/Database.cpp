#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/Database.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/file_paths.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/storage.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/utils.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/notification.h"
#include <sstream>
using namespace std;
void database::save_user(const user& u)
{
    string line =
        to_string(u.id) + "|" +
        u.username + "|" +
        u.password + "|" +
        utils::join_int(vector<int>(u.followers.begin(), u.followers.end())) + "|" +
        utils::join_int(vector<int>(u.followings.begin(), u.followings.end()));
    storage::write(USER_FILE, line);
}
vector<user> database::load_users()
{
    vector<user> res;
    auto lines = storage::read(USER_FILE);
    for (auto& line : lines)
    {
        stringstream ss(line);
        string id, username, password, followers, following;
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, followers, '|');
        getline(ss, following, '|');
        if (id.empty()) continue;
        user u(stoi(id), username, password);
        for (int f : utils::split_int(followers))
            u.followers.insert(f);
        for (int f : utils::split_int(following))
            u.followings.insert(f);
        res.push_back(u);
    }
    return res;
}
void database::save_post(const post& p)
{
    string line =
        to_string(p.id) + "|" +
        to_string(p.authorid) + "|" +
        p.content + "|" +
        utils::join_str(p.hashtags) + "|" +
        utils::join_int(vector<int>(p.likes.begin(), p.likes.end())) + "|" +
        utils::join_int(p.commentids) + "|" +
        p.createdat;
    storage::write(POST_FILE, line);
}
vector<post> database::load_posts()
{
    vector<post> res;
    auto lines = storage::read(POST_FILE);
    for (auto& line : lines)
    {
        stringstream ss(line);
        string id, authorid, content, tags, likes, comments, createdat;
        getline(ss, id, '|');
        getline(ss, authorid, '|');
        getline(ss, content, '|');
        getline(ss, tags, '|');
        getline(ss, likes, '|');
        getline(ss, comments, '|');
        getline(ss, createdat, '|');
        if (id.empty()) continue;
        post p(stoi(id), stoi(authorid), content, createdat);
        for (auto& t : utils::split_str(tags))
            p.hashtags.insert(t);
        for (int l : utils::split_int(likes))
            p.likes.insert(l);
        for (int c : utils::split_int(comments))
            p.commentids.push_back(c);

        res.push_back(p);
    }
    return res;
}
void database::save_comment(const comment& c)
{
    // format: id|postid|authorid|content|parentid|createdat
    string line =
        to_string(c.id) + "|" +
        to_string(c.postid) + "|" +
        to_string(c.authorid) + "|" +
        c.content + "|" +
        to_string(c.parentid) + "|" +
        c.createdat;
    storage::write(COMMENT_FILE, line);
}
vector<comment> database::load_comments()
{
    vector<comment> res;
    auto lines = storage::read(COMMENT_FILE);
    for (auto& line : lines)
    {
        stringstream ss(line);
        string id, postid, authorid, content, parentid, createdat;
        getline(ss, id, '|');
        getline(ss, postid, '|');
        getline(ss, authorid, '|');
        getline(ss, content, '|');
        if (!getline(ss, parentid, '|'))
            parentid = "";
        if (!getline(ss, createdat, '|'))
            createdat = "";

        if (id.empty()) continue;

        if (createdat.empty() && !parentid.empty() && (parentid.find_first_not_of("-0123456789") != string::npos))
        {
            // legacy format: id|postid|authorid|content|createdat
            createdat = parentid;
            parentid = "-1";
        }

        comment c(
            stoi(id),
            stoi(postid),
            stoi(authorid),
            content,
            createdat.empty() ? "now" : createdat
        );

        int parsedParent = -1;
        if (!parentid.empty())
        {
            try
            {
                parsedParent = stoi(parentid);
            }
            catch (...) { parsedParent = -1; }
        }
        c.parentid = parsedParent;
        res.push_back(c);
    }
    return res;
}
void database::clear_file(const string& file)
{
    storage::clear(file);
}
void database::save_notification(const notification& n)
{
    string line =
        to_string(n.id) + "|" +
        to_string(n.receiverid) + "|" +
        to_string(n.senderid) + "|" +
        n.message + "|" +
        (n.isRead ? "1" : "0") + "|" +
        n.createdAt;
    storage::write(NOTIFICATION_FILE, line);
}
vector<notification> database::load_notifications()
{
    vector<notification> res;
    auto lines = storage::read(NOTIFICATION_FILE);
    for (auto& line : lines)
    {
        stringstream ss(line);
        string id, receiverid, senderid, message, isRead, createdAt;
        getline(ss, id, '|');
        getline(ss, receiverid, '|');
        getline(ss, senderid, '|');
        getline(ss, message, '|');
        getline(ss, isRead, '|');
        getline(ss, createdAt, '|');
        if (id.empty()) continue;
        notification n(
            stoi(id),
            stoi(receiverid),
            stoi(senderid),
            message,
            createdAt
        );
        n.isRead = (isRead == "1");
        res.push_back(n);
    }
    return res;
}