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

#ifndef IBASE_H
#define IBASE_H

#include "logged.h"

#include <QObject>

/**
 * @brief The base interface class.
 */
class IBase : public QObject, public Logged {
public:
    IBase(QObject *parent = nullptr);

    IBase& operator=(const IBase&) = delete;
    virtual ~IBase() = default;

    void runSystemCommand(const QString &command);
};

#endif // IBASE_H
