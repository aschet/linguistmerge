// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TSREADER_H
#define TSREADER_H

#include "context.h"
#include <functional>
#include <QtCore/QXmlStreamReader>
class TS;

class TSReader : public QXmlStreamReader
{
public:
    using QXmlStreamReader::QXmlStreamReader;

    static bool isTSFile(const QString &filename);

    static bool read(const QString &filename, TS *ts);

    void read(TS *ts);

private:
    bool elementStarts(const QString &elementName) const;

    bool elementEnds(const QString &elementName) const;

    QString attrAsString(const QXmlStreamAttributes &attrs, const QString &name) const;

    int attrAsInt(const QXmlStreamAttributes &attrs, const QString &name, int defaultValue) const;

    bool attrAsBool(const QXmlStreamAttributes &attrs, const QString &name, bool defaultValue) const;

    Message::Type attrAsType(const QXmlStreamAttributes &attrs, const QString &name) const;

    void readTS();

    void readContext();

    void readMessage();

    Context m_currentContext;

    TS *m_ts = nullptr;
};

#endif
