#ifndef BLINKY_H
#define BLINKY_H

#include "ghost.h"
#include <QTimer>

class Blinky: public Ghost
{
    Q_OBJECT
public:
    Blinky(QPoint startPosition);

public slots:
    void updatePixmap();

    void findDestination(Entity* entity);

private:
    int m_currentIndex;

    QPixmap m_upPixmap, m_rightPixmap, m_downPixmap, m_leftPixmap;

    void loadPixmap();
};

#endif // BLINKY_H
