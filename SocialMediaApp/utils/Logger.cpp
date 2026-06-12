#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/utils/Logger.h"
#include <iostream>
using namespace std;
void logger::info(
    const string& msg
)
{
    cout << "[INFO] "
         << msg
         << "\n";
}
void logger::warning(
    const string& msg
)
{
    cout << "[WARNING] "
         << msg
         << "\n";
}
void logger::error(
    const string& msg
)
{
    cout << "[ERROR] "
         << msg
         << "\n";
}