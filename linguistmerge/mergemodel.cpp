// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include "mergemodel.h"

#include <QDir>
#include <QMimeData>
#include <QUrl>
#include <tsreader.h>
#include "waitcursorscope.h"

MergeModel::MergeModel(QObject *parent)
    :QAbstractItemModel(parent)
{

}

bool MergeModel::add(const QStringList &filenames)
{
    bool result = true;
    for (const QString &filename : filenames)
        result &= add(filename);
    return result;
}

bool MergeModel::add(const QString &filename)
{
    if (!TSReader::isTSFile(filename))
        return false;

    WaitCursorScope wc;

    TS ts;
    bool result = TSReader::read(filename, &ts);
    if (result)
    {
        int size = m_model.size();
        beginInsertRows(QModelIndex(), size, size);
        m_model.push_back(ts);
        endInsertRows();
    }
    return result;
}

void MergeModel::remove(const QModelIndexList &indexList)
{
    if (indexList.isEmpty())
        return;

    // currently only contigous selections are supported
    int firstRow = indexList.first().row();
    int lastRow = indexList.last().row();
    beginRemoveRows(QModelIndex(), firstRow, lastRow);
    m_model.erase(m_model.begin() + firstRow, m_model.begin() + lastRow + 1);
    endRemoveRows();
}

void MergeModel::clear()
{
    beginResetModel();
    m_model.clear();
    endResetModel();
}

bool MergeModel::hasData() const
{
    return !m_model.empty();
}

TS MergeModel::merge() const
{
    return ::merge(m_model);
}

QVariant MergeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    switch (section)
    {
    case 0:
        return tr("Filename");
    case 1:
        return tr("Language");
    case 2:
        return tr("Contexts");
    default:
        return QVariant();
    }
}

int MergeModel::columnCount(const QModelIndex &) const
{
    return 3;
}

int MergeModel::rowCount(const QModelIndex &index) const
{
    if (!index.isValid())
        return m_model.size();
    else
        return 0;
}

QModelIndex MergeModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column);
}

QModelIndex MergeModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

QVariant MergeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const TS &ts = m_model.at(index.row());
    switch (index.column())
    {
    case 0:
        return QDir::toNativeSeparators(ts.getFilename());
    case 1:
    {
        QString language = ts.getLanguage();
        if (language.isEmpty())
            language = tr("-");
         return language;
    }
    case 2:
        return ts.contexts().size();
    default:
        return QVariant();
    }
}

Qt::ItemFlags MergeModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;
}

Qt::DropActions MergeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList MergeModel::mimeTypes() const
{
    QStringList types = QAbstractItemModel::mimeTypes();
    types << "text/uri-list";
    return types;
}

bool MergeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    return QAbstractItemModel::canDropMimeData(data, action, row, column, parent) && !getFilesFromMimeData(data).isEmpty();
}

bool MergeModel::dropMimeData(const QMimeData *data, Qt::DropAction, int, int, const QModelIndex &)
{
    QStringList sourceFiles = getFilesFromMimeData(data);
    add(sourceFiles);
    return !sourceFiles.isEmpty();
}

QStringList MergeModel::getFilesFromMimeData(const QMimeData *data)
{
    QStringList sourceFiles;
    if (data->hasUrls())
    {
        QList<QUrl> urls = data->urls();
        for (auto it = urls.begin(), endIt = urls.end(); it != endIt; ++it)
        {
            QString localFile = it->toLocalFile();
            if (TSReader::isTSFile(localFile))
                sourceFiles.append(localFile);
        }

    }
    return sourceFiles;
}
