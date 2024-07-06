#include "pacmanmap.h"

PacmanMap::PacmanMap(QString filePath)
{
    loadMapFromFile(filePath);
    updateIntersections();
    getStartPositions();
    updateAmountOfDots();
}

uint PacmanMap::tiles(const int& x, const int& y) const
{
    return m_tiles[x][y];
}

bool PacmanMap::tileBlocksEntity(const int& x, const int& y)
{
    return m_tiles[x][y] == Resources::Tiles::Wall;
}

bool PacmanMap::isIntersection(const int& x, const int& y)
{
    QPoint checkablePlace{ x, y };
    foreach(const auto& intersection, m_intersections)
    {
        if(intersection == checkablePlace)
            return true;
    }
    return false;
}

bool PacmanMap::removeDot(Pacman* pacman, int &score)
{
    if (m_tiles[pacman->getTileX()][pacman->getTileY()] == Resources::Tiles::SmallDot)
    {
        m_tiles[pacman->getTileX()][pacman->getTileY()] = Resources::Tiles::Empty;
        pacman->eatDot();
        score += 5;
        return true;
    }
    else if (m_tiles[pacman->getTileX()][pacman->getTileY()] == Resources::Tiles::BigDot)
    {
        m_tiles[pacman->getTileX()][pacman->getTileY()] = Resources::Tiles::Empty;
        pacman->eatDot();
        score += 20;
        emit bigDotIsEaten();
        return true;
    }
    return false;
}

int PacmanMap::getMapHeight()
{
    return m_tiles.size();
}

int PacmanMap::getMapWidth()
{
    return m_tiles[0].size();
}

QPoint PacmanMap::getPacmanStartPosition()
{
    return m_pacmanStartPosition;
}

QPoint PacmanMap::getBlinkyStartPosition()
{
    return m_blinkyStartPosition;
}

QPoint PacmanMap::getClydeStartPosition()
{
    return m_clydeStartPosition;
}

QPoint PacmanMap::getInkyStartPosition()
{
    return m_inkyStartPosition;
}

QPoint PacmanMap::getPinkyStartPosition()
{
    return m_pinkyStartPosition;
}

QPoint PacmanMap::getFruitPosition()
{
    return m_fruitPosition;
}

int PacmanMap::getAmountOfDots()
{
    return m_amountOfDots;
}

void PacmanMap::loadMapFromFile(const QString &filePath)
{
    m_tiles.clear();
    QFile map(filePath);

    if(!map.exists())
    {
        throw QException::exception("Failed to find map file");
    }

    if(!map.open(QIODevice::ReadOnly))
    {
        throw QException::exception("Failed to open map file");
    }

    while(!map.atEnd())
    {
        AdvancedVector<int> row;
        QTextStream stream(map.readLine());
        while(!stream.atEnd())
        {
            QString tile;
            stream >> tile;
            if(tile != "")
                row.push_back(tile.toInt());
        }
        m_tiles.push_back(row);
    }
}

void PacmanMap::updateIntersections()
{
    m_intersections.clear();
    for(int x = 0; x < m_tiles.size(); ++x)
    {
        for(int y = 0; y < m_tiles[x].size(); ++y)
        {
            if(m_tiles[x][y] != Resources::Tiles::Wall)
            {
                int posibleMoves { 0 };
                if(m_tiles[x+1][y] != Resources::Tiles::Wall)
                    ++posibleMoves;
                if(m_tiles[x-1][y] != Resources::Tiles::Wall)
                    ++posibleMoves;
                if(m_tiles[x][y+1] != Resources::Tiles::Wall)
                    ++posibleMoves;
                if(m_tiles[x][y-1] != Resources::Tiles::Wall)
                    ++posibleMoves;

                if(posibleMoves > 2)
                    m_intersections.push_back(QPoint(x,y));
            }
        }
    }
}

void PacmanMap::getStartPositions()
{
    for(int x = 0; x < m_tiles.size(); ++x)
    {
        for(int y = 0; y < m_tiles[x].size(); ++y)
        {
            if(m_tiles[x][y] == Resources::Tiles::PacmanStartPosition)
            {
                m_pacmanStartPosition = QPoint(x,y);
                m_tiles[x][y] = Resources::Tiles::Empty;
            }
            if(m_tiles[x][y] == Resources::Tiles::BlinkyStartPosition)
            {
                m_blinkyStartPosition = QPoint(x,y);
                m_tiles[x][y] = Resources::Tiles::Empty;
            }
            if(m_tiles[x][y] == Resources::Tiles::ClydeStartPosition)
            {
                m_clydeStartPosition = QPoint(x,y);
                m_tiles[x][y] = Resources::Tiles::Empty;
            }
            if(m_tiles[x][y] == Resources::Tiles::InkyStartPosition)
            {
                m_inkyStartPosition = QPoint(x,y);
                m_tiles[x][y] = Resources::Tiles::Empty;
            }
            if(m_tiles[x][y] == Resources::Tiles::PinkyStartPosition)
            {
                m_pinkyStartPosition = QPoint(x,y);
                m_tiles[x][y] = Resources::Tiles::Empty;
            }
            if(m_tiles[x][y] == Resources::Tiles::Fruit)
            {
                m_fruitPosition = QPoint(x,y);
                m_tiles[x][y] = Resources::Tiles::Empty;
            }
        }
    }
}

void PacmanMap::updateAmountOfDots()
{
    m_amountOfDots = 0;
    for(int x = 0; x < m_tiles.size(); ++x)
    {
        for(int y = 0; y < m_tiles[x].size(); ++y)
        {
            if(m_tiles[x][y] == Resources::Tiles::SmallDot || m_tiles[x][y] == Resources::Tiles::BigDot)
            {
                m_amountOfDots++;
            }
        }
    }
}
