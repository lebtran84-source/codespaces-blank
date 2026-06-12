#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
using namespace std;
class utils
{
public:

    // ================= SPLIT INT =================
    static vector<int> split_int(const string& s)
    {
        vector<int> res;
        stringstream ss(s);
        string item;
        while (getline(ss, item, ','))
        {
            if (!item.empty())
                res.push_back(stoi(item));
        }
        return res;
    }

    // ================= SPLIT STRING =================
    static vector<string> split_str(const string& s)
    {
        vector<string> res;
        stringstream ss(s);
        string item;
        while (getline(ss, item, ','))
        {
            if (!item.empty())
                res.push_back(item);
        }
        return res;
    }

    // ================= JOIN INT =================
    static string join_int(const vector<int>& v)
    {
        string res;
        for (int i = 0; i < v.size(); i++)
        {
            res += to_string(v[i]);
            if (i != v.size() - 1)
                res += ",";
        }
        return res;
    }

    // ================= JOIN STRING =================
    static string join_str(const unordered_set<string>& v)
    {
        string res;
        int i = 0;
        for (auto& x : v)
        {
            res += x;
            if (i != v.size() - 1)
                res += ",";
            i++;
        }
        return res;
    }
};