#pragma once

#include <string>

using namespace std;

struct notification
{
    int id;
    int receiverid;
    int senderid;
    string message;
    bool isRead;
    string createdAt;
    notification()
        : isRead(false) {}

    notification(
        int id,
        int receiverid,
        int senderid,
        const string& message,
        const string& createdAt
    )
        : id(id),
          receiverid(receiverid),
          senderid(senderid),
          message(message),
          isRead(false),
          createdAt(createdAt)
    {}
};