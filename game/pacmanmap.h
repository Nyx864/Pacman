#ifndef PACMANMAP_H
#define PACMANMAP_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QException>
#include <QTextStream>
#include "advancedvector.h"
#include "pacman.h"

class PacmanMap : public QObject
{
    Q_OBJECT
public:
    PacmanMap(QString filePath);

    uint tiles(const int& x, const int& y) const;

    bool tileBlocksEntity(const int& x, const int& y);

    bool isIntersection(const int& x, const int& y);

    bool removeDot(Pacman* pacman, int& score);

    int getMapHeight();

    int getMapWidth();

    QPoint getPacmanStartPosition();

    QPoint getBlinkyStartPosition();

    QPoint getClydeStartPosition();

    QPoint getInkyStartPosition();

    QPoint getPinkyStartPosition();

    QPoint getFruitPosition();

    int getAmountOfDots();

signals:
    void bigDotIsEaten();

private:
    AdvancedVector<AdvancedVector<int>> m_tiles;

    QVector<QPoint> m_intersections;

    QPoint m_pacmanStartPosition;

    QPoint m_blinkyStartPosition;

    QPoint m_clydeStartPosition;

    QPoint m_inkyStartPosition;

    QPoint m_pinkyStartPosition;

    QPoint m_fruitPosition;

    int m_amountOfDots;

    void loadMapFromFile(const QString& filePath);

    void updateIntersections();

    void getStartPositions();

    void updateAmountOfDots();
};

#endif // PACMANMAP_H
