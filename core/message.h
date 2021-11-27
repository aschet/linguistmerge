// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MESSAGE_H
#define MESSAGE_H

#include "location.h"
#include <QtCore/QString>
#include <QtCore/QStringList>

class Message
{
public:
    enum Type
    {
        Finished,
        Unfinished,
        Obsolete
    };

    Message();

    bool operator==(const Message &other) const;

    inline void setNumerus(bool numerus)
    {
        m_numerus = numerus;
    }

    inline Locations& locations()
    {
        return m_locations;
    }

    inline const Locations& locations() const
    {
        return m_locations;
    }

    inline Type getType() const
    {
        return m_type;
    }

    inline void setType(Type type)
    {
        m_type = type;
    }

    inline bool isNumerus() const
    {
        return m_numerus;
    }

    inline QString getSource() const
    {
        return m_source;
    }

    inline void setSource(const QString &source)
    {
        m_source = source;
    }

    inline const QStringList& translations() const
    {
        return m_translations;
    }

    inline QStringList& translations()
    {
        return m_translations;
    }

    inline QString getTranslatorComment() const
    {
        return m_translatorComment;
    }

    inline void setTranslatorComment(const QString &translatorComment)
    {
        m_translatorComment = translatorComment;
    }

    bool hasTranslatorComment() const;

    bool isValid() const;

    int getNumberOfTranslated() const;

    void merge(const Message &other);

private:
    bool m_numerus = false;

    Type m_type = Unfinished;

    Locations m_locations;

    QString m_source;

    QStringList m_translations;

    QString m_translatorComment;
};

#endif
