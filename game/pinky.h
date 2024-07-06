#ifndef PINKY_H
#define PINKY_H

#include "ghost.h"

class Pinky: public Ghost
{
    Q_OBJECT
public:
    Pinky(QPoint startPosition);

public slots:
    void updatePixmap();

    void findDestination(Entity* entity, const Resources::Direction& entityDirection);

private:
    int m_currentIndex;

    QPixmap m_upPixmap, m_rightPixmap, m_downPixmap, m_leftPixmap;

    void loadPixmap();
};

#endif // PINKY_H
