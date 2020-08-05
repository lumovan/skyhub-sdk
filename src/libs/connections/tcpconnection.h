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

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "iconnection.h"

class QTcpSocket;

class TcpConnection : public IConnection
{
    Q_OBJECT
public:
    explicit TcpConnection(QObject *parent = nullptr);
    ~TcpConnection() override;

    bool open(const QString &name, const QVariant &parameter = QVariant()) override;
    void close() override;
    void reconnect() override;
    bool isOpened() const override;
    void setParameter(const QString &key, const QVariant &value) override;
    bool sendData(const char *data, qint64 length) override;
    ConnectionType type() const override { return ConnectionType::Tcp; }
    QString id() const override { return "TCP"; }

protected slots:
    void readData() override;

private:
    QTcpSocket *m_socket = nullptr;

    QString m_hostName = "localhost";
    quint16 m_port = 23;
    int m_connectTimeout = 1000;
    int m_disconnectTimeout = 1000;
    int m_writeTimeout = 500;
};

#endif // TCPCONNECTION_H
