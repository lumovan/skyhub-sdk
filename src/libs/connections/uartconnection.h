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

#ifndef UARTCONNECTION_H
#define UARTCONNECTION_H

#include <iconnection.h>

class QSerialPort;
class UartConnection : public IConnection
{
    Q_OBJECT
public:
    explicit UartConnection(QObject *parent = nullptr);
    ~UartConnection() override;

    bool open(const QString &name, const QVariant &parameter = QVariant()) override;
    void close() override;
    void reconnect() override;
    bool isOpened() const override;
    void setParameter(const QString &key, const QVariant &value) override;
    bool sendData(const char *data, qint64 length) override;
    ConnectionType type() const override { return ConnectionType::Uart; }
    QString id() const override { return "UART"; }

protected slots:
    void readData() override;

private:
    QSerialPort *m_port;
    QString m_portName;
    int m_baudRate;
};

#endif // UARTCONNECTION_H
