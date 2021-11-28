// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QtWidgets/QApplication>

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent, f)
    ,m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);
    m_ui->m_labelVersion->setText(tr("Version %1").arg(qApp->applicationVersion()));
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
