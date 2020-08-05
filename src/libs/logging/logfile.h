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

#ifndef LOGFILE_H
#define LOGFILE_H

#include <QFile>
#include <QDir>

class LogFile : public QFile
{
    Q_OBJECT
public:
    LogFile(QObject *parent = nullptr);

    ~LogFile() override;

    QString createFileName();
    void close() override;

    static const char *crlf() { return "\r\n"; }

    /// Returns the name of the file, excluding the path.
    QString fileShortName() const;

protected:
    virtual QString suffix() const = 0;
    bool open(OpenMode flags = WriteOnly) override;
};

#endif // LOGFILE_H
