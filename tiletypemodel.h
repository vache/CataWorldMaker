#ifndef TILETYPEMODEL_H
#define TILETYPEMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "worldtile.h"

class TileTypeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TileTypeModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

public slots:

    void addTile(WorldTile tile);
    WorldTile lookupTileByID(QString id);

private:

    QVector<WorldTile> tiles;

private slots:

signals:


};

#endif // TILETYPEMODEL_H
