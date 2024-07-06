#ifndef CLYDE_H
#define CLYDE_H

#include "ghost.h"

class Clyde: public Ghost
{
    Q_OBJECT
public:
    Clyde(QPoint startPosition);

public slots:
    void updatePixmap();

    void findDestination(Entity* entitity);

private:
    int m_currentIndex;

    QPixmap m_upPixmap, m_rightPixmap, m_downPixmap, m_leftPixmap;

    void loadPixmap();
};


#endif // CLYDE_H
