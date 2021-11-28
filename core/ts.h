// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TS_H
#define TS_H

#include "context.h"
#include <QtCore/QMap>
#include <QtCore/QVector>

typedef QMap<QString, Context> Contexts;

class TS
{
public:
    TS();

    inline QString getFilename() const
    {
        return m_filename;
    }

    inline void setFilename(const QString &filename)
    {
        m_filename = filename;
    }

    inline QString getLanguage() const
    {
        return m_language;
    }

    inline void setLanguage(const QString &language)
    {
        m_language = language;
    }

    inline QString getSourceLanguage() const
    {
        return m_sourceLanguage;
    }

    inline void setSourceLanguage(const QString &sourceLanguage)
    {
        m_sourceLanguage = sourceLanguage;
    }

    inline const Contexts& contexts() const
    {
        return m_contexts;
    }

    bool hasLanguage() const;

    bool hasSourceLanguage() const;

    void addContext(const Context &context);

    const Context *findContext(const QString &name) const;

    void merge(const TS &other);

private:
    QString m_filename;

    QString m_language;

    QString m_sourceLanguage;

    Contexts m_contexts;
};

typedef QVector<TS> TSVector;

TS merge(const TSVector &data);

#endif
