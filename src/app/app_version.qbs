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
import qbs.File
import qbs.FileInfo
import qbs.TextFile

Product {
    name: "app_version"
    type: "hpp"

    Group {
        name: "Input"
        files: [
            "app_version.h.in"
        ]
        fileTags: "hpp_in"
    }

    Rule {
        id: app_version
        alwaysRun: true
        inputs: ["hpp_in"]
        outputFileTags: ["hpp", ".version"]
        outputArtifacts: [
            {
                filePath: "app_version.h",
                fileTags: ["hpp"]
            },
            {
                filePath: ".version",
                fileTags: [".version"]
            }
        ]

        prepare: {
            var cmds = [];

            var hppCmd = new JavaScriptCommand();
            hppCmd.description = "generating app_version.h";
            hppCmd.highlight = "codegen";
            hppCmd.onWindows = (product.moduleProperty("qbs", "targetOS").contains("windows"));
            hppCmd.outputFilePath = outputs["hpp"][0].filePath;
            hppCmd.sourceCode = function() {
                var file;

                file = new TextFile(input.filePath);
                var content = file.readAll();
                file.close();
                // replace quoted quotes
                content = content.replace(/\\\"/g, '"');
                // replace Windows line endings
                if (onWindows) {
                    content = content.replace(/\r\n/g, "\n");
                }
                // replace the magic qmake incantations
                content = content.replace(/(\n#define APP_VERSION_MAJOR) .+\n/, "$1 " + project.versionMajor + "\n");
                content = content.replace(/(\n#define APP_VERSION_MINOR) .+\n/, "$1 " + project.versionMinor + "\n");
                content = content.replace(/(\n#define APP_VERSION_RELEASE) .+\n/, "$1 " + project.versionRelease + "\n");

                content = content.replace(/(\n#define APP_NAME) .+\n/, "$1 \"" + project.appName + "\"\n");

                var version = project.versionMajor + "." + project.versionMinor + "." + project.versionRelease;
                content = content.replace(/(\n#define APP_VERSION) .+\n/, "$1 \"" + version + "\"\n");

                // Bump build
                var buildFile = FileInfo.path(outputFilePath) + "/.build";
                var build = project.versionBuild;
                if (File.exists(buildFile)) {
                    file = TextFile(buildFile, TextFile.ReadOnly);
                    var versionString = file.readLine();
                    var buildString = file.readLine();
                    file.close();
                    if (versionString != version) {
                        build = 0;
                    } else {
                        build = parseInt(buildString) + 1;
                    }
                }
                file = TextFile(buildFile, TextFile.WriteOnly);
                file.writeLine(version);
                file.writeLine(build);
                file.close();

                content = content.replace(/(\n#define APP_VERSION_BUILD) .+\n/, "$1 " + build + "\n");

                var versionLong = version + "." + build;
                content = content.replace(/(\n#define APP_VERSION_LONG) .+\n/, "$1 \"" + versionLong + "\"\n");

                var now = new Date();
                content = content.replace(/(\n#define APP_YEAR) .+\n/, "$1 " + now.getFullYear() + "\n");
                content = content.replace(/(\n#define APP_DATE) .+\n/, "$1 \"" + now.toLocaleDateString("ru-RU") + "\"\n");

                file = new TextFile(outputFilePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }

            var versionCmd = new JavaScriptCommand();
            versionCmd.description = "generating .version";
            versionCmd.highlight = "codegen";
            versionCmd.outputFilePath = outputs[".version"][0].filePath;
            versionCmd.sourceCode = function() {
                var file = TextFile(outputFilePath, TextFile.WriteOnly);
                file.writeLine(project.versionMajor + "." + project.versionMinor + "." + project.versionRelease);
                file.close();
            }

            cmds.push(hppCmd);
            cmds.push(versionCmd);

            return cmds;
        }
    }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: product.buildDirectory
    }

    Group {
        fileTagsFilter: [".version"]
        qbs.install: true
        qbs.installPrefix: ""
    }
}
