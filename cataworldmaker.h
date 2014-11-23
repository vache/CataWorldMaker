#ifndef CATAWORLDMAKER_H
#define CATAWORLDMAKER_H

#include <QMainWindow>
#include <QAction>
#include <QDebug>
#include "worldmodel.h"
#include "tiletypemodel.h"
#include "overmapjsonreader.h"

namespace Ui {
class CataWorldMaker;
}

class CataWorldMaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit CataWorldMaker(QWidget *parent = 0);
    ~CataWorldMaker();

public slots:

private:
    Ui::CataWorldMaker *ui;
    QActionGroup* toolGroup;

    OvermapJsonReader* jsonReader;
    WorldModel worldModel;
    TileTypeModel tileModel;

    void initializeDrawingToolbar();

private slots:
    void changeTile(QModelIndex index);
    void changeZLevel(int level);
    void saveWorld();

signals:
    void newTileSelected(WorldTile);
    void drawToolChanged();

};

#endif // CATAWORLDMAKER_H
