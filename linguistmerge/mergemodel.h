// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MERGEMODEL_H
#define MERGEMODEL_H

#include <ts.h>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QStringList>

class MergeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MergeModel(QObject *parent = nullptr);

    bool add(const QStringList &filenames);

    bool add(const QString &filename);

    void remove(const QModelIndexList& indexList);

    void clear();

    bool hasData() const;

    TS merge() const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    virtual QModelIndex parent(const QModelIndex &index) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual Qt::DropActions supportedDropActions() const override;

    virtual QStringList mimeTypes() const override;

    virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;

    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    static QStringList getFilesFromMimeData(const QMimeData *data);

private:
    TSVector m_model;
};

#endif
