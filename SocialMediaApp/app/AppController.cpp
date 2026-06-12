#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/app/AppController.h"
#include <iostream>
#include <limits>
#include "/workspaces/codespaces-blank/socialmedia/SocialMediaApp/parser/ProfanityFilter.h"
using namespace std;
void appcontroller::init()
{
    // load profanity list early so create/edit posts and comments warn correctly
    profanityfilter::loadBadWords("/workspaces/codespaces-blank/socialmedia/SocialMediaApp/data/banned_words.txt");

    userSys.load();
    postSys.load();
    commentSys.load();

    friendSys.load(userSys.getUsersGraph());

    cout << "System initialized!\n";
}
void appcontroller::runAuth()
{
    int choice;

    while (true)
    {
        displayAuthMenu();
        cin >> choice;

        if (choice == AUTH_REGISTER)
        {
            string u, p;
            cout << "Username: ";
            cin >> u;
            cout << "Password: ";
            cin >> p;

            if (userSys.registerUser(u, p))
                cout << "Register success\n";
            else
                cout << "Username exists\n";
        }

        else if (choice == AUTH_LOGIN)
        {
            string u, p;
            cout << "Username: ";
            cin >> u;
            cout << "Password: ";
            cin >> p;

            int id = userSys.login(u, p);

            if (id != -1)
            {
                currentUserId = id;
                cout << "Login success. User ID: " << id << "\n";
                return;
            }

            cout << "Login failed\n";
        }

        else if (choice == AUTH_EXIT)
        {
            exit(0);
        }
    }
}
void appcontroller::run()
{
    init();
    runAuth();

    int choice;

    while (true)
    {
        displayMainMenu();
        cin >> choice;

        switch (choice)
        {
            case MAIN_USER_MANAGEMENT:
                handleUserMenu();
                break;

            case MAIN_POST_MANAGEMENT:
                handlePostMenu();
                break;

            case MAIN_SEARCH_FEATURE:
                handleSearchMenu();
                break;

            case MAIN_NOTIFICATIONS:
                handleNotificationMenu();
                break;

            case MAIN_VIEW_FEED:
                showFeed();
                break;

            case MAIN_ANALYTICS:
                analyticssystem::showDashboard(userSys, postSys, commentSys);
                break;

            case MAIN_LOGOUT:
                cout << "Logged out\n";
                currentUserId = -1;
                runAuth();
                break;

            case MAIN_EXIT:
                cout << "Bye!\n";
                return;

            default:
                cout << "Invalid choice\n";
        }
    }
}
void appcontroller::handleUserMenu()
{
    int choice;

    while (true)
    {
        displayUserMenu();
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number.\n";
            continue;
        }

        if (choice == USER_VIEW_PROFILE)
        {
            int id;
            cout << "User ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\n";
                continue;
            }

            userSys.viewProfile(id);
        }

        else if (choice == USER_SEARCH_USER)
        {
            string key;
            cout << "Keyword: ";
            cin >> key;

            userSys.searchUser(key);
        }

        else if (choice == USER_FOLLOW)
        {
            if (currentUserId == -1)
            {
                cout << "Please log in before following someone.\n";
                continue;
            }

            int id;
            cout << "Follow user ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\n";
                continue;
            }

            if (id == currentUserId)
            {
                cout << "You cannot follow yourself.\n";
                continue;
            }

            userSys.follow(currentUserId, id);
            // notify the target user
            {
                auto* follower = userSys.getUser(currentUserId);
                string followerName = follower ? follower->username : to_string(currentUserId);
                string msg = followerName + " started following you.";
                notiSys.notify(id, currentUserId, msg);
            }
        }

        else if (choice == USER_UNFOLLOW)
        {
            if (currentUserId == -1)
            {
                cout << "Please log in before unfollowing someone.\n";
                continue;
            }

            int id;
            cout << "Unfollow user ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\n";
                continue;
            }

            if (id == currentUserId)
            {
                cout << "You cannot unfollow yourself.\n";
                continue;
            }

            userSys.unfollow(currentUserId, id);
        }

        else if (choice == USER_GET_RECOMMENDATIONS)
        {
            if (currentUserId == -1)
            {
                cout << "Please log in to view recommendations.\n";
                continue;
            }
            userSys.showRecommendations(currentUserId);
        }

        else if (choice == USER_BACK)
        {
            return;
        }

        else
        {
            cout << "Invalid choice\n";
        }
    }
}
void appcontroller::handlePostMenu()
{
    int choice;

    while (true)
    {
        displayPostMenu();
        cin >> choice;

        if (choice == POST_CREATE)
        {
            if (currentUserId == -1)
            {
                cout << "Please login first!\n";
                return;
            }

            string content;
            cout << "Content: ";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, content);

            postSys.createPost(currentUserId, content);
        }

        else if (choice == POST_VIEW)
        {
            int id;
            cout << "Post ID: ";
            cin >> id;

            postSys.viewPost(id);
            // show comments for this post
            commentSys.viewComments(id);
        }

        else if (choice == POST_MY_POSTS)
        {
            postSys.viewMyPosts(currentUserId);
        }

        else if (choice == POST_EDIT)
        {
            if (currentUserId == -1)
            {
                cout << "Please login first!\n";
                return;
            }

            int id;
            cout << "Post ID: ";
            cin >> id;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string content;
            cout << "New content: ";
            getline(cin, content);

            postSys.editPost(currentUserId, id, content);
        }

        else if (choice == POST_DELETE)
        {
            int id;
            cout << "Post ID: ";
            cin >> id;

            postSys.deletePost(currentUserId, id);
        }

        else if (choice == POST_LIKE)
        {
            int id;
            cout << "Post ID: ";
            cin >> id;

            auto& postsRef = postSys.getPosts();
            if (postsRef.find(id) == postsRef.end())
            {
                cout << "Post not found\n";
                continue;
            }
            bool already = postsRef.at(id).likes.count(currentUserId);
            postSys.toggleLike(currentUserId, id);
            if (!already)
            {
                int author = postsRef.at(id).authorid;
                auto* liker = userSys.getUser(currentUserId);
                string name = liker ? liker->username : to_string(currentUserId);
                string msg = name + " liked your post.";
                notiSys.notify(author, currentUserId, msg);
            }
        }

        else if (choice == POST_ADD_COMMENT)
        {
            if (currentUserId == -1)
            {
                cout << "Please login first!\n";
                return;
            }

            int id;
            string c;

            cout << "Post ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Post ID\n";
                continue;
            }

            if (postSys.getPosts().find(id) == postSys.getPosts().end())
            {
                cout << "Post not found\n";
                continue;
            }

            cout << "Existing comments for post " << id << ":\n";
            commentSys.viewComments(id);
            cout << "Reply to comment ID (0 for new comment): ";
            int parent;
            if (!(cin >> parent))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid comment ID\n";
                continue;
            }
            if (parent != 0)
            {
                auto commentIt = commentSys.getComments().find(parent);
                if (commentIt == commentSys.getComments().end() || commentIt->second.postid != id)
                {
                    cout << "Comment ID not found for this post\n";
                    continue;
                }
            }

            cout << "Comment: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, c);

            int commentId = commentSys.addComment(currentUserId, id, c, parent == 0 ? -1 : parent);
            postSys.addCommentToPost(id, commentId);
            // notify post author
            {
                auto& postsRef = postSys.getPosts();
                if (postsRef.find(id) != postsRef.end())
                {
                    int author = postsRef.at(id).authorid;
                    if (author != currentUserId)
                    {
                        auto* commenter = userSys.getUser(currentUserId);
                        string name = commenter ? commenter->username : to_string(currentUserId);
                        string msg = name + " commented on your post.";
                        notiSys.notify(author, currentUserId, msg);
                    }
                }
            }
        }

        else if (choice == POST_BACK)
        {
            return;
        }
    }
}
void appcontroller::handleSearchMenu()
{
    int choice;

    while (true)
    {
        displaySearchMenu();
        cin >> choice;

        if (choice == SEARCH_POST_BY_KEYWORD)
        {
            string k;
            cout << "Keyword: ";
            cin >> k;

            postSys.searchPost(k);
        }

        else if (choice == SEARCH_POST_BY_HASHTAG)
        {
            string t;
            cout << "Hashtag: ";
            cin >> t;

            postSys.searchByHashtag(t);
        }

        else if (choice == SEARCH_USER_BY_NAME)
        {
            string u;
            cout << "Username: ";
            cin >> u;
            userSys.searchUser(u);
            cout << "\nEnter user ID to view profile (0 to skip): ";
            int userId;
            cin >> userId;

            if (userId != 0)
            {
                cout << "\n===== USER PROFILE =====\n";
                userSys.viewProfile(userId);
                cout << "\n===== USER'S POSTS =====\n";
                postSys.viewPostsByUser(userId);
            }
        }

        else if (choice == SEARCH_BACK)
        {
            return;
        }
    }
}

void appcontroller::handleNotificationMenu()
{
    int choice;

    while (true)
    {
        displayNotificationMenu();
        cin >> choice;

        if (choice == NOTIFICATION_VIEW)
        {
            notiSys.showNotifications(currentUserId);
        }

        else if (choice == NOTIFICATION_MARK_AS_READ)
        {
            int id;
            cout << "Notification ID: ";
            cin >> id;

            notiSys.markAsRead(currentUserId, id);
        }

        else if (choice == NOTIFICATION_BACK)
        {
            return;
        }
    }
}
void appcontroller::showFeed()
{
    // Print feed with author username, likes and comment count
    auto& posts = postSys.getPosts();
    if (posts.empty())
    {
        cout << "No posts\n";
        return;
    }

    for (auto& [id, p] : posts)
    {
        auto* author = userSys.getUser(p.authorid);
        string authorName = author ? author->username : to_string(p.authorid);
        cout << "Post ID: " << p.id << " | " << authorName
             << " | Likes: " << p.likes.size()
             << " | Comments: " << p.commentids.size() << "\n";
        cout << "  " << p.content << "\n";
    }

    // interactive actions
    while (true)
    {
        cout << "\nEnter Post ID to interact (0 to return): ";
        int pid;
        if (!(cin >> pid))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }
        if (pid == 0) return;
        if (posts.find(pid) == posts.end())
        {
            cout << "Post not found\n";
            continue;
        }

        auto& p = posts.at(pid);
        cout << "\n1) View Author Profile\n2) Like/Unlike\n3) Add Comment\n4) View Comments\n0) Back\nChoice: ";
        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice\n";
            continue;
        }

        if (choice == 1)
        {
            auto* au = userSys.getUser(p.authorid);
            if (au)
            {
                userSys.viewProfile(au->id);
                cout << "\nAuthor's posts:\n";
                postSys.viewPostsByUser(au->id);
            }
            else
                cout << "Author not found\n";
        }
        else if (choice == 2)
        {
            if (currentUserId == -1)
            {
                cout << "Please login to like/unlike posts\n";
                continue;
            }
            // determine if this is a new like
            bool alreadyLiked = posts.at(pid).likes.count(currentUserId);
            postSys.toggleLike(currentUserId, pid);
            cout << "Toggled like for post " << pid << "\n";
            if (!alreadyLiked)
            {
                int author = posts.at(pid).authorid;
                auto* liker = userSys.getUser(currentUserId);
                string name = liker ? liker->username : to_string(currentUserId);
                string msg = name + " liked your post.";
                notiSys.notify(author, currentUserId, msg);
            }
        }
        else if (choice == 3)
        {
            if (currentUserId == -1)
            {
                cout << "Please login to comment\n";
                continue;
            }
            cout << "Reply to comment ID (0 for new comment): ";
            int parent;
            if (!(cin >> parent))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string c;
            cout << "Comment: ";
            getline(cin, c);
            int commentId = commentSys.addComment(currentUserId, pid, c, parent == 0 ? -1 : parent);
            postSys.addCommentToPost(pid, commentId);
            cout << "Comment added\n";
            // show updated counts for the post immediately
            {
                auto* author = userSys.getUser(p.authorid);
                string authorName = author ? author->username : to_string(p.authorid);
                cout << "Updated -> Post ID: " << p.id << " | " << authorName
                     << " | Likes: " << p.likes.size()
                     << " | Comments: " << p.commentids.size() << "\n";
                cout << "  " << p.content << "\n";
            }
            // notify post author
            {
                int author = posts.at(pid).authorid;
                if (author != currentUserId)
                {
                    auto* commenter = userSys.getUser(currentUserId);
                    string name = commenter ? commenter->username : to_string(currentUserId);
                    string msg = name + " commented on your post.";
                    notiSys.notify(author, currentUserId, msg);
                }
            }
        }
        else if (choice == 4)
        {
            commentSys.viewComments(pid);
        }
        else if (choice == 0)
        {
            // back to feed listing
            return;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }
}


