#pragma once

#include <string>
#include <unordered_set>
using namespace std;

struct comment
{
    int id;            
    int postid;        
    int authorid;      
    string content;     
    unordered_set<int> likes;
    string createdat;      
    int parentid;
     comment() : parentid(-1) {}
    comment(
        int id,
        int postid,
        int authorid,
        const string& content,
        const string& createdat
        
    )
        : id(id),
          postid(postid),
          authorid(authorid),
          content(content),
          createdat(createdat)
    {
    }
};