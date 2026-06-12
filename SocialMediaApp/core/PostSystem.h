#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/Post.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/Database.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/search/HashtagEngine.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/search/SearchEngine.h"
using namespace std;
extern searchengine searchEngine;
extern hashtagengine hashtagEngine;
class postsystem
{
private:
    unordered_map<int, post> posts;
    unordered_map<string, vector<int>> keywordIndex;
    unordered_map<string, vector<int>> hashtagIndex;

    int postCounter = 0;
public:
    void load();
    int createPost(int authorId, const string& content);
    void deletePost(int userId, int postId);
    void editPost(int userId, int postId, const string& content);
    void addCommentToPost(int postId, int commentId);

    const unordered_map<int, post>& getPosts() const;
    void toggleLike(int userId, int postId);
    void viewPost(int postId);
    void viewMyPosts(int userId);
    void viewPostsByUser(int userId) const;
    void searchPost(const string& keyword);
    void searchByHashtag(const string& tag);
    void viewFeed(int userId);
};