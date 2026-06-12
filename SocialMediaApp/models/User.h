#pragma once
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;
struct user{
    int id;
    string username;
    string password;
    unordered_set<int> followers;
    unordered_set<int> followings;
    user()= default;
    user(
        int id,
        const string& username,
        const string& password
    ): id(id), username(username), password(password){}
};

