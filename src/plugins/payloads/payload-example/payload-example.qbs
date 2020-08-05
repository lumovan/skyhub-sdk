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

import qbs

DynamicLibrary {
    name: "payload-example"

    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["core"] }
    Depends { name: "base" }
    Depends { name: "connections" }
    Depends { name: "logging" }

    cpp.cxxLanguageVersion: "c++11"
    cpp.cxxFlags: ["-Werror"]

    files: [
        "*.cpp",
        "*.h"
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: "plugins/payloads"
        qbs.installPrefix: "/usr/local/lib"
    }
}
