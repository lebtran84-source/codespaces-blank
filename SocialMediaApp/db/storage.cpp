#include "storage.h"
#include <fstream>
void storage::write(const string& file, const string& line)
{
    ofstream f(file, ios::app);
    f << line << "\n";
}
vector<string> storage::read(const string& file)
{
    vector<string> res;
    ifstream f(file);
    string line;
    while (getline(f, line))
        if (!line.empty())
            res.push_back(line);

    return res;
}
void storage::clear(const string& file)
{
    ofstream f(file, ios::trunc);
}