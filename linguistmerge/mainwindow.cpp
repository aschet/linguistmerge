// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QFileDialog>
#include <tsreader.h>
#include <tswriter.h>
#include "aboutdialog.h"
#include "waitcursorscope.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->m_treeView->setModel(&m_model);
    m_ui->m_treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(m_ui->m_actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_ui->m_actionAdd, SIGNAL(triggered()), this, SLOT(onAddClicked()));
    connect(m_ui->m_actionRemove, SIGNAL(triggered()), this, SLOT(onRemoveClicked()));
    connect(m_ui->m_actionClear, SIGNAL(triggered()), this, SLOT(onClearClicked()));
    connect(m_ui->m_actionMerge, SIGNAL(triggered()), this, SLOT(onMergeClicked()));
    connect(m_ui->m_actionAbout, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    connect(&m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(onDataChange()));
    connect(&m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(onDataChange()));
    connect(&m_model, SIGNAL(modelReset()), this, SLOT(onDataChange()));
    connect(m_ui->m_treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onSelectionChange()));
    onDataChange();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

bool MainWindow::addFilenames(const QStringList &fileNames)
{
    return m_model.add(fileNames);
}

bool MainWindow::merge(const QString &fileName)
{
    WaitCursorScope wc;
    TS ts = m_model.merge();
    return TSWriter::write(fileName, &ts);
}

void MainWindow::onAddClicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Add Qt Localization TS Files"),
                                                          QString(), getFileFilter());
    if (!filenames.isEmpty())
    {
        m_model.add(filenames);
    }
}

void MainWindow::onRemoveClicked()
{
    m_model.remove(m_ui->m_treeView->selectionModel()->selectedRows());
}

void MainWindow::onClearClicked()
{
    m_model.clear();
}

void MainWindow::onMergeClicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Qt Localization TS File"),
                                                    QString(), getFileFilter());
    if (!filename.isEmpty())
    {
        if (!TSReader::isTSFile(filename))
            filename.append(".ts");
        merge(filename);
    }
}

void MainWindow::onAboutClicked()
{
    AboutDialog about(this);
    about.exec();
}

void MainWindow::onDataChange()
{
    bool hasData = m_model.hasData();
    m_ui->m_actionMerge->setEnabled(hasData);
    m_ui->m_actionClear->setEnabled(hasData);
    onSelectionChange();
}

void MainWindow::onSelectionChange()
{
    bool hasSelection = m_model.hasData() && m_ui->m_treeView->selectionModel()->hasSelection();
    m_ui->m_actionRemove->setEnabled(hasSelection);
}

QString MainWindow::getFileFilter() const
{
    return tr("Qt Localization TS Files (*.ts)");
}
