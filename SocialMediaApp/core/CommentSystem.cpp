#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/CommentSystem.h"
#include <iostream>
#include <functional>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/parser/ProfanityFilter.h"
using namespace std;
void commentsystem::load()
{
    auto data = database::load_comments();
    for (auto& c : data)
    {
        comments[c.id] = c;
        postComments[c.postid].push_back(c.id);
        commentCounter = max(commentCounter, c.id);
    }
}
int commentsystem::addComment(int userId, int postId, const string& text, int parentId)
{
    bool hasBad = !profanityfilter::isClean(text);
    string cleanText = text;
    if (hasBad)
    {
        cout << "Warning: Your comment contains inappropriate words and was filtered.\n";
        cleanText = profanityfilter::clean(text);
    }
    int id = ++commentCounter;
    comment c(id, postId, userId, cleanText, "now");
    c.parentid = parentId;
    comments[id] = c;
    postComments[postId].push_back(id);
    database::save_comment(c);
    return id;
}
void commentsystem::deleteComment(int userId, int commentId)
{
    if (comments.find(commentId) == comments.end())
        return;
    auto& c = comments[commentId];
    if (c.authorid != userId)
        return;
    comments.erase(commentId);
}
void commentsystem::viewComments(int postId)
{
    if (postComments.find(postId) == postComments.end())
    {
        cout << "No comments\n";
        return;
    }

    unordered_map<int, vector<int>> children;
    for (int cid : postComments[postId])
    {
        int pid = comments[cid].parentid;
        children[pid].push_back(cid);
    }

    function<void(int,int)> print = [&](int parent, int indent)
    {
        if (children.find(parent) == children.end()) return;
        for (int cid : children[parent])
        {
            auto& c = comments[cid];
            string displayed = profanityfilter::clean(c.content);
            for (int i = 0; i < indent; ++i) cout << "  ";
            cout << "[" << cid << "] User " << c.authorid << ": " << displayed;
            if (c.parentid != -1)
                cout << " (reply to " << c.parentid << ")";
            cout << "\n";
            print(cid, indent+1);
        }
    };

    print(-1, 0);
}
const unordered_map<int, comment>&
commentsystem::getComments() const
{
    return comments;
}