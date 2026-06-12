#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/core/UserSystem.h"
#include <iostream>

using namespace std;

void usersystem::load()
{
    auto data = database::load_users();
    unordered_map<int, unordered_set<int>> graph;
    for (auto& u : data)
    {
        users[u.id] = u;
        usernameMap[u.username] = u.id;
        graph[u.id] = u.followings;
    }

    friends.load(graph);
    recommender.setGraph(graph);
}

bool usersystem::registerUser(
    const string& username,
    const string& password
)
{
    if (usernameMap.find(username) != usernameMap.end())
        return false;
    int id = users.size() + 1;
    user u(id, username, password);
    users[id] = u;
    usernameMap[username] = id;
    database::save_user(u);
    return true;
}

int usersystem::login(
    const string& username,
    const string& password
)
{
    auto it = usernameMap.find(username);
    if (it == usernameMap.end())
        return -1;
    int id = it->second;
    if (users[id].password != password)
        return -1;
    currentUserId = id;
    return id;
}

void usersystem::logout()
{
    currentUserId = -1;
}

void usersystem::follow(
    int myId,
    int targetId
)
{
    if (myId == targetId)
        return;
    if (users.find(myId) == users.end())
        return;
    if (users.find(targetId) == users.end())
        return;
    if (users[myId].followings.count(targetId))
        return;
    users[myId].followings.insert(targetId);
    users[targetId].followers.insert(myId);
    friends.addFriend(myId, targetId);
    recommender.setGraph(
        friends.getGraph()
    );
}
void usersystem::unfollow(
    int myId,
    int targetId
)
{
    if (users.find(myId) == users.end())
        return;

    if (users.find(targetId) == users.end())
        return;
    users[myId].followings.erase(targetId);
    users[targetId].followers.erase(myId);
    friends.removeFriend(myId, targetId);
    recommender.setGraph(
        friends.getGraph()
    );
}
void usersystem::searchUser(
    const string& keyword
)
{
    bool found = false;
    for (auto& [id, u] : users)
    {
        if (u.username.find(keyword) != string::npos)
        {
            cout
                << "ID: "
                << u.id
                << " | Username: "
                << u.username
                << "\n";
            found = true;
        }
    }
    if (!found)
    {
        cout << "No user found\n";
    }
}
void usersystem::viewProfile(
    int id
)
{
    if (users.find(id) == users.end())
        return;
    auto& u = users[id];
    cout << "\n===== PROFILE =====\n";
    cout << "ID: "
         << u.id
         << "\n";
    cout << "Username: "
         << u.username
         << "\n";
    cout << "Followers: "
         << u.followers.size()
         << "\n";
    cout << "Following: "
         << u.followings.size()
         << "\n";
}
void usersystem::showRecommendations(
    int userId
)
{
    recommender.setGraph(
        friends.getGraph()
    );
    auto suggestions =
        recommender.recommend(userId);
    cout << "\n===== FRIEND RECOMMENDATIONS =====\n";
    if (suggestions.empty())
    {
        cout << "No recommendations\n";
        return;
    }
    for (int id : suggestions)
    {
        if (users.find(id) == users.end())
            continue;
        cout
            << "ID: "
            << id
            << " | Username: "
            << users[id].username
            << "\n";
    }
}
user* usersystem::getUser(
    int id
)
{
    auto it = users.find(id);
    if (it == users.end())
        return nullptr;
    return &it->second;
}
unordered_map<int, unordered_set<int>> usersystem::getUsersGraph() const
{
    unordered_map<int, unordered_set<int>> graph;
    for (const auto& [id, u] : users)
        graph[id] = u.followings;
    return graph;
}

const unordered_map<int, user>&
usersystem::getUsers() const
{
    return users;
}