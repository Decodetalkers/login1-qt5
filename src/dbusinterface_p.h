/*
 * Copyright (C) 2021 ~ 2023 Deepin Technology Co., Ltd.
 *
 * Author:     caixiangrong <caixiangrong@uniontech.com>
 *
 * Maintainer: caixiangrong <caixiangrong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "dbusinterface.h"

class QDBusPendingCallWatcher;

class DBusInterfacePrivate : public QObject
{
    Q_OBJECT

public:
    explicit DBusInterfacePrivate(DBusInterface *interface, QObject *parent);
    QVariant updateProp(const char *propname, const QVariant &value);
    void initDBusConnection();
    void setServiceValid(bool valid);

private Q_SLOTS:
    void onPropertiesChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties);
    void onAsyncPropertyFinished(QDBusPendingCallWatcher *w);
    void onDBusNameHasOwner(bool valid);
    void onDBusNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOWner);

public:
    QObject *m_parent;
    QString m_suffix;
    QVariantMap m_propertyMap;
    bool m_serviceValid;

    DBusInterface *q_ptr;
    Q_DECLARE_PUBLIC(DBusInterface)
};

