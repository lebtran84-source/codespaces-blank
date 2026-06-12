#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/search/HashtagEngine.h"
void hashtagengine::add(int postId, const vector<string>& tags)
{
    for (const auto& t : tags)
    {
        tagIndex[t].insert(postId);
    }
}
vector<int> hashtagengine::search(const string& tag) const
{
    auto it = tagIndex.find(tag);
    if (it == tagIndex.end())
        return {};
    return vector<int>(it->second.begin(), it->second.end());
}
void hashtagengine::removePost(int postId)
{
    for (auto& [tag, posts] : tagIndex)
    {
        posts.erase(postId);
    }
}
void hashtagengine::clear()
{
    tagIndex.clear();
}