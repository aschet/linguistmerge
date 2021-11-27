// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "context.h"

Context::Context() = default;

void Context::addMessage(const Message &message)
{
    m_messages.insert(message.getSource(), message);
}

const Message *Context::findMessage(const QString &source) const
{
    Messages::const_iterator it = m_messages.find(source);
    if (it != m_messages.end())
        return &it.value();
    else
        return nullptr;
}

bool Context::isValid() const
{
    return !m_name.isEmpty() && !m_messages.isEmpty();
}

void Context::merge(const Context &other)
{
    for (const Message& message : other.messages())
    {
        Messages::iterator it = m_messages.find(message.getSource());
        if (it != m_messages.end())
        {
            it->merge(message);
        }
        else
        {
            addMessage(message);
        }
    }
}
