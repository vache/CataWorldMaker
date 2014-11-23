#include "cataworldmaker.h"
#include "displaywidget.h"
#include "ui_cataworldmaker.h"

// TODO: see output file format read at savegame.cpp

CataWorldMaker::CataWorldMaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CataWorldMaker)
{
    ui->setupUi(this);
    this->initializeDrawingToolbar();

    jsonReader = new OvermapJsonReader("C:/cata-0.A/data/json/overmap_terrain.json");

    ui->TileSelectorView->setModel(&tileModel);
    ui->WorldView->setModel(&worldModel);

    connect(jsonReader, SIGNAL(newTile(WorldTile)), &tileModel, SLOT(addTile(WorldTile)));
    connect(ui->TileSelectorView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeTile(QModelIndex)));
    connect(this, SIGNAL(newTileSelected(WorldTile)), ui->WorldView, SLOT(tileChanged(WorldTile)));
    connect(ui->ZLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(changeZLevel(int)));
    connect(ui->ZLevelSlider, SIGNAL(valueChanged(int)), &worldModel, SLOT(setLevel(int)));

    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(saveWorld()));

    jsonReader->process();

    worldModel.setLevel(0);
    WorldTile t = tileModel.lookupTileByID("field");
    if(t != WorldTile())
    {
        worldModel.fillLevel(t);
    }
    for(int i = 1; i < OMAPS; i++)
    {
        worldModel.setLevel(-1 * i);
        t = tileModel.lookupTileByID("rock");
        if(t != WorldTile())
        {
            worldModel.fillLevel(t);
        }
    }
    worldModel.setLevel(0);

    ui->WorldView->resizeColumnsToContents();
    ui->WorldView->resizeRowsToContents();
}

CataWorldMaker::~CataWorldMaker()
{
    delete ui;
}

void CataWorldMaker::initializeDrawingToolbar()
{
    toolGroup = new QActionGroup(ui->Tools);

    QAction* penAction = new QAction("Pen", toolGroup);
    QVariant v;
    v.setValue<DrawTool>(t_pen);
    penAction->setData(v);
    penAction->setCheckable(true);
    connect(penAction, SIGNAL(triggered()), ui->WorldView, SLOT(toolChanged()));

    QAction* boxAction = new QAction("Box", toolGroup);
    v.setValue<DrawTool>(t_box);
    boxAction->setData(v);
    boxAction->setCheckable(true);
    connect(boxAction, SIGNAL(triggered()), ui->WorldView, SLOT(toolChanged()));

    QAction* hollowBoxAction = new QAction("Hollow Box", toolGroup);
    v.setValue<DrawTool>(t_hollow_box);
    hollowBoxAction->setData(v);
    hollowBoxAction->setCheckable(true);
    connect(hollowBoxAction, SIGNAL(triggered()), ui->WorldView, SLOT(toolChanged()));

    QAction* circleAction = new QAction("Circle", toolGroup);
    v.setValue<DrawTool>(t_circle);
    circleAction->setData(v);
    circleAction->setCheckable(true);
    connect(circleAction, SIGNAL(triggered()), ui->WorldView, SLOT(toolChanged()));

    QAction* hollowCircleAction = new QAction("Hollow Circle", toolGroup);
    v.setValue<DrawTool>(t_hollow_circle);
    hollowCircleAction->setData(v);
    hollowCircleAction->setCheckable(true);
    connect(hollowCircleAction, SIGNAL(triggered()), ui->WorldView, SLOT(toolChanged()));

    ui->Tools->addActions(toolGroup->actions());
}

void CataWorldMaker::changeTile(QModelIndex index)
{
    QVariant v = tileModel.data(index, Qt::UserRole);
    WorldTile tile = v.value<WorldTile>();

    emit newTileSelected(tile);
}

void CataWorldMaker::changeZLevel(int level)
{
    ui->ZLevelLabel->setText(QString::number(level));
}

void CataWorldMaker::saveWorld()
{
    QFile save("c:/cata-0.A/editor/o.0.0");
    save.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream stream(&save);

    stream << worldModel.save();

    stream.flush();

    save.close();
}
