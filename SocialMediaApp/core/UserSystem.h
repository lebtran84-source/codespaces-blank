#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/models/User.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/db/Database.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/social/FriendSystem.h"
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/social/RecommendationSystem.h"
using namespace std;
class usersystem
{
private:
    unordered_map<int, user> users;
    unordered_map<string, int> usernameMap;
    int currentUserId = -1;
public:
    void load();
    bool registerUser(const string& username, const string& password);
    int login(const string& username, const string& password);
    void logout();
    void follow(int myId, int targetId);
    void unfollow(int myId, int targetId);
    void searchUser(const string& keyword);
    void viewProfile(int id);
    void showRecommendations(int userId);
    unordered_map<int, unordered_set<int>> getUsersGraph() const;
    user* getUser(int id);
    const unordered_map<int, user>& getUsers() const;
    friendSystem friends;
    recommendationSystem recommender;
};