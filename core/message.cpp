// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "message.h"

Message::Message() = default;

bool Message::operator==(const Message &other) const
{
    return m_numerus == other.m_numerus &&
            m_type == other.m_type &&
            m_locations == other.m_locations &&
            m_source == other.m_source &&
            m_translations == other.m_translations &&
            m_translatorComment == other.m_translatorComment;
}

bool Message::hasTranslatorComment() const
{
    return !m_translatorComment.isEmpty();
}

bool Message::isValid() const
{
    return !m_source.isEmpty();
}

int Message::getNumberOfTranslated() const
{
    int translated = 0;
    for (const QString & translation : m_translations)
    {
        if (!translation.isEmpty())
            ++translated;
    }
    return translated;
}

void Message::merge(const Message &other)
{
    if (other.getType() == Message::Obsolete)
        return;

    if (getType() == Message::Obsolete)
    {
        operator=(other);
        return;
    }

    for (const Location &location : other.locations())
    {
        Locations::iterator it = std::find(m_locations.begin(), m_locations.end(), location);
        if (it == m_locations.end())
            m_locations.push_back(location);
    }
    std::sort(m_locations.begin(), m_locations.end());

    int totalTranslations = qMax(m_translations.size(), other.m_translations.size());
    for (int i = 0; i < totalTranslations; ++i)
    {
        if (m_translations[i].isEmpty())
            m_translations[i] = other.m_translations[i];
    }

    if (!hasTranslatorComment())
        m_translatorComment = other.getTranslatorComment();

    if (getType() == Message::Unfinished && other.getType() == Message::Finished)
        setType(Message::Finished);
}
