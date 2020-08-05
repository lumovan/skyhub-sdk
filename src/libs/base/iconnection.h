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

#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <QVariant>
#include "ibase.h"

enum class ConnectionType : uint8_t
{
    Simulator,
    Tcp,
    Uart,
    Bluetooth,
    I2c
};

/**
 * @brief The payload-to-core interface
 */
class IConnection : public IBase
{
    Q_OBJECT
public:
    IConnection(QObject *parent = nullptr) : IBase(parent)
    {
    }
    /**
     * @brief Open connection
     * @param name Connection name:
     * it's name of host for TCP connection;
     * it's name of serial port for UART connection;
     * it's name of device for Bluetooth connection
     * @param Specified parameters of connection
     * @return
     */
    virtual bool open(const QString &name, const QVariant &parameter = QVariant()) = 0;
    virtual void close() = 0;
    virtual void reconnect() = 0;
    virtual bool isOpened() const = 0;
    virtual void setParameter(const QString &key, const QVariant &value) = 0;
    virtual bool sendData(const char *data, qint64 length) = 0;
    virtual ConnectionType type() const = 0;

    bool sendCommand(const QString &cmd) { return sendData(cmd.toLocal8Bit()); }
    bool sendData(const QByteArray &data) { return sendData(data.constData(), data.length()); }

signals:
    void dataReceived(const QByteArray &data);
    void connected();
    void disconnected();

protected:
    virtual ~IConnection() = default;

protected slots:
    virtual void readData() = 0;
};

#endif // ICONNECTION_H
