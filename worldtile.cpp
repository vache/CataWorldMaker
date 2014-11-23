#include "worldtile.h"

WorldTile::WorldTile()
{
    this->character = QChar(' ');
    this->tileID = "";
    this->tileName = "";

//    this->canRotate = false;

    this->lineDrawing = false;
    this->lineDrawingID = "";

    this->bgcolor =  QColor(Qt::black);
    this->fgcolor =  QColor(Qt::black);
}

WorldTile::~WorldTile()
{

}

QChar WorldTile::displayChar() const
{
    return character;
}

QString WorldTile::name() const
{
    return tileName;
}

QString WorldTile::id() const
{
    return tileID;
}

QColor WorldTile::background() const
{
    return bgcolor;
}

QColor WorldTile::foreground() const
{
    return fgcolor;
}

//bool WorldTile::isRotateable() const
//{
//    return canRotate;
//}

bool WorldTile::isLine() const
{
    return lineDrawing;
}

QString WorldTile::lineID() const
{
    return lineDrawingID;
}

void WorldTile::setDisplayChar(QChar displayChar)
{
    character = displayChar;
}

void WorldTile::setBackground(QColor background)
{
    bgcolor = background;
}

void WorldTile::setForeground(QColor foreground)
{
    fgcolor = foreground;
}

void WorldTile::setDisplayName(QString displayName)
{
    tileName = displayName;
}

void WorldTile::setTileID(QString id)
{
    tileID = id;
    if(lineDrawing)
    {
        lineDrawingID = id;
    }
}

//void WorldTile::setRotateable(bool rotate)
//{
//    canRotate = rotate;
//}

void WorldTile::setLine(bool drawLine)
{
    lineDrawing = drawLine;
}

void WorldTile::setLineID(QString lineID)
{
    lineDrawingID = lineID;
}

bool WorldTile::operator!=(const WorldTile& other) const
{
    bool notEqual = false;
    if(bgcolor != other.background() ||
            fgcolor != other.foreground() ||
            character != other.displayChar() ||
            tileID != other.id() ||
            tileName != other.name() ||
            lineDrawing != other.isLine() ||
            lineDrawingID != other.lineID() /*||
            canRotate != other.isRotateable()*/)
    {
        notEqual = true;
    }

    return notEqual;
}
