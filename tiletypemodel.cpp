#include "tiletypemodel.h"

TileTypeModel::TileTypeModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QVariant TileTypeModel::data(const QModelIndex &index, int role) const
{
    WorldTile tile = tiles.at(index.row());
    switch(role)
    {
    case Qt::DisplayRole:
    {
        QString pattern = "%1 - %2 - %3";
        return pattern.arg(tile.displayChar()).arg(tile.id()).arg(tile.name());
    }
    case Qt::UserRole:
    {
        QVariant v;
        v.setValue(tile);
        return v;
    }
    default:
        return QVariant();
    }
}

int TileTypeModel::rowCount(const QModelIndex &parent) const
{
    return tiles.count();
}

void TileTypeModel::addTile(WorldTile tile)
{
    beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    tiles.append(tile);
    endInsertRows();
}

WorldTile TileTypeModel::lookupTileByID(QString id)
{
    foreach(WorldTile tile, tiles)
    {
        if(tile.id() == id)
        {
            return tile;
        }
    }
    return WorldTile();
}
