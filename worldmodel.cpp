#include "worldmodel.h"

WorldModel::WorldModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    world.resize(OMAPSIZE * OMAPS);
    currentLevel = 0;
}

QVariant WorldModel::data(const QModelIndex &index, int role) const
{
    WorldTile tile = world.at(convertIndex(index));

    switch(role)
    {
    case Qt::DisplayRole:
        return tile.displayChar();
    case Qt::BackgroundRole:
        return QBrush(tile.background());
    case Qt::ForegroundRole:
        return QBrush(tile.foreground());
    case Qt::SizeHintRole:
        return QSize(12, 12);
    default:
        return QVariant();
    }
}

int WorldModel::rowCount(const QModelIndex & parent) const
{
    return OMAPSIDE;
}

int WorldModel::columnCount(const QModelIndex & parent) const
{
    return OMAPSIDE;
}

QModelIndex WorldModel::index(int row, int column, const QModelIndex &parent) const
{
    return this->createIndex(row, column);
}

bool WorldModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.canConvert<WorldTile>())
    {
        WorldTile tile = value.value<WorldTile>();
        world.replace(convertIndex(index), tile);

        emit dataChanged(index, index);
    }
}

void WorldModel::setLevel(int level)
{
    currentLevel = -1 * level;
    emit dataChanged(index(0, 0), index(179, 179));
}

void WorldModel::fillLevel(WorldTile tile)
{
    QVariant v;
    v.setValue<WorldTile>(tile);

    for(int i = 0; i < OMAPSIDE; i++)
    {
        for(int j = 0; j < OMAPSIDE; j++)
        {
            setData(this->index(i, j), v);
        }
    }
}

QByteArray WorldModel::save()
{
    QByteArray output;

    QTextStream stream(&output);

    for(int m = 0; m < OMAPS; m++)
    {
        int inARow = 0;
        WorldTile lastTile = WorldTile();

        stream << "L " << 10-m << "\n";
        for(int i = 0; i < OMAPSIDE; i++)
        {
            for(int j = 0; j < OMAPSIDE; j++)
            {
                int index = (m * OMAPSIZE) + (i * OMAPSIDE) + j;
                WorldTile thisTile = world.at(index);

                if(thisTile.isLine())
                {
                    //  |   _ns, _ew, _es, _wn, _ne, _sw
                    // -*-  _esw, _nes, _nsw, _new
                    //  |   _nesw
                    // line above = index - 180, line below = index + 180
                    bool north = false, west = false, east = false, south = false;
                    QString n, w, e, s = "";
                    QString pattern = "%1_%2%3%4%5";
                    if(index - OMAPSIDE > 0)
                    {
                        north = (world.at(index - OMAPSIDE).id() == thisTile.id());
                        if(north) n = "n";
                    }
                    if(index + OMAPSIDE < OMAPSIZE)
                    {
                        south = (world.at(index + OMAPSIDE).id() == thisTile.id());
                        if(south) s = "s";
                    }
                    if((index - 1) % OMAPSIDE != 0)
                    {
                        west = (world.at(index - 1).id() == thisTile.id());
                        if(west) w = "w";
                    }
                    if((index + 1) % OMAPSIDE != 0)
                    {
                        east = (world.at(index + 1).id() == thisTile.id());
                        if(east) e = "e";
                    }
                    QString directions = pattern.arg(thisTile.id()).arg(n).arg(e).arg(s).arg(w);
                    if(north && west && !east && !south)
                    {
                        directions = pattern.arg(thisTile.id()).arg(w).arg(n).arg(e).arg(s);
                    }
                    else if(!north && !east && !south && !west)
                    {
                        directions = pattern.arg(thisTile.id()).arg("n").arg("e").arg("s").arg("w");
                    }
                    else if((north && !(south || east || west)) || (south && !(north || east || west)))
                    {
                        directions = pattern.arg(thisTile.id()).arg("n").arg("s").arg("").arg("");
                    }
                    else if((east && !(south || north || west)) || (west && !(north || east || south)))
                    {
                        directions = pattern.arg(thisTile.id()).arg("e").arg("w").arg("").arg("");
                    }
                    thisTile.setLineID(directions);
                }

                if(thisTile != lastTile)
                {
                    if(inARow > 0)
                    {
                        if(lastTile.isLine())
                        {
                            stream << lastTile.lineID() << " " << inARow << " ";
                        }
                        else
                        {
                            stream << lastTile.id() << " " << inARow << " ";
                        }
                    }
                    lastTile = thisTile;
                    inARow = 1;
                }
                else
                {
                    inARow++;
                }
            }
        }
        stream << lastTile.id() << " " << inARow << "\n";
    }
    stream.flush();

    return output;
}

int WorldModel::convertIndex(const QModelIndex & in) const
{
    //  column
    //r 0-179
    //o 180-359
    //w 360-539

    // row * 180 + column = index

    return (currentLevel * OMAPSIZE) + (in.row() * OMAPSIDE) + in.column();
}
