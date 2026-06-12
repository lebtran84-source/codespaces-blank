#pragma once
#include <string>
#include <vector>
# include <unordered_set>
using namespace std;
struct post{
    int id;
    int authorid;
    string content;
    unordered_set<string> hashtags;
    unordered_set<int> likes;
    vector<int> commentids;
    string createdat;
     post() = default;
    post(
        int id,
        int authorid,
        const string& content,
        const string& createdat
    )
        : id(id),
          authorid(authorid),
          content(content),
          createdat(createdat)
    {
    }
};