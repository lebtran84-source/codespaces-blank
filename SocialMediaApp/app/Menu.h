#pragma once

#include <iostream>
#include <string>
using namespace std;

// ================= MAIN MENU =================
enum MainMenuOption {
    MAIN_USER_MANAGEMENT = 1,
    MAIN_POST_MANAGEMENT = 2,
    MAIN_SEARCH_FEATURE = 3,
    MAIN_NOTIFICATIONS = 4,
    MAIN_VIEW_FEED = 5,
    MAIN_ANALYTICS = 6,
    MAIN_LOGOUT = 7,
    MAIN_EXIT = 0
};

// ================= USER MENU =================
enum UserMenuOption {
    USER_VIEW_PROFILE = 1,
    USER_SEARCH_USER = 2,
    USER_FOLLOW = 3,
    USER_UNFOLLOW = 4,
    USER_GET_RECOMMENDATIONS = 5,
    USER_BACK = 0
};

// ================= POST MENU =================
enum PostMenuOption {
    POST_CREATE = 1,
    POST_VIEW = 2,
    POST_MY_POSTS = 3,
    POST_EDIT = 4,
    POST_DELETE = 5,
    POST_LIKE = 6,
    POST_ADD_COMMENT = 7,
    POST_BACK = 0
};

// ================= SEARCH MENU =================
enum SearchMenuOption {
    SEARCH_POST_BY_KEYWORD = 1,
    SEARCH_POST_BY_HASHTAG = 2,
    SEARCH_USER_BY_NAME = 3,
    SEARCH_BACK = 0
};

// ================= NOTIFICATION MENU =================
enum NotificationMenuOption {
    NOTIFICATION_VIEW = 1,
    NOTIFICATION_MARK_AS_READ = 2,
    NOTIFICATION_BACK = 0
};

// ================= AUTH MENU =================
enum AuthMenuOption {
    AUTH_REGISTER = 1,
    AUTH_LOGIN = 2,
    AUTH_EXIT = 0
};

// ================= DISPLAY FUNCTIONS =================
void displayAuthMenu();
void displayMainMenu();
void displayUserMenu();
void displayPostMenu();
void displaySearchMenu();
void displayNotificationMenu();
