#ifndef INKY_H
#define INKY_H

#include "ghost.h"

class Inky: public Ghost
{
    Q_OBJECT
public:
    Inky(QPoint startPosition);

public slots:
    void updatePixmap();

    void findDestination(Entity* entity, Ghost* blinky);

private:
    int m_currentIndex;

    QPixmap m_upPixmap, m_rightPixmap, m_downPixmap, m_leftPixmap;

    void loadPixmap();
};

#endif // INKY_H
