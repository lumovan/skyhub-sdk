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

#ifndef PAYLOADEXAMPLE_H
#define PAYLOADEXAMPLE_H

#include <ipayloadplugin.h>
#include <app.h>
#include <app_version.h>

class PayloadExample : public IPayloadPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPayloadPlugin)
    Q_PLUGIN_METADATA(IID "com.ugcs.skyhub.ipayloadplugin")
public:
    PayloadExample();
    ~PayloadExample() override;

    void start() override;
    void stop() override;

    void timerEvent(QTimerEvent *event) override;

    ConnectionType connectionType() const override;
    PayloadId payloadId() const override;
    QString name() const override;
    QString version() const override { return C::AppVersionLong; }

    QString id() const override;

private:
    void calcRange();

private:
    int m_timerId = -1;
    PayloadId m_id = PayloadId::UserPayloadFirst;
    ScalarSensorData m_sensorData = { 0, ScalarSensorStatusId::SensorError };
};

#endif // PAYLOADEXAMPLE_H
