#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QTableView>
#include <QRubberBand>
#include <QMouseEvent>
#include <QItemDelegate>
#include <QAction>
#include <QDebug>
#include "worldtile.h"

enum DrawTool { t_pen, t_box, t_hollow_box, t_circle, t_hollow_circle };

Q_DECLARE_METATYPE(DrawTool)

class DisplayWidget : public QTableView
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = 0);

public slots:
    void toolChanged();
    void tileChanged(WorldTile newTile);

private:
    QRubberBand* rubberBand;
    QPoint rubberBandOrigin;

    WorldTile selectedTile;
    DrawTool currentTool;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:

signals:
};

#endif // DISPLAYWIDGET_H
