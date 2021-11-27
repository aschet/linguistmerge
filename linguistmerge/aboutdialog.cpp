// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent, f)
    ,m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
