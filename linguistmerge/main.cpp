// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QtCore/QCommandLineParser>
#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef APP_VERSION
    app.setApplicationVersion(APP_VERSION);
#endif

    MainWindow mainWindow;

    {
        QCommandLineParser parser;
        QCommandLineOption outputOption(QStringList() << "o" << "output", "Merged Qt localization TS file", "file");
        parser.setApplicationDescription("Merge Utility for Qt Localization TS Files");
        parser.addHelpOption();
        parser.addOption(outputOption);
        parser.addPositionalArgument("files", "Source Qt localization TS files", "[files...]");
        parser.process(app);

        QStringList filenames = parser.positionalArguments();
        if (!filenames.empty())
        {
            mainWindow.addFilenames(filenames);
            if (parser.isSet(outputOption))
            {
                QString targetPath = parser.value(outputOption);
                if (!targetPath.isEmpty())
                {
                    if (!mainWindow.merge(targetPath))
                        return 1;
                    else
                        return 0;
                }
            }
        }
    }

    mainWindow.show();
    return app.exec();
}
