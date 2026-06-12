cmake_minimum_required(VERSION 3.10)
project(SocialMediaApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    app/AppController.cpp
    app/Menu.cpp
    core/UserSystem.cpp
    core/PostSystem.cpp
    core/CommentSystem.cpp
    social/FriendSystem.cpp
    social/RecommendationSystem.cpp
    search/HashtagEngine.cpp
    search/SearchEngine.cpp
    feed/feedsystem.cpp
    analytics/AnalyticsSystem.cpp
    parser/ContentParser.cpp
    parser/ProfanityFilter.cpp
    db/Database.cpp
    db/storage.cpp
    realtime/NotificationSystem.cpp
    utils/Logger.cpp
)

add_executable(SocialMediaApp ${SOURCES})
target_include_directories(SocialMediaApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
