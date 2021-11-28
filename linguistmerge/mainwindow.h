// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include <mergemodel.h>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    bool addFilenames(const QStringList &filenames);

    bool merge(const QString &fileName);

private:
    Q_SLOT void onAddClicked();

    Q_SLOT void onRemoveClicked();

    Q_SLOT void onClearClicked();

    Q_SLOT void onMergeClicked();

    Q_SLOT void onAboutClicked();

    Q_SLOT void onDataChange();

    Q_SLOT void onSelectionChange();

    QString getFileFilter() const;

    Ui::MainWindow *m_ui;

    MergeModel m_model;
};

#endif
