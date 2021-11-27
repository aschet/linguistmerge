// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ts.h"

TS::TS() = default;

bool TS::hasLanguage() const
{
    return !m_language.isEmpty();
}

bool TS::hasSourceLanguage() const
{
    return !m_sourceLanguage.isEmpty();
}

void TS::addContext(const Context &context)
{
    m_contexts.insert(context.getName(), context);
}

const Context *TS::findContext(const QString &name) const
{    
    Contexts::const_iterator it = m_contexts.find(name);
    if (it != m_contexts.end())
        return &it.value();
    else
        return nullptr;
}

void TS::merge(const TS &other)
{
    if (!hasLanguage() && other.hasLanguage())
        setLanguage(other.getLanguage());

    if (!hasSourceLanguage() && other.hasSourceLanguage())
        setSourceLanguage(other.getSourceLanguage());

    for (const Context& context : other.contexts())
    {
        Contexts::iterator it = m_contexts.find(context.getName());
        if (it != m_contexts.end())
        {
            it->merge(context);
        }
        else
        {
            addContext(context);
        }
    }
}

TS merge(const TSVector &data)
{
    TS merged;
    for (const TS &ts : data)
        merged.merge(ts);
    return merged;
}
