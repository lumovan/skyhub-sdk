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

#ifndef LOGGED_H
#define LOGGED_H

#include <QDebug>

class Logged
{
public:
    Logged();

    QDebug trace(const QString &prefix = QString());
    QDebug debug() { return addPreamble(QMessageLogger().debug()) << "Dbg:"; }
    QDebug info() { return addPreamble(QMessageLogger().info()); }
    QDebug warning() { return addPreamble(QMessageLogger().warning()) << "WARN:"; }
    QDebug critical() { return addPreamble(QMessageLogger().critical()) << "CRIT:"; }

    void sendInfo(const QString &message);
    void sendError(const QString &message);
    void sendNotLoggedError(const QString &message);

protected:
    virtual QString id() const { return ""; }
    virtual QString prefix() const { return ""; }

private:
    QDebug addPreamble(const QDebug &logger);
};

#endif // LOGGED_H
