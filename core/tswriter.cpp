// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "tswriter.h"

#include <QtCore/QFile>
#include "ts.h"
#include "tsxmldefs.h"

using namespace TSXMLDefs;

bool TSWriter::write(const QString &filename, const TS *ts)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        TSWriter writer(&file);
        writer.write(ts);
        return true;
    }
    return false;
}

void TSWriter::write(const TS *ts)
{
    setAutoFormatting(true);
    writeStartDocument();
    writeDTD("<!DOCTYPE TS>");
    writeStartElement(TAG_TS);
    writeAttribute(ATTR_VERSION, "2.1");
    writeAttribute(ATTR_LANGUAGE, ts->getLanguage());
    if (ts->hasSourceLanguage())
        writeAttribute(ATTR_SOURCELANGUAGE, ts->getSourceLanguage());

    for (const Context &context : ts->contexts())
    {
        if (context.messages().isEmpty())
            continue;

        writeStartElement(TAG_CONTEXT);
        writeTextElement(TAG_NAME, context.getName());

        for (const Message &message : context.messages())
        {
            writeStartElement(TAG_MESSAGE);
            if (message.isNumerus())
                writeAttribute(ATTR_NUMERUS, VALUE_YES);

            for (const Location &location : message.locations())
            {
                writeStartElement(TAG_LOCATION);
                writeAttribute(ATTR_FILENAME, location.getFilename());
                if (location.hasLine())
                    writeAttribute(ATTR_LINE, QString::number(location.getLine()));
                writeEndElement();
            }

            writeTextElement(TAG_SOURCE, message.getSource());

            if (message.hasTranslatorComment())
                writeTextElement(TAG_TRANSLATORCOMMENT, message.getTranslatorComment());

            writeStartElement(TAG_TRANSLATION);
            if (message.getType() != Message::Finished)
                writeAttribute(ATTR_TYPE, typeAsAttr(message.getType()));
            if (message.translations().size() > 1)
            {
                for (const QString &translation : message.translations())
                {
                    writeStartElement(TAG_NUMERUSFORM);
                    writeCharacters(translation);
                    writeEndElement();
                }
            }
            else
            {
                QString translation;
                if (message.translations().size() == 1)
                    translation = message.translations().first();
                writeCharacters(translation);
            }
            writeEndElement();
            writeEndElement();
        }

        writeEndElement();
    }

    writeEndElement();
    writeEndDocument();
}

QString TSWriter::typeAsAttr(Message::Type type) const
{
    switch (type)
    {
    case Message::Unfinished:
        return VALUE_UNFINISHED;
    case Message::Obsolete:
        return VALUE_OBSOLETE;
    default:
        return QString();
    }
}
