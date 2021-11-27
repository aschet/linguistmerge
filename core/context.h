// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CONTEXT_H
#define CONTEXT_H

#include "message.h"
#include <QtCore/QMap>

typedef QMap<QString, Message> Messages;

class Context
{
public:
    Context();

    inline QString getName() const
    {
        return m_name;
    }

    void setName(const QString &name)
    {
        m_name = name;
    }

    inline const Messages& messages() const
    {
        return m_messages;
    }

    void addMessage(const Message &message);

    const Message *findMessage(const QString &source) const;

    bool isValid() const;

    void merge(const Context &other);

private:
    QString m_name;

    Messages m_messages;
};

#endif
