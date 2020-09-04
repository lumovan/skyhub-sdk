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

#ifndef I2CCONNECTION_H
#define I2CCONNECTION_H

#include "iconnection.h"
#include "digiapix-i2c.h"

class QTimer;

class I2cConnection :  public IConnection
{
    Q_OBJECT
public:
    explicit I2cConnection(QObject *parent = nullptr);
    ~I2cConnection() override;

    bool open(const QString &name, const QVariant &parameter = QVariant()) override;
    void close() override;
    void reconnect() override;
    bool isOpened() const override { return m_device != nullptr; }
    void setParameter(const QString &key, const QVariant &value) override;
    bool sendData(const char *data, qint64 length) override;
    ConnectionType type() const override { return ConnectionType::I2c; }
    QString id() const override { return "I2C"; }

protected slots:
    void readData() override;
    void timerEvent(QTimerEvent *event) override;

private:
    i2c_t *m_device = nullptr;
    uint8_t m_address;
    int m_rxPeriod = 0;
    int m_retries = 0;
    int m_timeout = 0;
    uint16_t m_rxBufferSize = 0;
    int m_timerId = -1;
};

#endif // I2CCONNECTION_H
