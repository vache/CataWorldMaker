#ifndef OVERMAPJSONREADER_H
#define OVERMAPJSONREADER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QObject>

#include "worldtile.h"
#include "colors.h"

class OvermapJsonReader : public QObject
{
    Q_OBJECT
public:
    OvermapJsonReader(QString filename, QObject* parent = 0);
    void process();

public slots:

private:
    QJsonDocument jsonDoc;

private slots:

signals:
    void newTile(WorldTile);
};

#endif // OVERMAPJSONREADER_H
