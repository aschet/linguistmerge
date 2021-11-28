// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TSWRITER_H
#define TSWRITER_H

#include <QXmlStreamWriter>

#include "message.h"
class TS;

class TSWriter : public QXmlStreamWriter
{
public:
    using QXmlStreamWriter::QXmlStreamWriter;

    static bool write(const QString &filename, const TS *ts);

    void write(const TS *ts);

private:
    QString typeAsAttr(Message::Type type) const;
};

#endif
