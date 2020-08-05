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

#ifndef POSITIONLOG_H
#define POSITIONLOG_H

#include "csvlog.h"

class PositionLog : public CsvLog
{
    Q_OBJECT
public:
    static PositionLog *instance();

    void write();

    void start();
    void stop();

    void close() override;

protected:
    QString suffix() const override { return "-position.csv"; }

private:
    PositionLog(QObject *parent = nullptr);

    void timerEvent(QTimerEvent *event) override;

private:
    static int m_counter;

    int m_timerId = -1;
    int m_periodMs = 0;
    bool m_rtkIsValid = false;
    bool m_gprConnected = false;
    bool m_echosounderConnected = false;
    bool m_daqEnabled = false;
};

#endif // POSITIONLOG_H
