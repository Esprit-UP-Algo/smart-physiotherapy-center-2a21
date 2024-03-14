#include "redez_vous.h"

redez_vous::redez_vous(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant redez_vous::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex redez_vous::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex redez_vous::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int redez_vous::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int redez_vous::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant redez_vous::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
