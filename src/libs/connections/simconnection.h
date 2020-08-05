/****************************************************************************
**
** Copyright (C) 2020, Smart Projects Holdings Ltd
** Contact: https://industrial.ugcs.com/contact
**
** This file is part of SkyHub SDK.
**
** BSD 3-Clause License Usage
**
** This file may be used under the terms of the BSD 3-Clause License
** as published by the Open Source Initiative and appearing in the file
** LICENSE included in the packaging of this file. Please review the
** following information to ensure the BSD 3-Clause License requirements
** will be met: https://opensource.org/licenses/BSD-3-Clause.
**
****************************************************************************/

#ifndef SIMCONNECTION_H
#define SIMCONNECTION_H

#include "iconnection.h"

class SimConnection : public IConnection
{
    Q_OBJECT
public:
    SimConnection(QObject *parent = nullptr) : IConnection(parent)
    {
    }
    ~SimConnection() override = default;

    bool open(const QString &name, const QVariant &parameter = QVariant()) override
    {
        Q_UNUSED(name)
        Q_UNUSED(parameter)
        return true;
    }
    void close() override {}
    void reconnect() override {}
    bool isOpened() const override { return true; }
    void setParameter(const QString &key, const QVariant &value) override
    {
        Q_UNUSED(key)
        Q_UNUSED(value)
    }
    void readData() override {}
    bool sendData(const char *data, qint64 length) override
    {
        Q_UNUSED(data)
        Q_UNUSED(length)
        return true;
    }
    ConnectionType type() const override { return ConnectionType::Simulator; }
};

#endif // SIMCONNECTION_H
