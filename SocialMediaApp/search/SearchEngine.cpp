#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/search/SearchEngine.h"
void searchengine::add(int postId, const vector<string>& words)
{
    for (const auto& w : words)
    {
        keywordIndex[w].insert(postId);
    }
}
vector<int> searchengine::search(const string& keyword) const
{
    auto it = keywordIndex.find(keyword);
    if (it == keywordIndex.end())
        return {};
    return vector<int>(it->second.begin(), it->second.end());
}
vector<int> searchengine::multiSearch(const vector<string>& keywords) const
{
    unordered_set<int> result;
    for (const auto& k : keywords)
    {
        auto it = keywordIndex.find(k);
        if (it == keywordIndex.end()) continue;

        for (int id : it->second)
            result.insert(id);
    }
    return vector<int>(result.begin(), result.end());
}
void searchengine::removePost(int postId)
{
    for (auto& [word, posts] : keywordIndex)
    {
        posts.erase(postId);
    }
}
void searchengine::clear()
{
    keywordIndex.clear();
}