#pragma once

#include "namespace.h"
#include <qobject.h>
#include <qvariant.h>

LOGIN1_BEGIN_NAMESPACE
struct ScheduledShutdownValue
{
    QString type;
    quint64 usec;
};

struct SessionProperty
{
    QString name;
    QVariant var;
};

struct Inhibitor
{
    QString what;
    QString who;
    QString why;
    QString mode;
    uint    uid;
    uint    pid;
};

struct Seat
{
    QString seat_id;
    QString path;
};

struct Session
{
    QString session_id;
    uint user_id;
    QString user_name;
    QString seat_id;
    QString path;
};

struct User
{
    uint user_id;
    QString user_name;
    QString path;
};

typedef Seat SeatPath;

struct SessionPath
{
    QString session_id;
    QString path;
};

struct UserPath
{
    uint user_id;
    QString path;
};

LOGIN1_END_NAMESPACE
