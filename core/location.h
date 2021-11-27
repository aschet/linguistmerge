// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LOCATION_H
#define LOCATION_H

#include <limits> // workaround for compilation problems with numeric_limits
#include <QtCore/QString>
#include <QtCore/QVector>

class Location
{
public:
    static const int INVALID_LINE;

    Location();

    Location(const QString &filename, int line = INVALID_LINE);

    bool operator==(const Location &other) const;

    bool operator<(const Location &other) const;

    inline QString getFilename() const
    {
        return m_filename;
    }

    inline void setFileName(const QString &filename)
    {
        m_filename = filename;
    }

    inline int getLine() const
    {
        return m_line;
    }

    inline void setLine(int line)
    {
        m_line = line;
    }

    bool hasLine() const;

    bool isValid() const;

private:
    QString m_filename;

    int m_line = INVALID_LINE;
};

typedef QVector<Location> Locations;

#endif
