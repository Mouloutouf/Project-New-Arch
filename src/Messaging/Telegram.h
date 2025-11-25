//
// Created by maxdu on 11/11/2025.
//

#ifndef NEWARCH_TELEGRAM_H
#define NEWARCH_TELEGRAM_H

#include <cmath>
#include <iosfwd>
#include <ostream>

struct Telegram
{
    //the entity that sent this telegram
    std::string sender;

    //the entity that is to receive this telegram
    std::string receiver;

    //the message itself. These are all enumerated in the file
    //"MessageTypes.h"
    int messageType;

    //messages can be dispatched immediately or delayed for a specified amount
    //of time. If a delay is necessary this field is stamped with the time
    //the message should be dispatched.
    double dispatchTime;

    //any additional information that may accompany the message
    void* pExtraInfo;


    Telegram()
        : sender(nullptr), receiver(nullptr), messageType(-1), dispatchTime(-1), pExtraInfo(nullptr)
    {
    }


    Telegram(const double time, const std::string& sender, const std::string& receiver, const int message, void* pExtraInfo = nullptr)
        : sender(sender), receiver(receiver), messageType(message), dispatchTime(time), pExtraInfo(pExtraInfo)
    {
    }
};

constexpr double SMALLEST_DELAY = 0.25;

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
    return fabs(t1.dispatchTime - t2.dispatchTime) < SMALLEST_DELAY &&
        t1.sender == t2.sender &&
        t1.receiver == t2.receiver &&
        t1.messageType == t2.messageType;
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
    if (t1 == t2)
        return false;

    return t1.dispatchTime < t2.dispatchTime;
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
    os << "Time: " << t.dispatchTime << ", Sender: " << t.sender << ", Receiver: " << t.receiver << ", Message: " << t.messageType;
    return os;
}

#endif //NEWARCH_TELEGRAM_H