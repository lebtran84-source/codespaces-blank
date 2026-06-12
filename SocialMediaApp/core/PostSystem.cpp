#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/PostSystem.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/parser/ContentParser.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/parser/ProfanityFilter.h"
using namespace std;
searchengine searchEngine;
hashtagengine hashtagEngine;
void postsystem::load()
{
    auto data = database::load_posts();
    for (auto& p : data)
    {
        posts[p.id] = p;
        postCounter = max(postCounter, p.id);
        vector<string> tags(p.hashtags.begin(), p.hashtags.end());
        hashtagEngine.add(p.id, tags);
        for (auto& tag : tags)
            hashtagIndex[tag].push_back(p.id);
        auto words = contentparser::extractWords(p.content);
        searchEngine.add(p.id, words);
        for (auto& w : words)
            keywordIndex[w].push_back(p.id);
    }
}
int postsystem::createPost(int authorId, const string& content)
{
    int id = ++postCounter;
    bool hasBadWords = !profanityfilter::isClean(content);
    string cleanContent = content;
    if (hasBadWords)
    {
        cout << "Warning: Your post contains inappropriate words and was filtered.\n";
        cleanContent = profanityfilter::clean(content);
    }
    auto tags = contentparser::extractHashtags(cleanContent);
    auto words = contentparser::extractWords(cleanContent);
    post p(id, authorId, cleanContent, "now");
    for (auto& tag : tags)
    {
        p.hashtags.insert(tag);
        hashtagIndex[tag].push_back(id);
    }
    for (auto& w : words)
    {
        keywordIndex[w].push_back(id);
    }

    searchEngine.add(id, words);
    hashtagEngine.add(id, tags);
    posts[id] = p;
    database::save_post(p);

    return id;
}
void postsystem::deletePost(int userId, int postId)
{
    if (posts.find(postId) == posts.end()) return;
    if (posts[postId].authorid != userId) return;
    posts.erase(postId);
    searchEngine.removePost(postId);
    hashtagEngine.removePost(postId);
}
void postsystem::editPost(int userId, int postId, const string& content)
{
    if (posts.find(postId) == posts.end()) return;

    auto& p = posts[postId];

    if (p.authorid != userId) return;
    for (auto& w : contentparser::extractWords(p.content))
    {
        auto& vec = keywordIndex[w];
        vec.erase(std::remove(vec.begin(), vec.end(), postId), vec.end());
    }
    for (auto& tag : p.hashtags)
    {
        auto& vec = hashtagIndex[tag];
        vec.erase(std::remove(vec.begin(), vec.end(), postId), vec.end());
    }
    searchEngine.removePost(postId);
    hashtagEngine.removePost(postId);
    p.content = content;
    auto tags = contentparser::extractHashtags(content);
    auto words = contentparser::extractWords(content);
    p.hashtags.clear();
    for (auto& tag : tags)
    {
        p.hashtags.insert(tag);
        hashtagIndex[tag].push_back(postId);
    }
    for (auto& w : words)
    {
        keywordIndex[w].push_back(postId);
    }
    searchEngine.add(postId, words);
    hashtagEngine.add(postId, tags);

    database::save_post(p);
}
void postsystem::addCommentToPost(int postId, int commentId)
{
    if (posts.find(postId) == posts.end()) return;
    auto& p = posts[postId];
    p.commentids.push_back(commentId);
    database::save_post(p);
}
void postsystem::toggleLike(int userId, int postId)
{
    if (posts.find(postId) == posts.end()) return;
    auto& p = posts[postId];
    if (p.likes.count(userId))
        p.likes.erase(userId);
    else
        p.likes.insert(userId);
    database::save_post(p);
}
void postsystem::viewPost(int postId)
{
    if (posts.find(postId) == posts.end()) return;
    auto& p = posts[postId];
    cout << "Post ID: " << p.id << "\n";
    cout << "Author: " << p.authorid << "\n";
    cout << "Content: " << p.content << "\n";
    cout << "Likes: " << p.likes.size() << "\n";
    cout << "Comments: " << p.commentids.size() << "\n";
}
void postsystem::viewMyPosts(int userId)
{
    for (auto& [id, p] : posts)
    {
        if (p.authorid == userId)
            cout << p.id << " | " << p.content << "\n";
    }
}
void postsystem::viewPostsByUser(int userId) const
{
    bool found = false;
    for (auto& [id, p] : posts)
    {
        if (p.authorid == userId)
        {
            cout << "Post ID: " << p.id << " | Content: " << p.content << "\n";
            found = true;
        }
    }
    if (!found)
        cout << "No posts from this user\n";
}
void postsystem::searchPost(const string& keyword)
{
    if (keywordIndex.find(keyword) == keywordIndex.end())
    {
        cout << "No posts found\n";
        return;
    }

    for (int id : keywordIndex[keyword])
        cout << posts[id].content << "\n";
}
void postsystem::searchByHashtag(const string& tag)
{
    if (hashtagIndex.find(tag) == hashtagIndex.end())
    {
        cout << "No hashtag found\n";
        return;
    }

    for (int id : hashtagIndex[tag])
        cout << posts[id].content << "\n";
}
void postsystem::viewFeed(int userId)
{
    for (auto& [id, p] : posts)
        cout << p.id << " | " << p.content << "\n";
}
const unordered_map<int, post>&
postsystem::getPosts() const
{
    return posts;
}