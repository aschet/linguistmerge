// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "waitcursorscope.h"

#include <limits>
#include <QtWidgets/QApplication>

WaitCursorScope::WaitCursorScope()
{
    qApp->setOverrideCursor(Qt::WaitCursor);
}

WaitCursorScope::~WaitCursorScope()
{
    qApp->restoreOverrideCursor();
}
