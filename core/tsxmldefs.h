// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TSXMLDEFS_H
#define TSXMLDEFS_H

#include <QtCore/QString>

namespace TSXMLDefs
{
const QString TAG_TS = "TS";

const QString TAG_CONTEXT = "context";

const QString TAG_NAME = "name";

const QString TAG_MESSAGE = "message";

const QString TAG_LOCATION = "location";

const QString TAG_SOURCE = "source";

const QString TAG_TRANSLATORCOMMENT = "translatorcomment";

const QString TAG_TRANSLATION = "translation";

const QString TAG_NUMERUSFORM = "numerusform";

const QString ATTR_VERSION = "version";

const QString ATTR_LANGUAGE = "language";

const QString ATTR_SOURCELANGUAGE = "sourcelanguage";

const QString ATTR_NUMERUS = "numerus";

const QString ATTR_FILENAME = "filename";

const QString ATTR_LINE = "line";

const QString ATTR_TYPE = "type";

const QString VALUE_YES = "yes";

const QString VALUE_UNFINISHED = "unfinished";

const QString VALUE_OBSOLETE = "obsolete";
};

#endif
