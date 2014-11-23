#include  <QDebug>
#include "overmapjsonreader.h"

OvermapJsonReader::OvermapJsonReader(QString filename, QObject* parent)
    : QObject(parent)
{
    QFile jsonFile;
    jsonFile.setFileName(filename);
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "ERROR OPENING JSON FILE";
    }

    jsonDoc = QJsonDocument::fromJson(jsonFile.readAll());

    jsonFile.close();
}

void OvermapJsonReader::process()
{
    if(jsonDoc.isNull())
    {
        qDebug() << "ERROR READING JSON FILE";
        return;
    }
    if(jsonDoc.isArray())
    {
        QJsonArray jsonArray = jsonDoc.array();
        for(int i = 0; i < jsonArray.size(); i++)
        {
            QJsonValue jsonValue = jsonArray.at(i);
            if(jsonValue.isObject())
            {
                QJsonObject jsonObj = jsonValue.toObject();
                if(jsonObj.contains("type") && jsonObj.value("type").toString() == "overmap_terrain")
                {
                    WorldTile tile;

                    if(jsonObj.contains("name"))
                    {
                        tile.setDisplayName(jsonObj.value("name").toString());
                    }

                    if(jsonObj.contains("id"))
                    {
                        tile.setTileID(jsonObj.value("id").toString());
                    }

                    if(jsonObj.contains("color"))
                    {
                        QString color = jsonObj.value("color").toString();
                        tile.setBackground(color_from_string(color).bg);
                        tile.setForeground(color_from_string(color).fg);
                    }
                    else if(jsonObj.contains("bgcolor"))
                    {
                        QString color = jsonObj.value("bgcolor").toString();
                        tile.setBackground(bgcolor_from_string(color).bg);
                        tile.setForeground(bgcolor_from_string(color).fg);
                    }

                    if(jsonObj.contains("line_drawing"))
                    {
                        tile.setLine(jsonObj.value("line_drawing").toBool());
                    }

//                    if(jsonObj.contains("rotate"))
//                    {
//                        tile.setRotateable(jsonObj.value("rotate").toBool());
//                    }

                    if(jsonObj.contains("sym"))
                    {
                        if(jsonObj.value("sym").isArray())
                        {
                            QJsonArray symArray = jsonObj.value("sym").toArray();
                            for(int i = 0; i < symArray.size(); i++)
                            {
                                WorldTile altTile = tile;
                                int sym = symArray.at(i).toVariant().toInt();
                                altTile.setDisplayChar(QChar(sym));
                                switch(sym)
                                {
                                case 94:
                                    altTile.setTileID(altTile.id() + "_north");
                                    break;
                                case 62:
                                    altTile.setTileID(altTile.id() + "_east");
                                    break;
                                case 118:
                                    altTile.setTileID(altTile.id() + "_south");
                                    break;
                                case 60:
                                    altTile.setTileID(altTile.id() + "_west");
                                    break;
                                default:
                                    break;
                                }

                                emit newTile(altTile);
                            }
                            continue;
                        }
                        else
                        {
                            tile.setDisplayChar(QChar(jsonObj.value("sym").toVariant().toInt()));
                        }
                    }
                    else
                    {
                        tile.setDisplayChar(QChar('r'));
                    }

                    emit newTile(tile);
                }
            }
        }
    }
}
