#ifndef WORLDTILE_H
#define WORLDTILE_H

#include <QColor>

class WorldTile
{
public:
    WorldTile();
    ~WorldTile();

    QChar displayChar() const;

    QString name() const;
    QString id() const;

    QColor background() const;
    QColor foreground() const;

//    bool isRotateable() const;

    bool isLine() const;
    QString lineID() const;

    void setDisplayChar(QChar displayChar);
    void setBackground(QColor background);
    void setForeground(QColor foreground);
    void setDisplayName(QString displayName);
    void setTileID(QString id);
//    void setRotateable(bool rotate);
    void setLine(bool drawLine);
    void setLineID(QString lineID);

    bool operator!=(const WorldTile& other) const;

private:
    QChar character;

    QString tileName;
    QString tileID;

    QColor bgcolor;
    QColor fgcolor;

//    bool canRotate;

    bool lineDrawing;
    QString lineDrawingID;
};

Q_DECLARE_METATYPE(WorldTile)

#endif // WORLDTILE_H
