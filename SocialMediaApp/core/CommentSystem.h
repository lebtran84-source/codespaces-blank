#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/Comment.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/Database.h"
using namespace std;
class commentsystem
{
private:
    unordered_map<int, comment> comments;
    unordered_map<int, vector<int>> postComments; 
    int commentCounter = 0;

public:
    void load();
    const unordered_map<int, comment>& getComments() const;
    int addComment(int userId, int postId, const string& text, int parentId = -1);
    void deleteComment(int userId, int commentId);
    void viewComments(int postId);
};
