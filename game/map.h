#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QFile>
#include <QException>

class Map
{
public:
    Map();
protected:
    QVector<QVector<int>> m_tiles;
};

#endif // MAP_H
