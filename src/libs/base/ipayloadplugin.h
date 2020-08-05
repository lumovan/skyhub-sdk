
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

#ifndef IPAYLOADPLUGIN_H
#define IPAYLOADPLUGIN_H

#include "ibase.h"
#include "iconnection.h"
#include "protocol.h"

/**
 * @brief The interface of payload
 */
class IPayloadPlugin : public IBase
{
    Q_OBJECT
public:
    IPayloadPlugin(QObject *parent = nullptr);
    ~IPayloadPlugin() override;

    void requestStart();
    virtual void stop() = 0;

    virtual ConnectionType connectionType() const = 0;
    virtual PayloadId payloadId() const = 0;
    virtual QString name() const { return ""; }

signals:
    void dataReceived(MessageId messageId, PayloadId payloadId,
                      const QByteArray &data, const QVariant &param = QVariant());

public slots:
    virtual void start() = 0;

protected:
    int telemetryTimerId() const { return m_telemetryTimerId; }
    int telemetryPeriod() const { return m_telemetryPeriod; }
    void restartTelemetryTimer(int period);
    void setStartDelay(int startDelay);

private:
    void stopTimer();

private slots:
    void startTelemetryTimer();

private:
    int m_startDelay;
    int m_telemetryPeriod;
    int m_telemetryTimerId = -1;
};

Q_DECLARE_INTERFACE(IPayloadPlugin, "com.ugcs.skyhub.ipayloadplugin")

#endif // IPAYLOADPLUGIN_H
