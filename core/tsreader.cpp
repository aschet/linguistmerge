// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "tsreader.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include "ts.h"
#include "tsxmldefs.h"

using namespace TSXMLDefs;

bool TSReader::isTSFile(const QString &filename)
{
    return !filename.isEmpty() && QFileInfo(filename).suffix().compare("ts", Qt::CaseInsensitive) == 0;
}

bool TSReader::read(const QString &filename, TS *ts)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        TSReader reader(&file);
        reader.read(ts);
        ts->setFilename(filename);
        return true;
    }
    return false;
}

void TSReader::read(TS *ts)
{
    m_ts = ts;
    *m_ts = TS();
    while (!atEnd())
    {
        readNext();

        if (elementStarts(TAG_TS))
        {
            readTS();
        }
    }
}

bool TSReader::elementStarts(const QString &elementName) const
{
    return isStartElement() && name() == elementName;
}

bool TSReader::elementEnds(const QString &elementName) const
{
    return isEndElement() && name() == elementName;
}

void TSReader::readTS()
{
    QXmlStreamAttributes attrs = attributes();
    m_ts->setLanguage(attrAsString(attrs, ATTR_LANGUAGE));
    m_ts->setSourceLanguage(attrAsString(attrs, ATTR_SOURCELANGUAGE));

    while (!atEnd())
    {
        readNext();

        if (elementStarts(TAG_CONTEXT))
        {
            readContext();
        }
    }
}

void TSReader::readContext()
{
    m_currentContext = Context();

    while (!atEnd())
    {
        readNext();

        if (elementStarts(TAG_NAME))
        {
            m_currentContext.setName(readElementText());
        }
        else if (elementStarts(TAG_MESSAGE))
        {
            readMessage();
        }
        else if (elementEnds(TAG_CONTEXT))
        {
            break;
        }
    }

    if (m_currentContext.isValid())
        m_ts->addContext(m_currentContext);
}

void TSReader::readMessage()
{
    Message message;
    message.setNumerus(attrAsBool(attributes(), ATTR_NUMERUS, false));

    while (!atEnd())
    {
        readNext();

        if (elementStarts(TAG_LOCATION))
        {
            Location location;
            QXmlStreamAttributes attrs = attributes();
            location.setFileName(attrAsString(attrs, ATTR_FILENAME));
            location.setLine(attrAsInt(attrs, ATTR_LINE, Location::INVALID_LINE));
            message.locations().push_back(location);
        }
        else if (elementStarts(TAG_SOURCE))
        {
            message.setSource(readElementText());
        }
        else if (elementStarts(TAG_TRANSLATORCOMMENT))
        {
            message.setTranslatorComment(readElementText());
        }
        else if (elementStarts(TAG_TRANSLATION))
        {
            message.setType(attrAsType(attributes(), ATTR_TYPE));
            if (!message.isNumerus())
                message.translations().push_back(readElementText());
        }
        else if (elementStarts(TAG_NUMERUSFORM))
        {
            message.translations().push_back(readElementText());
        }
        else if (elementEnds(TAG_MESSAGE))
        {
            break;
        }
    }

    if (message.isValid())
        m_currentContext.addMessage(message);
}

QString TSReader::attrAsString(const QXmlStreamAttributes &attrs, const QString &name) const
{
    return attrs.value(name).toString();
}

int TSReader::attrAsInt(const QXmlStreamAttributes &attrs, const QString &name, int defaultValue) const
{
    QStringView attr = attrs.value(name);
    int value = defaultValue;
    if (!attr.isEmpty())
    {
        bool isOK = false;
        int eval = attr.toInt(&isOK);
        if (isOK)
            value = eval;
    }
    return value;
}

bool TSReader::attrAsBool(const QXmlStreamAttributes &attrs, const QString &name, bool defaultValue) const
{
    QStringView attr = attrs.value(name);
    bool value = defaultValue;
    if (!attr.isEmpty())
    {
        value = attr.compare(VALUE_YES, Qt::CaseInsensitive) == 0;
    }
    return value;
}

Message::Type TSReader::attrAsType(const QXmlStreamAttributes &attrs, const QString &name) const
{
    Message::Type type = Message::Type::Finished;
    auto attr = attrs.value(name);
    if (!attr.isEmpty())
    {
        if (attr.compare(VALUE_UNFINISHED, Qt::CaseInsensitive) == 0)
            type = Message::Type::Unfinished;
        else if (attr.compare(VALUE_OBSOLETE, Qt::CaseInsensitive) == 0)
            type = Message::Type::Obsolete;
    }
    return type;
}
