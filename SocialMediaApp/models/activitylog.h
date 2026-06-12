#pragma once
#include <string>
using namespace std;
struct activitylog
{
    int userid;
    string action;
    string createdat;
    activitylog() = default;
    activitylog(
        int userid,
        const string& action,
        const string& createdat
    )
        : userid(userid),
          action(action),
          createdat(createdat)
    {
    }
};