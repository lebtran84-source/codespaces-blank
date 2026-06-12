#pragma onc
#include <vector>
#include <unordered_map>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/Post.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/Database.h"
using namespace std;
class feedsystem
{
private:
    unordered_map<int, post> posts;
public:
    void loadPosts();
    vector<int> getFeed(int userId);
    void printFeed(int userId);
};