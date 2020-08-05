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
import "skyhub-version.js" as Version

Project {
    name: "skyhub-sdk"
    property string fullVersion: Version.major + "." + Version.minor + "." + Version.release
    property path libDir: "lib"

    property path sourcePath: path + "/src"
    property path headersBasePath: sourcePath + "/libs"
    property path payloadPath: sourcePath + "/plugins/payloads/payload-example"

    minimumQbsVersion: "1.6.0"
    qbs.installPrefix: ""

    references: payloadPath

    Product {
        name: "connections"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [
                headersBasePath + "/connections",
            ]
            cpp.libraryPaths: libDir
            cpp.staticLibraries: name + "-" + qbs.architecture + "-" + fullVersion
        }
    }

    Product {
        name: "logging"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [
                headersBasePath + "/logging",
                headersBasePath + "/logging/logs",
            ]
            cpp.libraryPaths: libDir
            cpp.staticLibraries: name + "-" + qbs.architecture + "-" + fullVersion
        }
    }

    Product {
        name: "base"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [
                headersBasePath + "/base",
                headersBasePath + "/base/messages",
            ]
            cpp.libraryPaths: libDir
            cpp.staticLibraries: name + "-" + qbs.architecture + "-" + fullVersion
        }
    }
}
