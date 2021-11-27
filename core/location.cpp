// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "location.h"

const int Location::INVALID_LINE = -1;

Location::Location() = default;

Location::Location(const QString &filename, int line)
    :m_filename(filename)
    ,m_line(line)
{

}

bool Location::operator==(const Location &other) const
{
    return m_filename == other.m_filename && m_line == other.m_line;
}

bool Location::operator<(const Location &other) const
{
    if (m_filename == other.m_filename)
    {
        return m_line < other.m_line;
    }
    else
    {
        return m_filename < other.m_filename;
    }
}

bool Location::hasLine() const
{
    return m_line > INVALID_LINE;
}

bool Location::isValid() const
{
    return !m_filename.isEmpty();
}
