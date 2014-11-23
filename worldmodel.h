#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QBrush>
#include <QDebug>
#include "worldtile.h"

#define OMAPSIDE 180
#define OMAPSIZE (OMAPSIDE*OMAPSIDE)
#define OMAPS 11

class WorldModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WorldModel(QObject *parent = 0);

    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;

    int rowCount( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount( const QModelIndex & parent = QModelIndex() ) const ;

    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const ;

public slots:
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    void setLevel( int level );

    void fillLevel( WorldTile tile );

    QByteArray save();

private:

    int convertIndex(const QModelIndex & in) const;
    int currentLevel;

    QVector<WorldTile> world;


private slots:

signals:

};

#endif // WORLDMODEL_H
